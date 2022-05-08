//Mux control pins
int s0 = 5;
int s1 = 4;
int s2 = 0;
int s3 = 2;

//Mux in "SIG" pin
int SIG_pin = 0;
double voltage = 0;

// current sensor
int sensitive = 100; // 20A
int offset = 1760;

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  Serial.begin(115200);
}


void loop() {
  double c = readCurrent();
  Serial.print("Current: ");
  Serial.println(c);
  double v = readVoltage();
  Serial.print("Voltage: ");
  Serial.println(v);
  delay(500);
//  Serial.println(readSig(14));
}

int readSig(int channel)
{
   // use the first four bits of the channel number to set the channel select pins 
    digitalWrite(s0, bitRead(channel, 0));
    digitalWrite(s1, bitRead(channel, 1));
    digitalWrite(s2, bitRead(channel, 2));
    digitalWrite(s3, bitRead(channel, 3));
    int sig = analogRead(SIG_pin);
    // read from the selected mux channel
    return sig;
}

double readVoltage(){
  double sensorValue1 = 0;
  double sensorValue2 = 0;
  int crosscount = 0;
  int climb_flag = 0;
  int val[100];
  int max_v = 0;
  double VmaxD = 0;
  double VeffD = 0;
  double Veff = 0;
  for ( int i = 0; i < 100; i++ ) {
    sensorValue1 = readSig(15);
    if (readSig(15) > 511) {
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
    Veff = (((VeffD - 420.76) / -90.24) * -210.2) + 210.2;
  }
  else {
    Veff = 0;
  }
  VmaxD = 0;
  delay(100);
  return Veff;
}



double readCurrent() {
  int count = 200;
  double sum = 0;
  for (int i = 0; i < count; i++) {
    sum += getC();
  }
  double val = sum / count;
  return val;
}

double getC() {
  int a = readSig(14);
  double v = (a / 1024.0) * 3300;
  double c = (v - offset) / sensitive;
  return c;
}
