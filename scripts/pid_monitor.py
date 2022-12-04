import datetime
import time

def line_to_dict(line: str):
    d = {}
    line = line[len("00:14:43 DEBUG /workspaces/rivanna2/ECU/src/main.cpp:46: "):]
    print(line)
    for item in line.split(', '):
        key, value = item.split(': ')
        try:
            d[key] = int(value)
            # assume unsigned
            if d[key] > 2**15:
                d[key] -= (2**16 - 1)
        except:
            try:
                d[key] = float(value)
            except:
                d[key] = value
    return d

events = []
start_time = None

try:
    while True:
        read = input()
        if 'last_error: ' not in read:
            continue
        if start_time is None:
            start_time = time.time()
        events.append({**line_to_dict(read), 'timestamp': time.time() - start_time})
except Exception as e:
    print(e)

    import json
    import os

    if not os.path.isdir('output'):
        os.mkdir('output')

    time_ = datetime.datetime.fromtimestamp(start_time).strftime("%Y%m%d-%H%M%S")

    with open(f'./output/log_pid_{time_}.json', 'w') as f:
        json.dump(events, f)