import matplotlib.pyplot as plt

class Dashboard:
    def __init__(self):
        self.bps_pack_ts = []
        fig = plt.figure()
        current_plot = fig.add_subplot(211)
        voltage_plot = fig.add_subplot(212)
        self.current_line, = current_plot.plot([], [])
        current_plot.set_ylabel('Current')
        self.voltage_line, = voltage_plot.plot([], [])
        voltage_plot.set_ylabel('Voltage')

    def next_line(self, line):
        def _after(prefix):
            if prefix in line:
                return line[line.index(prefix) + len(prefix):]

        def _dict(s):
            d = {}
            for item in s.split(', '):
                key, value = item.split()
                try:
                    d[key] = float(value)
                except:
                    try:
                        d[key] = int(value)
                    except:
                        d[key] = value
                
            return d

        if 'BPSPackInformation: ' in line:
            d = _dict(_after('BPSPackInformation: '))
            self.bps_pack_ts.append(d)
            print('Pack current:', d['pack_current'])

    def update_plot(self):
        cutoff = 256
        current_data = [data['pack_current'] for data in self.bps_pack_ts][-cutoff:]
        voltage_data = [data['pack_voltage'] for data in self.bps_pack_ts][-cutoff:]
        x_data = list(range(len(self.bps_pack_ts) - len(current_data), len(self.bps_pack_ts)))
        self.current_line.set_xdata(x_data)
        self.current_line.set_ydata(current_data)
        self.voltage_line.set_xdata(x_data)
        self.voltage_line.set_ydata(voltage_data)
        

dashboard = Dashboard()
try:
    while True:
        dashboard.next_line(input())
except KeyboardInterrupt:
    import json

    with open('./log.txt', 'w') as f:
        json.dump(dashboard.bps_pack_ts, f)
