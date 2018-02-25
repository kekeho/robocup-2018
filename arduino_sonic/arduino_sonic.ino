int fst_trig = 3;
int fst_echo = 2;
int snd_trig = 5;
int snd_echo = 6;
int thd_trig = 11;
int thd_echo = 12;

float fst_dist; float snd_dist; float thd_dist;

void setup() {
  Serial.begin(9600);
  pinMode(fst_trig, OUTPUT);
  pinMode(fst_echo, INPUT);
  pinMode(snd_trig, OUTPUT);
  pinMode(snd_echo, INPUT);
  pinMode(thd_trig, OUTPUT);
  pinMode(thd_echo, INPUT);
}

void loop() {
  fst_dist = sonic_distance(fst_trig, fst_echo);
  snd_dist = sonic_distance(snd_trig, snd_echo);
  thd_dist = sonic_distance(thd_trig, thd_echo);
  Serial.print("1. ");
  Serial.println(fst_dist);
  Serial.print("2. ");
  Serial.println(snd_dist);
  Serial.print("3. ");
  Serial.println(thd_dist);
}

float sonic_distance(int trig, int echo){
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
