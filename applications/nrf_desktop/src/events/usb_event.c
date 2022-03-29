/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <assert.h>
#include <sys/util.h>
#include <stdio.h>

#include "usb_event.h"


static const char * const state_name[] = {
	[USB_STATE_DISCONNECTED] = "DISCONNECTED",
	[USB_STATE_POWERED]      = "POWERED",
	[USB_STATE_ACTIVE]       = "ACTIVE",
	[USB_STATE_SUSPENDED]    = "SUSPENDED"
};

static void log_usb_state_event(const struct application_event_header *aeh)
{
	const struct usb_state_event *event = cast_usb_state_event(aeh);

	BUILD_ASSERT(ARRAY_SIZE(state_name) == USB_STATE_COUNT,
			 "Invalid number of elements");

	__ASSERT_NO_MSG(event->state < USB_STATE_COUNT);

	APPLICATION_EVENT_MANAGER_LOG(aeh, "state:%s", state_name[event->state]);
}

APPLICATION_EVENT_TYPE_DEFINE(usb_state_event,
		  log_usb_state_event,
		  NULL,
		  APPLICATION_EVENT_FLAGS_CREATE(
			IF_ENABLED(CONFIG_DESKTOP_INIT_LOG_USB_STATE_EVENT,
				(APPLICATION_EVENT_TYPE_FLAGS_INIT_LOG_ENABLE))));

static void log_usb_hid_event(const struct application_event_header *aeh)
{
	const struct usb_hid_event *event = cast_usb_hid_event(aeh);

	APPLICATION_EVENT_MANAGER_LOG(aeh, "id:%p %sabled", event->id,
			(event->enabled)?("en"):("dis"));
}

APPLICATION_EVENT_TYPE_DEFINE(usb_hid_event,
		  log_usb_hid_event,
		  NULL,
		  APPLICATION_EVENT_FLAGS_CREATE(
			IF_ENABLED(CONFIG_DESKTOP_INIT_LOG_USB_HID_EVENT,
				(APPLICATION_EVENT_TYPE_FLAGS_INIT_LOG_ENABLE))));
