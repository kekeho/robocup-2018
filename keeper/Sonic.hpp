#include<Arduino.h>

#ifndef SONIC_H
#define SONIC_H

class Sonic{
    public:
        Sonic();
        int ldist();
        int rdist();
        int bdist();
};

#endif // !SONIC_H