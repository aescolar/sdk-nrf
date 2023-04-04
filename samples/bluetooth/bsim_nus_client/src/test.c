/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include "bs_types.h"
#include "bs_tracing.h"
#include "time_machine.h"
#include "bstests.h"
#include "bs_utils.h"
#include <zephyr/kernel.h>

extern enum bst_result_t bst_result;

static void test_nus_client_init(void)
{
	/*
	 * We aren't really testing anything => we just claim we pass
	 * so it does not appear as a failed test
	 */
	bst_result = Passed;
}

K_THREAD_STACK_DEFINE(test_thread_stack, 256);
struct k_thread test_nus_thread;

void feed_nus_data(char *c, size_t len);

static void drive_coap_client_thread(void *a, void *b, void *c){
	ARG_UNUSED(a);
	ARG_UNUSED(b);
	ARG_UNUSED(c);

	k_sleep(K_SECONDS(10));
	/* Request the COAP client to send a multicast light toggle request */
	feed_nus_data("m\r",2);
	k_sleep(K_SECONDS(20));
	/* Request the COAP client to pair */
	feed_nus_data("p\r",2);
	/* Request the COAP client to send a unicast light toggle request */
	k_sleep(K_SECONDS(5));
	feed_nus_data("u\r",2);
}

static void test_drive_coap_post_kernel(void)
{
	k_thread_create(&test_nus_thread, test_thread_stack,
			K_THREAD_STACK_SIZEOF(test_thread_stack),
			drive_coap_client_thread,
			NULL, NULL, NULL,
			1, 0, K_NO_WAIT);
}

static const struct bst_test_instance drive_coap_client[] = {
	{
		.test_id = "drive_coap_client",
		.test_descr = "Companion for the COAP client/server samples "
			"tests which connect to a BT NUS server (the COAP "
			"client) and send it a few request",
		.test_post_init_f = test_nus_client_init,
		.test_fake_ddriver_postkernel_f = test_drive_coap_post_kernel,
	},
	BSTEST_END_MARKER
};

struct bst_test_list *test_drive_coap_client_install(struct bst_test_list *tests)
{
	tests = bst_add_tests(tests, drive_coap_client);
	return tests;
}

bst_test_install_t test_installers[] = {
	test_drive_coap_client_install,
	NULL
};
