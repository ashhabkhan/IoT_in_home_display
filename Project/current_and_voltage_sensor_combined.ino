#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;
// current sensor
int sensitive = 100; // 20A
int offset = 3880;

// voltage sensor
double sensorValue1 = 0;
double sensorValue2 = 0;
int crosscount = 0;
int climb_flag = 0;
int val[100];
int max_v = 0;
double VmaxD = 0;
double VeffD = 0;
double Veff = 0;

// setup fucntion
void setup() {
  Serial.begin(9600);
}

// main loop
void loop() {
  // voltage sensor
  for ( int i = 0; i < 100; i++ ) {
    sensorValue1 = ads.readADC_SingleEnded(1);
    if (ads.readADC_SingleEnded(1) > 511) {
      val[i] = sensorValue1;
    }
    else {
      val[i] = 0;
    }
    delay(1);
  }

  max_v = 0;
  for ( int i = 0; i < 100; i++ )
  {
    if ( val[i] > max_v )
    {
      max_v = val[i];
    }
    val[i] = 0;
  }
  if (max_v != 0) {
    VmaxD = max_v;
    VeffD = VmaxD / sqrt(2);
    Veff = (((VeffD - 480) / -90) * -240) + 240;
  }
  else {
    Veff = 0;
  }
  // current sensor
  double c = getCA();
  Serial.print("Current: ");
  Serial.println(c);
  Serial.print("Voltage: ");
  Serial.println(Veff);
  VmaxD = 0;
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

double getC() {
  int a = analogRead(A0);
  double v = (a / 1024.0) * 5000;
  double c = (v - offset) / sensitive;
  return c;
}
