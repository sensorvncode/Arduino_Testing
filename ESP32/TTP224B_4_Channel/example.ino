/*
  Created by SENSORVN.COM, April 05, 2024.
*/

/* Variables */
#define quantity 4
int pin[quantity] = {7, 6, 5, 4};

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
