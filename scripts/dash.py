# Usage: sh monitor.sh | python dash.py

import time
import datetime

class Dashboard:
    def __init__(self):
        self.bps_pack_ts = []
        self.motor_controller_power_ts = []
        self.motor_commands_ts = []
        self.pedal_ts = []
        self.start_time: float = None

    def t(self):
        return time.time() - self.start_time

    def next_line(self, line):
        if self.start_time is None:
            self.start_time = time.time()

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

        elif 'ECUMotorCommands: ' in line:
            d = _dict(_after('ECUMotorCommands: '))
            self.motor_commands_ts.append({**d, 'timestamp': self.t()})
            if len(self.motor_commands_ts) % 10 == 0:
                '''
                throttle %u
                regen %u
                cruise_control_speed %u
                cruise_control_en %u
                forward_en %u
                reverse_en %u
                motor_on %u
                '''
                print(f'[{len(self.motor_commands_ts)}] throttle:', d['throttle'], 'regen:', d['regen'], flush=True)

        elif 'RawPedalInput: ' in line:
            d = _dict(_after('RawPedalInput: '))
            self.pedal_ts.append({**d, 'timestamp': self.t()})
            if len(self.pedal_ts) % 10 == 0:
                '''
                pedal %u
                '''
                print(f'[{len(self.pedal_ts)}] pedal:', d['pedal'], flush=True)
            

dashboard = Dashboard()
try:
    while True:
        dashboard.next_line(input())
except Exception as e:
    print(e)

    import json
    import os

    if not os.path.isdir('output'):
        os.mkdir('output')

    time_ = datetime.datetime.fromtimestamp(dashboard.start_time).strftime("%Y%m%d-%H%M%S")

    with open(f'./output/log_{time_}.json', 'w') as f:
        json.dump({
            "bps": dashboard.bps_pack_ts,
            "motor": dashboard.motor_controller_power_ts,
            "motor_commands": dashboard.motor_commands_ts,
            "pedal": dashboard.pedal_ts,
        }, f)
