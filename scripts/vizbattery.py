"""
00:17:08 INFO /root/RivannaWorkshop/Common/include/BPSCANStructs.h:28: BPSPackInformation: pack_voltage 10808, pack_current 0, pack_soc 40, discharge_relay_status 0, charge_relay_status 1, charger_safety_status 0, dtc_status 0, multipurpose_input_signal_status 0, always_on_signal_status 1, is_ready_signal_status 1, is_charging_signal_status 0
"""

import sys

def update_progress(pack_voltage, pack_current):
    sys.stdout.write(f"\rPack Voltage: {pack_voltage} ?V    Pack Current: {pack_current} ?A")

while True:
    x = input()
    if "BPSPackInformation" not in x:
        continue
    x = x.split(" ")
    v, c = int(x[5][:-1]), int(x[7][:-1])
    update_progress(v, c)
