#!/usr/bin/env bash
# Copyright 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

# Simple COAP test, consisting of:
# a COAP servers device with "light" resources;
# and a COAP client, which will command it
#
# This test is based on the openthread/coap_{client,server} samples
# Note: Currently this test does not check for anything, it simply executes
# TODO: actually test for something

simulation_id="coap_test"
verbosity_level=2
EXECUTE_TIMEOUT=100

source ${ZEPHYR_BASE}/tests/bsim/sh_common.source

cd ${BSIM_OUT_PATH}/bin

Execute ./bs_${BOARD}_tests_bsim_samples_openthread_coap_client_prj_conf_multiprotocol_ble \
 -s=${simulation_id} -v=${verbosity_level} -d=0 -RealEncryption=1 -testid=coap_client

Execute ./bs_${BOARD}_tests_bsim_samples_openthread_coap_server_prj_conf \
 -s=${simulation_id} -v=${verbosity_level} -d=1 -RealEncryption=1 -testid=coap_server

Execute ./bs_2G4_phy_v1 -v=${verbosity_level} -s=${simulation_id} \
  -D=2 -sim_length=60e6 -argschannel -at=40 -argsmain $@

wait_for_background_jobs #Wait for all programs in background and return != 0 if any fails
