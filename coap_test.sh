#!/usr/bin/env bash

# Build the applications as
# coap client and NUS server: 
#   mkdir build ; cd build ;  
#   cmake ../samples/openthread/coap_client/ -DBOARD=nrf52_bsim -GNinja -DOVERLAY_CONFIG="overlay-multiprotocol_ble.conf"
#   ninja
# coap server: 
#   mkdir build2 ; cd build2 ;  
#   cmake ../samples/openthread/coap_server/ -DBOARD=nrf52_bsim -GNinja
#   ninja
# BT NUS client 
#   mkdir build3 ; cd build3 ;  
#   cmake ../samples/bluetooth/bsim_nus_client/ -DBOARD=nrf52_bsim -GNinja 
#   ninja
# Then you can run them together with this silly script:

cp build/zephyr/zephyr.exe ${BSIM_OUT_PATH}/bin/coap_client.exe
cp build2/zephyr/zephyr.exe ${BSIM_OUT_PATH}/bin/coap_server.exe
cp build3/zephyr/zephyr.exe ${BSIM_OUT_PATH}/bin/bt_nus_client.exe

cd ${BSIM_OUT_PATH}/bin

if [ "1" == "0" ]; then
  # Run with the COAP client driven from the test code which pretends to press buttons 
  ./coap_client.exe -s=coap -d=0 -RealEncryption=1 -testid=coap_client & 
  ./coap_server.exe -s=coap -d=1 -RealEncryption=1 -testid=coap_server &
  ./bs_2G4_phy_v1 -s=coap -D=2 -sim_length=60e6 -v=2 -argschannel -at=40 
fi

if [ "0" == "0" ]; then
  # Run with the COAP client driven from the NUS client
  ./bt_nus_client.exe -s=coap -d=0 -RealEncryption=1 -testid=drive_coap_client &
  ./coap_client.exe -s=coap -d=1 -RealEncryption=1 & #Note here we run the COAP client without a test injecting button presses
  ./coap_server.exe -s=coap -d=2 -RealEncryption=1 -testid=coap_server &
  ./coap_server.exe -s=coap -d=3 -RealEncryption=1 -testid=coap_server &
  ./bs_2G4_phy_v1 -s=coap -D=4 -sim_length=60e6 -v=2 -argschannel -at=40 
fi

# You can get a pcap trace of the radio activity with: 
# ${BSIM_COMPONENTS_PATH}/ext_2G4_phy_v1/dump_post_process/csv2pcap_15.4.py ${BSIM_OUT_PATH}/results/coap/d_2G4_0*.Tx.csv -o bsim_trace.pcap
