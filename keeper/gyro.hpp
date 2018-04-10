#include <MPU9250_asukiaaa.h>
#include <Wire.h>

#ifndef GYRO_H
#define GYRO_H

class Gyro{
    private:
        MPU9250 gyro;
        float correction;
        float gz;
        float pregz;
        float deg;
    public:
        Gyro();
        void init();
        float update(float dt);
        int get_dir();
};

#endif // !GYRO_H
