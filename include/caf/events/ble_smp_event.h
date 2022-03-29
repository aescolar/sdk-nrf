/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _BLE_SMP_EVENT_H_
#define _BLE_SMP_EVENT_H_

/**
 * @brief Bluetooth LE SMP Event
 * @defgroup ble_smp_event Bluetooth LE SMP Event
 * @{
 */

#include <app_evt_mgr.h>
#include <app_evt_mgr_profiler_tracer.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Bluetooth LE SMP transfer event. */
struct ble_smp_transfer_event {
	struct application_event_header header;
};
APPLICATION_EVENT_TYPE_DECLARE(ble_smp_transfer_event);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _BLE_SMP_EVENT_H_ */
