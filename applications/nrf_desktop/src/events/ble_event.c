/*
 * Copyright (c) 2018-2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <assert.h>
#include <sys/util.h>
#include <stdio.h>

#include "ble_event.h"

#define BLE_EVENT_LOG_BUF_LEN 128

APPLICATION_EVENT_TYPE_DEFINE(ble_discovery_complete_event,
		  NULL,
		  NULL,
		  APPLICATION_EVENT_FLAGS_CREATE(
			IF_ENABLED(CONFIG_DESKTOP_INIT_LOG_BLE_DISC_COMPLETE_EVENT,
				(APPLICATION_EVENT_TYPE_FLAGS_INIT_LOG_ENABLE))));


#if CONFIG_DESKTOP_BLE_QOS_ENABLE
static void log_ble_qos_event(const struct application_event_header *aeh)
{
	const struct ble_qos_event *event = cast_ble_qos_event(aeh);
	int pos = 0;
	char log_buf[BLE_EVENT_LOG_BUF_LEN];
	int err;

	err = snprintf(&log_buf[pos], sizeof(log_buf) - pos, "chmap:");
	for (size_t i = 0; (i < CHMAP_BLE_BITMASK_SIZE) && (err > 0); i++) {
		pos += err;
		err = snprintf(&log_buf[pos], sizeof(log_buf) - pos, " 0x%02x", event->chmap[i]);
	}
	if (err < 0) {
		APPLICATION_EVENT_MANAGER_LOG(aeh, "log message preparation failure");
		return;
	}
	APPLICATION_EVENT_MANAGER_LOG(aeh, "%s", log_strdup(log_buf));
}

APPLICATION_EVENT_TYPE_DEFINE(ble_qos_event,
		  log_ble_qos_event,
		  NULL,
		  APPLICATION_EVENT_FLAGS_CREATE(
			IF_ENABLED(CONFIG_DESKTOP_INIT_LOG_BLE_QOS_EVENT,
				(APPLICATION_EVENT_TYPE_FLAGS_INIT_LOG_ENABLE))));
#endif
