#include<PixyI2C.h>

#ifndef CAPTURE_H
#define CAPTURE_H

typedef struct Point{
    int x;
    int y;
};

class Capture{
    private:
        PixyI2C pixy;
        int width;
        bool flag;
        uint16_t blocks;
    public:
        Capture();
        void init();
        void update();
        int get_ball();
        Point get_goal();
        bool isthis_neutral_point(); //中立点の判定
        bool isthere_mine_goal(); //味方のゴールが見えているか
        bool isthere_ball(); //ボールが見えているか
};

#endif // !CAPTURE_H