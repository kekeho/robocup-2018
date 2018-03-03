int back_trig = 3; //back
int back_echo = 2;
int right_trig = 8; //right
int right_echo = 7;
int left_trig = 12; //left
int left_echo = 11;

int out_back = 14;
int out_right = 15;
int out_left = 16;
int cnt = 0;

int b_MAX = 30; //30cm
int goal_MAX = 5.2; //3~4cm
int MAX = 50; //46cm
int SUM = 100; //左右の壁から壁までは182cm。超音波センサの間隔が14.5cm
char checkback_mode;

float back_dist; float right_dist; float left_dist;

void setup() {
  Serial.begin(9600);
  pinMode(back_trig, OUTPUT);
  pinMode(back_echo, INPUT);
  pinMode(right_trig, OUTPUT);
  pinMode(right_echo, INPUT);
  pinMode(left_trig, OUTPUT);
  pinMode(left_echo, INPUT);
  pinMode(out_back, OUTPUT);
  pinMode(out_right, OUTPUT);
  pinMode(out_left, OUTPUT);
}

void loop() {
  back_dist = sonicDisrance(back_trig, back_echo);
  left_dist = sonicDisrance(left_trig, left_echo);
  right_dist = sonicDisrance(right_trig, right_echo);
  checkLeftAndRight(left_dist, right_dist);
  checkBack(back_dist);
  
  Serial.print("b ");
  Serial.println(back_dist);
  Serial.print("r ");
  Serial.println(right_dist);
  Serial.print("l ");
  Serial.println(left_dist);
}

float sonicDisrance(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  duration = duration/2;
  float distance = duration*340*100/1000000;
  return distance;
}

int checkLeftAndRight(int d_left,int d_right){\
  //おそらく他ロボットが入ってきているとき(10cmの誤差考慮)
  if(d_left + d_right < SUM-10){
    digitalWrite(out_back, LOW);
    digitalWrite(out_left, LOW);
    digitalWrite(out_right, LOW);
    return -1;
  }
  //壁に接近(あと5cm)
  if(d_left < MAX+6){
    digitalWrite(out_left, HIGH);
    digitalWrite(out_right, LOW);
  } else if(d_right < MAX+8){
    digitalWrite(out_right, HIGH);
    digitalWrite(out_left, LOW);
  } else {
    digitalWrite(out_left, LOW);
    digitalWrite(out_right, LOW);
  }
  return 0;
}

int checkBack(int d_back){
  //goal mode
  if(d_back > 15 || d_back < 5){
    digitalWrite(out_back, HIGH);
  } else {
    digitalWrite(out_back, LOW);
  }
  return 0;
}
