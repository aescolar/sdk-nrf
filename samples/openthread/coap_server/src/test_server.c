/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include "bstests.h"
#include <dk_buttons_and_leds.h>
#include <zephyr/kernel.h>

extern enum bst_result_t bst_result;

static void test_coap_server_init(void)
{
	/*
	 * We aren't really testing anything => we just claim we pass
	 * so it does not appear as a failed test
	 */
	bst_result = Passed;
}

void fake_button_press(int button);
void fake_button_release(int button);

K_THREAD_STACK_DEFINE(test_thread_stack, 256);
struct k_thread test_server_thread;

/**
 * A thread that injects a few "button presses"
 * as if an operator was driving the test
 */
static void test_thread_entry(void *a, void *b, void *c){
	ARG_UNUSED(a);
	ARG_UNUSED(b);
	ARG_UNUSED(c);

	k_sleep(K_SECONDS(30));
	/* Go into pairing mode */
	fake_button_press(3);
	k_sleep(K_MSEC(50));
	fake_button_release(3);
}

static void test_coap_server_post_kernel(void)
{
	k_thread_create(&test_server_thread, test_thread_stack,
			K_THREAD_STACK_SIZEOF(test_thread_stack),
			test_thread_entry,
			NULL, NULL, NULL,
			1, 0, K_NO_WAIT);
}

static const struct bst_test_instance test_coap_server[] = {
	{
		.test_id = "coap_server",
		.test_descr = "COAP server 'test'. It pretends to press"
			"a DK buttons, to switch into pairing mode ",
		.test_post_init_f = test_coap_server_init,
		.test_fake_ddriver_postkernel_f = test_coap_server_post_kernel,
	},
	BSTEST_END_MARKER
};

struct bst_test_list *test_coap_server_install(struct bst_test_list *tests)
{
	tests = bst_add_tests(tests, test_coap_server);
	return tests;
}

bst_test_install_t test_installers[] = {
	test_coap_server_install,
	NULL
};
