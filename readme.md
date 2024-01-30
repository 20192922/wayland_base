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
