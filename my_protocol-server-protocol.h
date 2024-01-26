/* Generated by wayland-scanner 1.20.0 */

#ifndef MY_EXTENSION_SERVER_PROTOCOL_H
#define MY_EXTENSION_SERVER_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-server.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_client;
struct wl_resource;

/**
 * @page page_my_extension The my_extension protocol
 * @section page_ifaces_my_extension Interfaces
 * - @subpage page_iface_my_interface - 
 */
struct my_interface;

#ifndef MY_INTERFACE_INTERFACE
#define MY_INTERFACE_INTERFACE
/**
 * @page page_iface_my_interface my_interface
 * @section page_iface_my_interface_api API
 * See @ref iface_my_interface.
 */
/**
 * @defgroup iface_my_interface The my_interface interface
 */
extern const struct wl_interface my_interface_interface;
#endif

/**
 * @ingroup iface_my_interface
 * @struct my_interface_interface
 */
struct my_interface_interface {
	/**
	 */
	void (*function1)(struct wl_client *client,
			  struct wl_resource *resource,
			  int32_t x,
			  int32_t y,
			  int32_t w,
			  int32_t h);
};

#define MY_INTERFACE_ONFUNCTION1 0

/**
 * @ingroup iface_my_interface
 */
#define MY_INTERFACE_ONFUNCTION1_SINCE_VERSION 1

/**
 * @ingroup iface_my_interface
 */
#define MY_INTERFACE_FUNCTION1_SINCE_VERSION 1

/**
 * @ingroup iface_my_interface
 * Sends an onfunction1 event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
my_interface_send_onfunction1(struct wl_resource *resource_, int32_t x, int32_t y, int32_t w, int32_t h)
{
	wl_resource_post_event(resource_, MY_INTERFACE_ONFUNCTION1, x, y, w, h);
}

#ifdef  __cplusplus
}
#endif

#endif