void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    String data = Serial.readString();
    Serial.print(data);
  }
}
