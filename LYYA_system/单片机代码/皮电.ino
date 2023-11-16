const int LED=13;
const int GSR=A2;
int threshold=0;
int sensorValue;
int n;
void setup(){
  Serial.begin(9600);
  }

void loop(){
  int temp;
  n++;
  sensorValue=analogRead(GSR);
  Serial.println(sensorValue);
  delay(20); 
  }