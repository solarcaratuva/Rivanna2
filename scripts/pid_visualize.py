import json
import sys
import numpy as np
import matplotlib.pyplot as plt

def create_plots(data, output_file):
    timestamps = [x['timestamp'] for x in data]
    # These are NOT the constants; these are the contributions from each part
    p = [x['p'] for x in data]
    i = [x['i'] for x in data]
    d = [x['d'] for x in data]
    error = [x['error'] for x in data]
    last_error = [x['last_error'] for x in data]
    input = [x['input'] for x in data]
    setpoint = [x['setpoint'] for x in data]
    p = np.array(p)
    i = np.array(i)
    d = np.array(d)
    output = p + i + d
    error = np.array(error)
    input = np.array(input)
    setpoint = np.array(setpoint)

    plt.figure(figsize=(20, 10))
    plt.plot(timestamps, output, label='output')
    plt.plot(timestamps, error, label='error')
    plt.plot(timestamps, input, label='input')
    plt.plot(timestamps, setpoint, label='setpoint')
    plt.plot(timestamps, p, label='p')
    plt.plot(timestamps, i, label='i')
    plt.plot(timestamps, d, label='d')
    plt.legend()
    plt.savefig(output_file + '_pid.png')

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 pid_visualize.py <log_file>")
        exit(1)

    log_file = sys.argv[1]
    with open(log_file, 'r') as f:
        data = json.load(f)
    create_plots(data, log_file.replace(".json", ""))
