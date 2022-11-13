# Usage: sh monitor.sh | python dash.py

import time

class Dashboard:
    def __init__(self):
        self.bps_pack_times = []
        self.bps_pack_ts = []
        self.motor_controller_power_times = []
        self.motor_controller_power_ts = []
        self.start_time = None
        # self.fig = plt.figure()
        # self.current_plot = self.fig.add_subplot(211)
        # self.voltage_plot = self.fig.add_subplot(212)
        # self.current_line, = self.current_plot.plot([], [])
        # self.current_plot.set_ylabel('Current')
        # self.voltage_line, = self.voltage_plot.plot([], [])
        # self.voltage_plot.set_ylabel('Voltage')
        # plt.show()

    def t(self):
        return time.time() - self.start_time

    def next_line(self, line):
        if self.start_time is None:
            self.start_time = time.time(0)

        def _after(prefix):
            if prefix in line:
                return line[line.index(prefix) + len(prefix):]

        def _dict(s):
            d = {}
            for item in s.split(', '):
                key, value = item.split()
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

        if 'BPSPackInformation: ' in line:
            d = _dict(_after('BPSPackInformation: '))
            self.bps_pack_ts.append({**d, 'timestamp': self.t()})
            if len(self.bps_pack_ts) % 10 == 0:
                '''
                pack_voltage 10769,
                pack_current 0,
                pack_soc 20,
                discharge_relay_status 1,
                charge_relay_status 1,
                charger_safety_status 0,
                dtc_status 0,
                multipurpose_input_signal_status 0,
                always_on_signal_status 1,
                is_ready_signal_status 1,
                is_charging_signal_status 0
                '''
                print(f'[{len(self.bps_pack_ts)}] pack current:', d['pack_current'], 'pack voltage:', d['pack_voltage'], flush=True)

        elif 'MotorControllerPowerStatus: ' in line:
            d = _dict(_after('MotorControllerPowerStatus: '))
            self.motor_controller_power_ts.append({**d, 'timestamp': self.t()})
            if len(self.motor_controller_power_ts) % 10 == 0:
                '''
                battery_voltage %u
                battery_current %u
                battery_current_direction %u
                motor_current %u
                fet_temp %u
                motor_rpm %u
                pwm_duty %u
                lead_angle %u
                '''
                print(f'[{len(self.motor_controller_power_ts)}] battery current:', d['battery_current'], 'motor rpm:', d['motor_rpm'], flush=True)

    def update_plot(self):
        cutoff = 256
        current_data = [data['pack_current'] for data in self.bps_pack_ts][-cutoff:]
        voltage_data = [data['pack_voltage'] for data in self.bps_pack_ts][-cutoff:]
        x_data = list(range(len(self.bps_pack_ts) - len(current_data), len(self.bps_pack_ts)))

        self.current_plot.set_xlim(min(x_data) - 1, max(x_data) + 1)
        self.voltage_plot.set_xlim(min(x_data) - 1, max(x_data) + 1)

        self.current_line.set_xdata(x_data)
        self.current_line.set_ydata(current_data)
        self.current_plot.set_ylim(min(current_data) - 1, max(current_data) + 1)

        self.voltage_line.set_xdata(x_data)
        self.voltage_line.set_ydata(voltage_data)
        self.voltage_plot.set_ylim(min(voltage_data) - 1, max(voltage_data) + 1)

        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        

dashboard = Dashboard()
try:
    while True:
        dashboard.next_line(input())
except KeyboardInterrupt:
    import json

    with open('./log.txt', 'w') as f:
        json.dump({"bps": dashboard.bps_pack_ts, "motor": dashboard.motor_controller_power_ts}, f)
