int ir1 = A0, ir2 = A1, ir3 = A2, ir4 = A3, ir5 = A4;

void setup() {
  Serial.begin(9600);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void loop() {
  int r1 = digitalRead(ir1);
  int r2 = digitalRead(ir2);
  int r3 = digitalRead(ir3);
  int r4 = digitalRead(ir4);
  int r5 = digitalRead(ir5);

  Serial.print(r1);
  Serial.print(" ");
  Serial.print(r2);
  Serial.print(" ");
  Serial.print(r3);
  Serial.print(" ");
  Serial.print(r4);
  Serial.print(" ");
  Serial.println(r5);
}
