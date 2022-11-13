from random import randint
import sys
from time import sleep

def update_progress(regen, throttle, step=""):
    g = 30
    regenB = int(regen / 100 * g)
    thorttleB = int(throttle / 100 * g)
    regen_bar = ''.join(['■' if x >= g-regenB else '□' for x in range(g)])
    throttle_bar = ''.join(['■' if x < thorttleB else '□' for x in range(g)])
    if not step:
        step = "[-->💀<--]" if throttle == 0 and regen == 0 else "         "
    regen = regen if regen > 99 else f" {regen}"
    throttle = throttle if throttle > 99 else f" {throttle}"
    sys.stdout.write(f"\rREGEN: {regen}% {regen_bar}   {step}   {throttle_bar}\tTHROTTLE: {throttle}% \t")

while True:
    x = input()
    if "ERROR" not in x:
        continue
    x = x.split(" ")
    regen, throttle = int(x[4]), int(x[-1])
    throttle = int(throttle / 256 * 100)
    regen = int(regen / 256 * 100)
    update_progress(regen, throttle)


for i in list(range(257)) + list(range(256,-1,-1)):
    if i <= 50:
        regen, throttle = (79.159 * ((50-i) ** 0.3)), 0
    elif i < 100:
        regen, throttle = 0, 0
    else:
        throttle, regen = -56.27610464*((156-(i-100))**0.3)+256, 0
    throttle = int(throttle / 256 * 100)
    regen = int(regen / 256 * 100)
    update_progress(regen, throttle, f"ADC Input: {i}")
    sleep(0.05)
