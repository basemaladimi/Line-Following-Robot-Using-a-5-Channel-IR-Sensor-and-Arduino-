int ir1 = A0 , ir2 = A1 , ir3 = A2 , ir4 = A3 , ir5 = A4;  

int motor1Pin1 = 3 , motor1Pin2 = 4 , motor2Pin1 = 7 , motor2Pin2 = 8 , enablePinA = 6 , enablePinB = 5;

int speed = 255; 

void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);
}

void loop() {
  moveForward(speed, speed);
  delay(1000);
  turnRight(speed, 0);
  delay(1000);
  turnLeft(0, speed);
  delay(1000);
}


void moveForward(int speed1, int speed2) {
  analogWrite(enablePinA, speed1);  
  analogWrite(enablePinB, speed2); 
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnRight(int speed1, int speed2) {
  analogWrite(enablePinA, speed1);  
  analogWrite(enablePinB, speed2);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnLeft(int speed1, int speed2) {
  analogWrite(enablePinA, speed1);
  analogWrite(enablePinB, speed2);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopCar() {
  analogWrite(enablePinA, 0);
  analogWrite(enablePinB, 0);
}
