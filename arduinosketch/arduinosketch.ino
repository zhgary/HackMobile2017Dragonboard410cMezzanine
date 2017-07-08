#define limit_lo -70
#define limit_hi 260

String string_b = "";
char buffer[80] = "";
float currentAngle = (limit_lo+limit_hi)/2;

void servoPulse(int pin, float angle)
{
  angle = angle < limit_lo ? limit_lo : angle;
  angle = angle > limit_hi ? limit_hi : angle;
  int microSeconds = angle*50./9.;
  digitalWrite(pin,1);
  delayMicroseconds(1000+microSeconds);
  digitalWrite(pin,0);
}

void setup()
{
  pinMode(4,OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop()
{
  int result;
  servoPulse(4,currentAngle);
  delay(2);
  result = Serial.readBytes(buffer,10);
  if (result > 0)
  {
    byte value = (byte)buffer[0];
    currentAngle = ((float)value)*(limit_hi-limit_lo)/255. + limit_lo;
    Serial.println(currentAngle);
    //buffer[result] = 0;
    //Serial.write(buffer);
    //string_b = buffer;
    //currentAngle = string_b.toInt();
  }
}




