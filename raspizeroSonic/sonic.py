import wiringpi as pi
import time, sys

# 番号はGPIO番号であってPIN番号ではない
fst_trig = 4
fst_echo = 5
snd_trig = 6
snd_echo = 7
thd_trig = 8
thd_echo = 9
HIGH = 1
LOW = 0


def setup(trig, echo):
    pi.pinMode(trig, pi.OUTPUT)
    pi.pinMode(echo, pi.INPUT)


def sonic_dist(trig, echo):
    pi.digitalWrite(trig, pi.LOW)
    time.sleep(2 * 10**(-6))  # wait 2μs
    pi.digitalWrite(trig, pi.HIGH)
    time.sleep(10 * 10**(-6))  # wait 10μs
    pi.digitalWrite(trig, pi.LOW)
    sigoff = time.time()
    while(pi.digitalRead(echo) == pi.LOW):
        sigoff = time.time()
    sigon = time.time()

    dist = ((sigon - sigoff) * 34000) / 2
    return dist


def main():
    fst_dist = sonic_dist(fst_trig, fst_echo)
    # snd_dist = sonic_dist(snd_trig, snd_echo)
    # thd_dist = sonic_dist(thd_trig, thd_echo)
    print(fst_dist)


if __name__ == '__main__':
    if(sys.argv[1] == '-d'):
        try:
            pi.wiringPiSetupGpio()
            setup(fst_trig, fst_echo)
            setup(snd_trig, snd_echo)
            setup(thd_trig, thd_echo)
            while True:
                main()
        except Exception as e:
            print(e)
            exit()
    else:
        pi.wiringPiSetupGpio()
        setup(fst_trig, fst_echo)
        setup(snd_trig, snd_echo)
        setup(thd_trig, thd_echo)
        while True:
            main()
