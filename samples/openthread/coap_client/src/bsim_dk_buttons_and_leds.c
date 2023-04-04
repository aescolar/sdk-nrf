/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief Quick replacement for the DK buttons/LED interface for simulation
 */

#include <stdint.h>
#include "bs_types.h"
#include "bs_tracing.h"
#include "bs_utils.h"
#include <dk_buttons_and_leds.h>

#define N_LEDS 32
#define N_BUTTONS 32
static bool leds_status[N_LEDS];
static bool button_status[N_LEDS];
static uint32_t button_mask;
static char *on_string[2] = {"OFF", "ON"};
static button_handler_t button_handler_cb = NULL;

int dk_set_led(uint8_t led_idx, uint32_t val){
	val = BS_MIN(val,1);
	led_idx = BS_MIN(led_idx,N_LEDS-1);
	bs_trace_info_time(2, "LED %i %s->%s\n", led_idx,
			   on_string[leds_status[led_idx]],
			   on_string[val]);
	leds_status[led_idx] = val;
	return 0;
}

int dk_set_led_on(uint8_t led_idx)
{
	return dk_set_led(led_idx, true);
}

int dk_set_led_off(uint8_t led_idx)
{
	return dk_set_led(led_idx, false);
}

int dk_buttons_init(button_handler_t button_handler){
	button_handler_cb = button_handler;
	return 0;
}

int dk_leds_init(void){
	//Purposefully left empty
	return 0;
}

/**
 * Pretend to press a DK button (note <button> is indexed from 0)
 */
void fake_button_press(int button){
	button = BS_MIN(button, N_BUTTONS-1);
	uint32_t bit_mask = 1<<button;
	uint32_t change_mask = 0;

	if ((button_mask & bit_mask) == 0) {
		change_mask = bit_mask;
	}
	button_mask |= bit_mask;

	bs_trace_info_time(2, "Button %i pressed, was %s\n", button+1,
			   on_string[button_status[button]]);
	button_status[button] = true;

	if (button_handler_cb) {
		button_handler_cb(button_mask, change_mask);
	}
}

/**
 * Pretend to release a DK button (note <button> is indexed from 0)
 */
void fake_button_release(int button){
	button = BS_MIN(button, N_BUTTONS-1);
	uint32_t bit_mask = 1<<button;
	uint32_t change_mask = 0;

	if (button_mask & bit_mask) {
		change_mask = bit_mask;
	}
	button_mask &= ~bit_mask;

	bs_trace_info_time(2, "Button %i released, was %s\n", button+1,
			   on_string[button_status[button]]);
	button_status[button] = false;

	if (button_handler_cb) {
		button_handler_cb(button_mask, change_mask);
	}
}
