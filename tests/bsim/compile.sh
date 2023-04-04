#!/usr/bin/env bash
# Copyright 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

# Compile all the applications needed by all bsim tests

#set -x #uncomment this line for debugging
set -ue

: "${BSIM_OUT_PATH:?BSIM_OUT_PATH must be defined}"
: "${BSIM_COMPONENTS_PATH:?BSIM_COMPONENTS_PATH must be defined}"
: "${ZEPHYR_BASE:?ZEPHYR_BASE must be set to point to the zephyr root\
 directory}"

NRF_BASE="${NRF_BASE:-${ZEPHYR_BASE}/../nrf}"
WORK_DIR="${WORK_DIR:-${ZEPHYR_BASE}/bsim_out}"
BOARD="${BOARD:-nrf52_bsim}"
BOARD_ROOT="${BOARD_ROOT:-${ZEPHYR_BASE}}"
app_root=${NRF_BASE}

mkdir -p ${WORK_DIR}

source ${ZEPHYR_BASE}/tests/bsim/compile.source

run_in_background ${NRF_BASE}/tests/bsim/samples/compile.sh

app=tests/bsim/bsim_nus_client compile

wait_for_background_jobs
