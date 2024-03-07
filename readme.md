## 1.wayland 协议文件的基础一

1-1. **定义协议接口**: 首先，在 XML 文件中定义扩展协议。在这个文件中，指定接口、请求、事件和它们的参数。一个可能的 XML 定义：

    ```xml
    <protocol name="my_extension">
      <interface name="my_interface" version="1">
        <request name="function1">
          <arg name="x" type="int"/>
          <arg name="y" type="int"/>
          <arg name="w" type="int"/>
          <arg name="h" type="int"/>
        </request>
        <event name="onfunction1">
          <arg name="x" type="int"/>
          <arg name="y" type="int"/>
          <arg name="w" type="int"/>
          <arg name="h" type="int"/>
        </event>
      </interface>
    </protocol>
    ```

    这个定义声明了一个名为 `my_interface` 的新接口，该接口有一个请求 `function1` 和一个事件 `onfunction1`。

1-2. **生成C代码**: 使用 `wayland-scanner` 根据 XML 协议文件生成 C 语言代码。
--这里注意wayland-scanner的版本，尤其是移植扩展协议和修改一有协议后.

    ```bash 
    wayland-scanner private-code < my_protocol.xml > my_protocol.c
    wayland-scanner client-header < my_protocol.xml > my_protocol-client-protocol.h
    wayland-scanner server-header < my_protocol.xml > my_protocol-server-protocol.h
    ```

1-3. **实现客户端代码**: 在客户端，你将调用由 `wayland-scanner` 生成的函数来发送 `function1` 请求。

    ```c
    my_interface_function1(my_interface_proxy, x, y, w, h);
    ```
    这里，`my_interface_proxy` 是客户端持有的服务端对象的代理，`x`, `y`, `w`, `h` 是你的参数。
1-4. **实现服务端代码**: 在服务端，你需要监听这个请求，并在接收到请求时执行相应的操作。这通常是通过设置一个监听器（或回调函数）来完成。

    ```c
    static void
    my_interface_function1_handler(struct wl_client *client, struct wl_resource *resource, int x, int y, int w, int h) {
        // 这里执行服务端需要做的对应于 function1 请求的操作

        // 假设有服务端需要回送的事件
        my_interface_send_onfunction1(resource, x, y, w, h);
    }

    static const struct my_interface_interface my_interface_implementation = {
        .function1 = my_interface_function1_handler,
    };
    ```

    在这里，`my_interface_function1_handler` 是当客户端发送 `function1` 请求时服务端要调用的函数。`my_interface_interface` 是一个结构体，定义了服务端对于 `my_interface` 可能会处理的请求的实现。

1-5. **绑定接口**: 最后，服务端和客户端都需要知道何时以及如何创建或绑定到这个新的扩展接口。这通常涉及到扩展 `wl_registry` 的使用，以及管理全局和客户端对象的创建。

通过这种方式，当客户端调用 `function1` 时，服务端会收到请求并运行 `my_interface_function1_handler` 函数，参数也将是 `x`, `y`, `w`, `h`。在这个处理函数中，服务端可以执行它需要做的任何事情，包括例如更新窗口大小、位置或发送一个事件回客户端。

## 2.wayland协议扩展


1-1. **定义协议接口**: 首先，在 XML 文件中定义扩展协议。在这个文件中，指定接口、请求、事件和它们的参数。以llp_protocol.xml为列：

```xml
  <protocol name="llp_extension">
      <interface name="llp_interface" version="1">
        <request name="function1">
          <arg name="x" type="int"/>
          <arg name="y" type="int"/>
          <arg name="w" type="int"/>
          <arg name="h" type="int"/>
        </request>
        <event name="onfunction1">
          <arg name="x" type="int"/>
          <arg name="y" type="int"/>
          <arg name="w" type="int"/>
          <arg name="h" type="int"/>
        </event>
      </interface>
    </protocol>
```



1-2. **生成C代码**: 使用 `wayland-scanner` 根据 XML 协议文件生成 C 语言代码。
--这里注意wayland-scanner的版本，尤其是移植扩展协议和修改一有协议后，x86和imx8的版本也不相同。

    ```bash 
    wayland-scanner private-code < llP_protocol.xml > my_protocol.c
    wayland-scanner client-header < llp_protocol.xml > my_protocol-client-protocol.h
    wayland-scanner server-header < my_protocol.xml > my_protocol-server-protocol.h
    ```

1-3.客户端移植移：

client.c:

