#define RELAY 8
#define LED_R 9
#define LED_G 10
#define LED_B 11
#define POWER 3
void setup() {
  pinMode(RELAY,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(POWER,INPUT_PULLUP);
  digitalWrite(RELAY,LOW);
  digitalWrite(LED_R,HIGH);
  digitalWrite(LED_G,HIGH);
  digitalWrite(LED_B,HIGH);
  Serial.begin(9600);
}
bool is_on = false;
void loop() {
  Serial.println(digitalRead(POWER));
  if(!digitalRead(POWER)){
    is_on = !is_on;
    digitalWrite(RELAY,is_on); 
    digitalWrite(LED_R,!is_on);
    delay(1000);
  }
}
