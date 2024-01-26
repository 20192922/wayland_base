#include <wayland-server.h>
#include <stdlib.h>
#include <stdio.h>

static void bind_compositor(struct wl_client *client, void *data,
                            uint32_t version, uint32_t id) {
    // 这里将实现wl_compositor接口的绑定逻辑
    // ...
    printf("Compositor bound to client\n");
}

static void bind_registry(struct wl_client *client, void *data,
                            uint32_t version, uint32_t id) {
    // 这里将实现wl_registry接口的绑定逻辑
    // ...
    printf("Registry bound to client\n");
}

int main(int argc, char *argv[]) {
    struct wl_display *display;
    struct wl_global *compositor_global, *registry_global;

    display = wl_display_create();
    if (display == NULL) {
        fprintf(stderr, "Cannot create Wayland display\n");
        return -1;
    }

    // 创建wl_compositor全局对象
    compositor_global = wl_global_create(display, &wl_compositor_interface, 4, NULL, bind_compositor);
    if (compositor_global == NULL) {
        fprintf(stderr, "Cannot create wl_compositor global\n");
        wl_display_destroy(display);
        return -1;
    }

    // 创建wl_registry全局对象
    registry_global = wl_global_create(display, &wl_registry_interface, 1, NULL, bind_registry);
    if (registry_global == NULL) {
        fprintf(stderr, "Cannot create wl_registry global\n");
        wl_display_destroy(display);
        return -1;
    }

    // 现在可以启动Wayland服务器，监听连接
    if (wl_display_add_socket(display, NULL)) {
        fprintf(stderr, "Failed to add socket to Wayland display\n");
        wl_display_destroy(display);
        return -1;
    }

    printf("Wayland display running\n");

    // 进入Wayland事件循环
    while (1) {
        wl_display_flush_clients(display);
        //wl_display_dispatch(display);
    }

    // 清理资源
    wl_display_destroy(display);
    return 0;
}