from __future__ import print_function

import time
from itertools import count
import RPi.GPIO as GPIO


INPUT_PIN = 24
def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(INPUT_PIN, GPIO.IN)


def read():
    return GPIO.input(INPUT_PIN)


def pause():
    time.sleep(.1)


def sync():
    """
    Waits while high, then until the next high
    """
    while read():
        pause()
    while not read():
        pass

def main():
    setup()
    sync()
    for highcount in count():
        if not read():
            break
    print(highcount)


if __name__ == '__main__':
    main()
