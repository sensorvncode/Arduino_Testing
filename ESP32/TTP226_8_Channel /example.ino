/*
  Created by SENSORVN.COM, April 05, 2024.
*/
/* Variables */
#define quantity 8
int pin[quantity] = {2, 3, 4, 5, 6, 7, 8, 9};
/* Arduino Functions */
void setup()
{
  // Serial
  Serial.begin(9600);
}
void loop()
{
  for(int i = 0; i < quantity; i++)
  {
    if(digitalRead(pin[i]) == HIGH)
    {
      Serial.println(i + 1);
      delay(500);
    }
  }
}
