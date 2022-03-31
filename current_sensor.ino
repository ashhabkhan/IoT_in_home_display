int sensitive = 100; // 20A

int offset = 3880; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  double c = getCA();
  Serial.println(c);
  delay(1000);
}

double getCA() {
  int count = 200;
  double sum = 0;
  for (int i = 0; i < count; i++) {
    sum += getC();
  }
  double val = sum / count;
  return val;
}
// อ่านค่ากระแส
double getC() {
  int a = analogRead(A0);
  double v = (a / 1024.0) * 5000;
  double c = (v - offset) / sensitive;
  return c;
}

// testing
//void loop()

//{
//  int val = 0;
//  val = analogRead(A0);    // read the input pin
//  Serial.println(val);             // debug value
//
//}
