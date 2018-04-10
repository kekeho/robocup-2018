#ifndef move_h
#define move_h

class Move{
  public:
    void moter_set();
    void outPut(float angle, float x, float y);

  private:
    float out1, out2, out3;
    int r = 1;
    bool sw;
  
};

#endif
