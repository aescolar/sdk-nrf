# Copyright (c) 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(test_openthread_coap_client)

set(sample_path ${NRF_DIR}/samples/openthread/coap_client)

target_sources(app PRIVATE
  ${sample_path}/src/coap_client.c
  ${sample_path}/src/coap_client_utils.c
  ${sample_path}/src/ble_utils.c
)

target_include_directories(app PUBLIC ${sample_path}/../coap_server/interface)

target_sources(app PRIVATE src/bsim_test_client.c
  src/bsim_dk_buttons_and_leds.c
)

zephyr_include_directories(
  $ENV{BSIM_COMPONENTS_PATH}/libUtilv1/src/
)
