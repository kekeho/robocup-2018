//moter.h
#ifndef line_h
#define line_h

class Line{
  public:
    Line(int thb,int thw);
    bool check_black();
    bool check_white();

  private:
    uint8_t fpin[4];
    uint8_t bpin[2][5];
    int threshold_black;
    int threshold_white;
};

#endif