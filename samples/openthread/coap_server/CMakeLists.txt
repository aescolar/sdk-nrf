#
# Copyright (c) 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(openthread_coap_server)

# NORDIC SDK APP START
target_sources(app PRIVATE src/coap_server.c
			   src/ot_coap_utils.c)

target_include_directories(app PRIVATE interface)
# NORDIC SDK APP END

if (DEFINED CONFIG_BOARD_NRF52_BSIM)
  target_sources(app PRIVATE src/test_server.c
    ../coap_client/src/bsim_dk_buttons_and_leds.c
  )

  zephyr_include_directories(
    $ENV{BSIM_COMPONENTS_PATH}/libUtilv1/src/
  )
endif()
