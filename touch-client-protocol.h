/* Generated by wayland-scanner 1.19.0 */

#ifndef LLP_TOUCH_EXTENSION_CLIENT_PROTOCOL_H
#define LLP_TOUCH_EXTENSION_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_llp_touch_extension The llp_touch_extension protocol
 * @section page_ifaces_llp_touch_extension Interfaces
 * - @subpage page_iface_llp_touch - LLP add to deliver touch information
 */
struct llp_touch;

#ifndef LLP_TOUCH_INTERFACE
#define LLP_TOUCH_INTERFACE
/**
 * @page page_iface_llp_touch llp_touch
 * @section page_iface_llp_touch_desc Description
 *
 * The llp_touch interface is exposed as a global object enabling clients
 * to deliver touch information from server to client.
 * @section page_iface_llp_touch_api API
 * See @ref iface_llp_touch.
 */
/**
 * @defgroup iface_llp_touch The llp_touch interface
 *
 * The llp_touch interface is exposed as a global object enabling clients
 * to deliver touch information from server to client.
 */
extern const struct wl_interface llp_touch_interface;
#endif

#ifndef LLP_TOUCH_TOUCH_EVENT_ENUM
#define LLP_TOUCH_TOUCH_EVENT_ENUM
enum llp_touch_Touch_event {
	/**
	 * one
	 */
	LLP_TOUCH_TOUCH_EVENT_ONE_CLICK = 0,
	/**
	 * pinch_in
	 */
	LLP_TOUCH_TOUCH_EVENT_PINCH_IN = 1,
	/**
	 * pinch_out
	 */
	LLP_TOUCH_TOUCH_EVENT_PINCH_OUT = 2,
	/**
	 * swipe_lift
	 */
	LLP_TOUCH_TOUCH_EVENT_SWIPE_LIFT = 3,
	/**
	 * swipe_right
	 */
	LLP_TOUCH_TOUCH_EVENT_SWIPE_RIGHT = 4,
	/**
	 * swipe_up
	 */
	LLP_TOUCH_TOUCH_EVENT_SWIPE_UP = 5,
	/**
	 * swipe_down
	 */
	LLP_TOUCH_TOUCH_EVENT_SWIPE_DOWN = 6,
	/**
	 * double
	 */
	LLP_TOUCH_TOUCH_EVENT_DOUBLE_CLICK = 7,
};
#endif /* LLP_TOUCH_TOUCH_EVENT_ENUM */

/**
 * @ingroup iface_llp_touch
 * @struct llp_touch_listener
 */
struct llp_touch_listener {
	/**
	 * send_touch_event
	 *
	 * send_touch_event
	 */
	void (*message_to_client)(void *data,
				  struct llp_touch *llp_touch,
				  int32_t x,
				  int32_t y,
				  int32_t w,
				  int32_t h,
				  int32_t touch_event);
};

/**
 * @ingroup iface_llp_touch
 */
static inline int
llp_touch_add_listener(struct llp_touch *llp_touch,
		       const struct llp_touch_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) llp_touch,
				     (void (**)(void)) listener, data);
}

#define LLP_TOUCH_GET_TOUCH_EVENT 0

/**
 * @ingroup iface_llp_touch
 */
#define LLP_TOUCH_MESSAGE_TO_CLIENT_SINCE_VERSION 1

/**
 * @ingroup iface_llp_touch
 */
#define LLP_TOUCH_GET_TOUCH_EVENT_SINCE_VERSION 1

/** @ingroup iface_llp_touch */
static inline void
llp_touch_set_user_data(struct llp_touch *llp_touch, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) llp_touch, user_data);
}

/** @ingroup iface_llp_touch */
static inline void *
llp_touch_get_user_data(struct llp_touch *llp_touch)
{
	return wl_proxy_get_user_data((struct wl_proxy *) llp_touch);
}

static inline uint32_t
llp_touch_get_version(struct llp_touch *llp_touch)
{
	return wl_proxy_get_version((struct wl_proxy *) llp_touch);
}

/** @ingroup iface_llp_touch */
static inline void
llp_touch_destroy(struct llp_touch *llp_touch)
{
	wl_proxy_destroy((struct wl_proxy *) llp_touch);
}

/**
 * @ingroup iface_llp_touch
 *
 * get_touch_event
 */
static inline void
llp_touch_get_touch_event(struct llp_touch *llp_touch, int32_t x, int32_t y, int32_t w, int32_t h, int32_t touch_event)
{
	wl_proxy_marshal((struct wl_proxy *) llp_touch,
			 LLP_TOUCH_GET_TOUCH_EVENT, x, y, w, h, touch_event);
}

#ifdef  __cplusplus
}
#endif

#endif
