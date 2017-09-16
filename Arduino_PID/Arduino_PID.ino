// Change these variables to match the ports you used on your Arduino
int motor1 = 0;
int motor2 = 0;
int pot = A0;

void setup() { // put your setup code here, to run once:
  pinMode(pin, OUTPUT); // It's necessary to define each pin as
                        // either an INPUT or an OUTPUT
}

void loop() { // put your main code here, to run repeatedly:
  int pv = analogRead(pot); // Read pot position with analogRead

  int cv = 0; // Create your PID Controller Here

  setOutput(cv);
  delay(10); // Set algroithm frequency to 100hz
}

// Convience method for controlling H-bridge
void setOutput(int value){ // -255<value<255
  int pv = analogRead(pot);
  if(pv==1023 || pv==0) value = 0;
  
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

