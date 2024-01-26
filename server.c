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
static void my_function1(struct wl_client *client, struct wl_resource *resource, int32_t x, int32_t y, int32_t w, int32_t h) {
  // 这里处理您的业务逻辑。例如，保存这些参数或者更改窗口的大小等。
  printf("Function1 called with x=%d, y=%d, w=%d, h=%d\n", x, y, w, h);

  // 假设我们需要响应客户端
  my_interface_send_onfunction1(resource, x, y, w, h);
}

// 这个结构体定义了接口的实现，它包含了接口中函数的实际实现
static const struct my_interface_interface my_implementation = {
    my_function1,
};

// 当客户端请求创建一个 my_interface 实例时调用此函数
static void bind_my_interface(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
  struct wl_resource *resource;

  // 创建一个新的资源实例
  resource = wl_resource_create(client, &my_interface_interface, version, id);

  // 将我们的实现与新创建的资源关联起来
  wl_resource_set_implementation(resource, &my_implementation, NULL, NULL);
}

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
  wl_global_create(display, &my_interface_interface, 1, NULL, bind_my_interface);

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