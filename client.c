#include <stdio.h>
#include <stdlib.h>
#include <wayland-client.h>
#include "my_protocol-client-protocol.h"
#include <string.h>
struct llp_interface *my_interface;
/*创建这个监听结构体，以便服务器回调。wayland的通信方式，*/
static void on_function1(void *data, struct llp_interface *my_interface, int32_t x, int32_t y, int32_t w, int32_t h) {
  printf("onfunction1 event: x=%d, y=%d, w=%d, h=%d\n", x, y, w, h);
}

static const struct llp_interface_listener my_listener = {
    on_function1,
};

static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
 
  printf("%s\n",interface);
  //printf("haha");
  if (strcmp(interface, "llp_interface") == 0) {
    printf("%s\n",interface);
    my_interface = wl_registry_bind(registry, id, &llp_interface_interface, version);
    llp_interface_add_listener(my_interface, &my_listener, NULL);
  }
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
  llp_interface_function1(my_interface, 10, 20, 30, 40);

  //wl_display_roundtrip(display);
  while (wl_display_dispatch(display))
  {
    
  }
  wl_display_disconnect(display);
  return 0;
}