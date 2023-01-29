# First, create output by running `sh monitor.sh | python scripts/dash.py` when connected to the PowerAux board.
# Then, based on output in output/log_<time>.json, create plots of power and RPM over time

import json
import sys

import matplotlib.pyplot as plt
import numpy as np


def create_plots(data, output_file):
    bps = data['bps']
    motor = data['motor']
    pedal = data.get('pedal', [])
    motor_commands = data['motor_commands']
    
    # Create power plot
    bps_timestamps = np.array([x['timestamp'] for x in bps])
    bps_currents = np.array([x['pack_current'] for x in bps]) # amps
    bps_voltages = np.array([x['pack_voltage'] for x in bps]) / 10000 # mv/10 = volts * 100
    power = bps_currents * bps_voltages
    throttle = np.array([x['throttle'] for x in motor_commands]) / 100 # percent
    regen = np.array([x['regen'] for x in motor_commands]) / 100 # percent
    mc_timestamps = np.array([x['timestamp'] for x in motor_commands])

    motor_timestamps = [x['timestamp'] for x in motor]
    motor_rpms = np.array([x['motor_rpm'] for x in motor])

    # Energy = integral of power.
    energy = np.cumsum(power[1:] * (bps_timestamps[1:] - bps_timestamps[:-1]))
    energy_timestamps = (bps_timestamps[1:] + bps_timestamps[:-1]) / 2

    fig, (ax_power, ax_energy, ax_rpm, ax_throttle) = plt.subplots(4, 1, sharex=True)
    # Power plot
    ax_power.plot(bps_timestamps, power)
    ax_power.set_ylabel('Power (W)')
    # Energy plot
    ax_energy.plot(energy_timestamps, energy)
    ax_energy.set_ylabel('Energy (J)')
    # RPM plot
    ax_rpm.plot(motor_timestamps, motor_rpms)
    ax_rpm.set_ylabel('RPM')

    pedal_timestamps = [x['timestamp'] for x in pedal]
    pedal_values = [x['pedal'] for x in pedal]

    # Throttle and regen plot
    ax_throttle.plot(mc_timestamps, throttle, label='Throttle')
    ax_throttle.plot(mc_timestamps, regen, label='Regen')
    ax_throttle.plot(pedal_timestamps, pedal_values, label='Pedal')
    ax_throttle.plot()
    ax_throttle.set_ylabel('Throttle, Regen, Pedal')
    ax_throttle.legend()
    ax_throttle.set_xlabel('Time (s)')
    plt.savefig(output_file + "_power.png")
    
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
