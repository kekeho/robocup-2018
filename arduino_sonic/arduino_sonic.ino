int fst_trig = 3; //right
int fst_echo = 2;
int snd_trig = 5; //left
int snd_echo = 6;
int thd_trig = 11; //back
int thd_echo = 12;
int cnt = 0;

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
  if(cnt == 0){
    thd_dist = sonic_distance(thd_trig, thd_echo);
  } 
  fst_dist = sonic_distance(fst_trig, fst_echo);
  snd_dist = sonic_distance(snd_trig, snd_echo);
  Serial.print("1. ");
  Serial.println(fst_dist);
  Serial.print("2. ");
  Serial.println(snd_dist);
  Serial.print("3. ");
  Serial.println(thd_dist);
  cnt++;
  if(cnt > 2){
    cnt = 0;
  }
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
