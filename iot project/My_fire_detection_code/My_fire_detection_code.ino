#define flamePin D2
#define led1 D0
#define led2 D1
#define buzzer D6
void setup()
{
  Serial.begin(115200);
  pinMode(flamePin,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(buzzer,OUTPUT);
}
void loop()
{
  int Flame = digitalRead(flamePin);
  Serial.print("\nFlame Value:");
  Serial.print(Flame);
  delay(1000);
  if(Flame == 0)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(buzzer,LOW);

  }
  else
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(buzzer,HIGH);
  }
}