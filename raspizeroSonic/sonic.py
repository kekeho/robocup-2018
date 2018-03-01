import RPi.GPIO as gpio
import time

fst_trig = 0
fst_echo = 1
snd_trig = 2
snd_echo = 3
thd_trig = 4
thd_echo = 5
HIGH = 1
LOW = 0


def setup(trig, echo):
    gpio.setmode(trig, gpio.OUT)
    gpio.setmode(echo, gpio.IN)


def pulseIn(pin):
    global HIGH
    t_start = 0
    t_end = 0

    # check high time
    while gpio.input(pin) == HIGH:
        t_end = time.time()
    return t_end - t_start


def sonic_dist(trig, echo):
    global HIGH
    global LOW
    gpio.output(trig, LOW)
    time.sleep(2 * 10**(-6))  # wait 2μs
    gpio.output(trig, HIGH)
    time.sleep(10 * 10**(-6))  # wait 10μs
    gpio.output(trig, LOW)
    duration = pulseIn(echo, HIGH)
    duration = duration / 2
    dist = duration * 340 * 100 / 1000000
    return dist


def main():
    setup(fst_trig, fst_echo)
    setup(snd_trig, snd_echo)
    setup(thd_trig, thd_echo)

    fst_dist = sonic_dist(fst_trig, fst_echo)
    snd_dist = sonic_dist(snd_trig, snd_echo)
    thd_dist = sonic_dist(thd_trig, thd_echo)
    print(fst_dist, snd_dist, thd_dist)


if __name__ == '__main__':
    while True:
        try:
            main()
        except Exception as e:
            print(e)
            print('FIN')
            exit()
