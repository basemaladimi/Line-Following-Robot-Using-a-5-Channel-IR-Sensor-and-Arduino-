int ir1 = A0 , ir2 = A1 , ir3 = A2 , ir4 = A3 , ir5 = A4;  

int motor1Pin1 = 3 , motor1Pin2 = 4 , motor2Pin1 = 7 , motor2Pin2 = 8 , enablePinA = 6 , enablePinB = 5;

// متغيرات خاصة بالسماح بتشغيل عمليتين في نفس الوقت
bool turning = false; 
bool all_black = false;
// متغيرات الخاصة بالميليز
unsigned long lastSensorReadTime = 0;
const unsigned long sensorReadInterval = 1;
unsigned long lastMotorUpdateTime = 0;
const unsigned long motorUpdateInterval = 1;

const int S1 = 220 , S2 = 200 , S3 = 255 , S4 = 220 ; // سرعة الموتور أثناء خط مستقيم

int previousError = 0; // متغير لحفظ قيمة آخر قراءة للحساس

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

  TCCR0B = TCCR0B & B11111000 | B00000010; // للتخفيف من سرعة الموتور حتى إذا كان الفولت عالي
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSensorReadTime >= sensorReadInterval) {
    lastSensorReadTime = currentTime;
    readSensors();
  }

  if (currentTime - lastMotorUpdateTime >= motorUpdateInterval) {
    lastMotorUpdateTime = currentTime;
    updateMotors();
  }
}

void readSensors() {
  int r1 = digitalRead(ir1);
  int r2 = digitalRead(ir2);
  int r3 = digitalRead(ir3);
  int r4 = digitalRead(ir4);
  int r5 = digitalRead(ir5);

  // التحقق من حالة الخط الأسود
  if (r1 == LOW && r2 == LOW && r3 == LOW && r4 == LOW && r5 == LOW) {
    all_black = true;
    moveForward(S4 , S4); 
    delay (1000);
  } 
  // التحقق من حالة الخط الأبيض أو الخطوط الأخرى
  else if (r1 == HIGH && r2 == HIGH && r3 == HIGH && r4 == HIGH && r5 == HIGH) {
    if (all_black) {
      stopCar();
    } else {
      correctCourse();
    }
  }
  else if (r1 == HIGH && r2 == LOW && r3 == LOW && r4 == LOW && r5 == HIGH){
    correctCourse();
  }
  // المنطق الطبيعي للحركة
  else {
    all_black = false;
    if (r2 == HIGH && r4 == HIGH && r1 == HIGH && r5 == HIGH && r3 == LOW) {
      previousError = 0;
      turning = false;
      moveForward(225 , 225);
    } 
    else if ((r1 == HIGH && r2 == LOW && r3 == HIGH && r4 == HIGH && r5 == HIGH) || 
             (r1 == HIGH && r2 == LOW && r3 == LOW && r4 == HIGH && r5 == HIGH)) {
      previousError = -1;
      turning = true;
      turnLeft(160, S1);
    } 
    else if (r1 == LOW && r2 == HIGH && r3 == HIGH && r4 == HIGH && r5 == HIGH) {
      previousError = -1;
      turning = true;
      turnLeft(0, S3);
    } 
    else if ((r1 == HIGH && r2 == HIGH && r3 == HIGH && r4 == LOW && r5 == HIGH) ||
             (r1 == HIGH && r2 == HIGH && r3 == LOW && r4 == LOW && r5 == HIGH)) {
      previousError = 1;
      turning = true;
      turnRight(S1, 160);
    } 
    else if (r1 == HIGH && r2 == HIGH && r3 == HIGH && r4 == HIGH && r5 == LOW) {
      previousError = 1;
      turning = true;
      turnRight(S3, 0);
    } 
    else if ((r1 == LOW && r2 == LOW && r3 == LOW && r4 == HIGH && r5 == HIGH) || 
             (r1 == LOW && r2 == LOW && r3 == HIGH && r4 == HIGH && r5 == HIGH)) {
      previousError = -1;
      turning = true;
      turnLeft(0, S3);
      delay (500);
    } 
    else if ((r1 == HIGH && r2 == HIGH && r3 == LOW && r4 == LOW && r5 == LOW) || 
             (r1 == HIGH && r2 == HIGH && r3 == HIGH && r4 == LOW && r5 == LOW)) {
      previousError = 1;
      turning = true;
      turnRight(S3, 0);
      delay (500);
    } 
    else if (r1 == HIGH && r2 == LOW && r3 == LOW && r4 == LOW && r5 == LOW) {
      previousError = 1;
      turning = true;
      turnRight(S3, 0); 
    } 
    else if (r1 == LOW && r2 == LOW && r3 == LOW && r4 == LOW && r5 == HIGH) {
      previousError = -1;
      turning = true;
      turnLeft(0, S3);
    }
  }
}

void updateMotors() {
  if (!turning) {
  } else {
    checkTurnCompletion();
  }
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

void checkTurnCompletion() {
  int r2 = digitalRead(ir2);
  int r4 = digitalRead(ir4);

  if (r2 == HIGH && r4 == HIGH) {
    turning = false;
  }
}

 // منطق تعديل المسار عند الخروح منه
void correctCourse() {
  if (previousError == 1) {
    turnRight(S3, 0);
  } 
  else if (previousError == -1) {
    turnLeft(0, S3);
  } 
  else if (previousError == 0) {
    moveForward(S4 , S4);
  }
}
