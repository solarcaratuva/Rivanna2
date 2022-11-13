# Based on output in output/log_<time>.json, create plots of power and RPM over time

import json
import sys

import matplotlib.pyplot as plt
import numpy as np


def create_plots(data):
    bps = data['bps']
    motor = data['motor']
    
    # Create power plot
    bps_timestamps = [x['timestamp'] for x in bps]
    bps_currents = np.array([x['pack_current'] for x in bps]) # amps
    bps_voltages = np.array([x['pack_voltage'] for x in bps]) / 100 # mv/10 = volts * 100
    power = bps_currents * bps_voltages

    motor_timestamps = [x['timestamp'] for x in motor]
    motor_rpms = np.array([x['motor_rpm'] for x in motor])

    fig, ax = plt.subplots(2, 1, sharex=True)
    ax[0].plot(bps_timestamps, power)
    ax[0].set_ylabel('Power (W)')
    ax[1].plot(motor_timestamps, motor_rpms)
    ax[1].set_ylabel('RPM')
    ax[1].set_xlabel('Time (s)')
    plt.savefig('power_rpm.png')
    # plt.show()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 analyze_power.py <log_file>")
        exit(1)

    log_file = sys.argv[1]
    with open(log_file, 'r') as f:
        data = json.load(f)
    create_plots(data)
