int fst_trig = 3;
int fst_echo = 2;

void setup() {
  Serial.begin(9600);
  pinMode(fst_trig, OUTPUT);
  pinMode(fst_echo, INPUT);
}

void loop() {
  sonic_distance(fst_trig, fst_echo);
}

void sonic_distance(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  if(duration > 0){
    duration = duration/2;
    float distance = duration*340*100/1000000;
    Serial.print("                                      "); //初期化
    Serial.print("\rDistance: ");
    Serial.print(distance);
    Serial.print("cm");
  }
  delay(500);
}
