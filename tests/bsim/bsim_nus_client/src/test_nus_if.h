/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef TESTS_BSIM_BSIM_NUS_CLIENT_SRC_NUS_IF_H
#define TESTS_BSIM_BSIM_NUS_CLIENT_SRC_NUS_IF_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void feed_nus_data(char *c, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* TESTS_BSIM_BSIM_NUS_CLIENT_SRC_NUS_IF_H */
