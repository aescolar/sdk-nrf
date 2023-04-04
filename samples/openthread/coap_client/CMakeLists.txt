#
# Copyright (c) 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(openthread_coap_client)

# NORDIC SDK APP START
target_sources(app PRIVATE src/coap_client.c
			   src/coap_client_utils.c)

target_include_directories(app PUBLIC ../coap_server/interface)
# NORDIC SDK APP END

target_sources_ifdef(CONFIG_BT_NUS app PRIVATE src/ble_utils.c)


if (DEFINED CONFIG_BOARD_NRF52_BSIM)
  target_sources(app PRIVATE src/bsim_test_client.c
    src/bsim_dk_buttons_and_leds.c
  )

  zephyr_include_directories(
    $ENV{BSIM_COMPONENTS_PATH}/libUtilv1/src/
  )
endif()
