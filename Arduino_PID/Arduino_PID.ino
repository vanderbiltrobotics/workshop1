// Change these variables to match the ports you used on your Arduino
int motor1 = 0;
int motor2 = 0;
int pot = A0;

double Kp = 0;
double Ki = 0;
double Kd = 0;

void setup() { // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(pot, INPUT);

  Serial.begin(9600);
}

double acc = 0;
int lastPV = 0;

void loop() { // put your main code here, to run repeatedly:
  int pv = analogRead(pot); // Read pot position with analogRead

  int sp = 500;
  int error = sp-pv;
  acc+=error;

  int pTerm = Kp * error;
  int iTerm = Ki * acc;
  int dTerm = Kd * (pv-lastPV);
  int cv = pTerm + iTerm + dTerm;

  lastPV = pv;

  setOutput(cv);
  Serial.print("PV=");
  Serial.println(pv);
  Serial.print("CV=");
  Serial.println(cv);
  delay(10); // Set algorithm frequency to 100hz
}

// Convenience method for controlling H-bridge
void setOutput(int value){ // -255<value<255
  int pv = analogRead(pot);
  if(pv>=1010 || pv<=10) value = 0; // If pot is at edge, stop output
  
  if(value>0) {
    digitalWrite(motor1, LOW);
    analogWrite(motor2, value);
  }else if(value<0){
    digitalWrite(motor2, LOW);
    analogWrite(motor1, abs(value));
  }else{
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
  }
}

