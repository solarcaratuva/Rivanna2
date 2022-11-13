# Based on output in output/log_<time>.json, create plots of power and RPM over time

import json
import sys

import matplotlib.pyplot as plt
import numpy as np


def create_plots(data, output_file):
    bps = data['bps']
    motor = data['motor']
    
    # Create power plot
    bps_timestamps = np.array([x['timestamp'] for x in bps])
    bps_currents = np.array([x['pack_current'] for x in bps]) # amps
    bps_voltages = np.array([x['pack_voltage'] for x in bps]) / 10000 # mv/10 = volts * 100
    power = bps_currents * bps_voltages

    motor_timestamps = [x['timestamp'] for x in motor]
    motor_rpms = np.array([x['motor_rpm'] for x in motor])

    fig, ax = plt.subplots(2, 1, sharex=True)
    ax[0].plot(bps_timestamps, power)
    ax[0].set_ylabel('Power (W)')
    ax[1].plot(motor_timestamps, motor_rpms)
    ax[1].set_ylabel('RPM')
    ax[1].set_xlabel('Time (s)')
    plt.savefig(output_file + "_power.png")
    
    # Create energy plot
    # Energy = integral of power.
    energy = np.cumsum(power[1:] * (bps_timestamps[1:] - bps_timestamps[:-1]))
    timestamp = (bps_timestamps[1:] + bps_timestamps[:-1]) / 2

    plt.clf()
    fig, ax = plt.subplots(2, 1, sharex=True)
    ax[0].plot(timestamp, energy)
    ax[0].set_ylabel('Energy (J)')
    ax[1].plot(motor_timestamps, motor_rpms)
    ax[1].set_ylabel('RPM')
    ax[1].set_xlabel('Time (s)')
    plt.savefig(output_file + "_energy.png")

    recovered_by_regen = np.max(energy) - energy[-1]
    print(f"Recovered by regen: {recovered_by_regen:.2f} J (recovery = {recovered_by_regen / np.max(energy) * 100:.2f}%) (max used: {np.max(energy):.2f} J; total used: {energy[-1]:.2f} J)")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 analyze_power.py <log_file>")
        exit(1)

    log_file = sys.argv[1]
    with open(log_file, 'r') as f:
        data = json.load(f)
    create_plots(data, log_file.replace(".json", ""))
