int pressureAnalogPin = 35;
int pressureReading;
float p1 = 0; // to be swapped with current pressure
float p2 = 0; // current pressure
unsigned long t1 = 0; // to be swapped with current time
unsigned long t2 = 0;// current time

float threshold = 7;// threshold for pressure change 

void setup() 
{
Serial.begin(9600);
}

void loop() 
{
pressureReading = analogRead(pressureAnalogPin);
t2 = millis(); // defines t2 as millseconds 
float voltage = pressureReading * (3.3 / 4095);
p2 = ((10.0 - 0.03) / (3.3 - 0) * voltage);

if (t1 != 0) // slots in first time difference
  {
  float dt= (t2 - t1) / 1000.0; // change in time, divided by 1000 due to milliseconds
  if (dt > 0) // ensures no division by 0
    {
    float dPdt = (p2 - p1) /dt; // Finite Difference Method Derivative
    if (dPdt > threshold) // pressure vs finger  
      {
      Serial.println("BUTTON PRESSED");
      }  
    }
  }
Serial.println(p2);

t1 = t2; // time swap
p1 = p2; // pressure swap

delay(100);
}