```c
#include <stdio.h>
#include <stdlib.h>
#include <wayland-client.h>
#include "my_protocol-client-protocol.h"
#include <string.h>
struct llp_interface *my_interface;// 1
static void on_function1(void *data, struct llp_interface *my_interface, int32_t x, int32_t y, int32_t w, int32_t h) {
  printf("onfunction1 event: x=%d, y=%d, w=%d, h=%d\n", x, y, w, h);
}  //2

static const struct llp_interface_listener my_listener = {
    on_function1,
}; //3

static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {

  printf("%s\n",interface);
  //printf("haha");
  if (strcmp(interface, "llp_interface") == 0) {
    printf("%s\n",interface);
    my_interface = wl_registry_bind(registry, id, &llp_interface_interface, version);
    llp_interface_add_listener(my_interface, &my_listener, NULL);
  }//4
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name) {
  // This space intentionally left blank
}

static const struct wl_registry_listener registry_listener = {
    registry_handle_global,
    registry_handle_global_remove,
};

int main(int argc, char **argv) {
  struct wl_display *display;
  struct wl_registry *registry;

  display = wl_display_connect("wayland-0");
  if (display == NULL) {
    fprintf(stderr, "Cannot connect to Wayland display\n");
    exit(EXIT_FAILURE);
  }
  printf("1\n");
  registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, NULL);

  wl_display_dispatch(display);

  // Here you should have your my_interface bound if it's available
  // Now you can use function1
  llp_interface_function1(my_interface, 10, 20, 30, 40);//5

  //wl_display_roundtrip(display);
  while (wl_display_dispatch(display))
  {
    
  }
  wl_display_disconnect(display);
  return 0;
}
```

代码中1，2，3，4为加入协议，5为调用。

1-4 服务器移移植：

server.c

```c
#include <wayland-server.h>
#include "my_protocol-server-protocol.h"
#include <stdio.h>
// 定义您的 compositor 接口的函数
static void compositor_create_surface(struct wl_client *client, struct wl_resource *resource, uint32_t id) {
    // 在这里实现创建 surface 的逻辑
}

static void compositor_create_region(struct wl_client *client, struct wl_resource *resource, uint32_t id) {
    // 在这里实现创建 region 的逻辑
}

// 创建 compositor 接口的实现结构体
static const struct wl_compositor_interface compositor_interface = {
    .create_surface = compositor_create_surface,
    .create_region = compositor_create_region,
};

// 当客户端 bind wl_compositor 时调用此函数
static void bind_compositor(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
    struct wl_resource *resource = wl_resource_create(client, &wl_compositor_interface, version, id);
    wl_resource_set_implementation(resource, &compositor_interface, data, NULL);
}
/*1*/
static void my_function1(struct wl_client *client, struct wl_resource *resource, int32_t x, int32_t y, int32_t w, int32_t h) {
  printf("Function1 called with x=%d, y=%d, w=%d, h=%d\n", x, y, w, h);
  // 假设我们需要响应客户端
   /*2*/
  llp_interface_send_onfunction1(resource, x, y, w, h);
}

// 这个结构体定义了接口的实现，它包含了接口中函数的实际实现
static const struct llp_interface_interface my_implementation = {
    my_function1,
};//3

// 当客户端请求创建一个 my_interface 实例时调用此函数
static void bind_my_interface(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
  struct wl_resource *resource;

  // 创建一个新的资源实例
  resource = wl_resource_create(client, &llp_interface_interface, version, id);

  // 将我们的实现与新创建的资源关联起来
  wl_resource_set_implementation(resource, &my_implementation, NULL, NULL);
}// ---------4

int main(int argc, char **argv) {
  struct wl_display *display;
  struct wl_event_loop *event_loop;
  struct wl_global *global;

  // 创建 Wayland display
  display = wl_display_create();
  printf("1\n");
  // 获取 Wayland event loop
  event_loop = wl_display_get_event_loop(display);

  // 添加我们的扩展协议到 Wayland registry
  //global = ewl_global_creat(display, &my_interface_interface, 1, NULL, bind_my_interface);
  wl_global_create(display,&wl_compositor_interface,4,NULL,bind_compositor);
  wl_global_create(display, &llp_interface_interface, 1, NULL, bind_my_interface);//------5

  // 启动 Wayland 服务端
  if (wl_display_add_socket(display, "wayland-1")) {
    //fprintf(stderr, "Failed to add Wayland display socket\n");
    return -1;
  }

  // 进入主事件循环
  //fprintf(stderr, "Entering Wayland event loop\n");
  printf("wait~\n");
  wl_event_loop_dispatch(event_loop, -1);
  wl_display_run(display);//good
  //wl_event_loop_dispatch(event_loop, -1);

  // 清理资源
 // wl_global_destroy(global);
  wl_display_destroy(display);

  return 0;
}
```

1,2,3是wayland服务器的经典操作。4是5需要的一个接口，作用是创建并实现并关联新资源。5将变量设置为像wl_compositer一样的全局变量，之后，客户端可以注册这个变量。



注意函数名关系

 <interface name="llp_interface" version="1">
   <request name="function1">

 <event name="onfunction1">

客户端调用函数为llp_interface_function1,服务器响应这个函数，

服务器调用函数为 llp_interface_send_onfunction1，客户端响应这个函数。

具体过程如下：

client ------>llp_interface_function1(my_interface, 10, 20, 30, 40)----->server

---->static const struct llp_interface_interface my_implementation = {my_function1,};

static void my_function1(struct wl_client *client, struct wl_resource *resource, int32_t x, int32_t y, int32_t w, int32_t h) {
printf("Function1 called with x=%d, y=%d, w=%d, h=%d\n", x, y, w, h);

响应客户端
 llp_interface_send_onfunction1(resource, x, y, w, h);

}

------->client

static const struct llp_interface_listener my_listener = {on_function1,};

static void on_function1(void *data, struct llp_interface *my_interface, int32_t x, int32_t y, int32_t w, int32_t h) {printf("onfunction1 event: x=%d, y=%d, w=%d, h=%d\n", x, y, w, h);}

