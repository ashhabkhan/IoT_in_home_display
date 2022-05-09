#include <ESP8266WiFi.h>
#include <MicroGear.h>

/* NETPIE Parameters */
const char* ssid     = "ThailandFang24_2G";       // WiFi ssid
const char* password = "0887688468";   // WiFi password

#define APPID   "Workshop1IoT"              // use group AppID 
#define KEY     "V6hnr5aYCTWgOfG"                // use group Key
#define SECRET  "0A7SdXj0vhVfXlLzub9runtQo"             // use group Secret
#define ALIAS   "IoTProject"  // your device name, ex. "A01"

WiFiClient client;
int timer = 0;
MicroGear microgear(client);

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

// energy parameters
float Wh =0 ; // Energy in kWh
unsigned long last_time =0;
unsigned long current_time =0;
unsigned long interval = 100;
unsigned int pF = 85;           // Power Factor default 95
float bill_amount = 0;   // 30 day cost as present energy usage incl approx PF 
unsigned int energyTariff = 5000; // Energy cost in THB per unit (kWh)
float power = 0;         // power in watt  





/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void setup() {
    /* PIN SETUP MUX */
    pinMode(s0, OUTPUT); 
    pinMode(s1, OUTPUT); 
    pinMode(s2, OUTPUT); 
    pinMode(s3, OUTPUT); 
    
    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
    }
    delay(2000);         // wait two seconds for initializing
    oled.clearDisplay(); // clear display

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}

void loop() {

    double c = readCurrent();
    Serial.print("Current: ");
    Serial.println(c);
    double v = readVoltage();
    Serial.print("Voltage: ");
    Serial.println(v);
    power= (v * c) * (pF / 100.0);
    Serial.print("Power: ");
    Serial.println(power); 
    last_time = current_time;
    current_time = millis();    
    Wh = Wh +  power *(( current_time -last_time) /3600000.0) ; // calculating energy in Watt-Hour
    Serial.print("Energy: ");
    Serial.println(Wh); 
    bill_amount = Wh * (energyTariff/1000);
     
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();

        if (timer >= 1000) {
            Serial.println("Publish...");

            /* Chat with the microgear named ALIAS which is myself */
            String datastring = (String)v+","+(String)c +","+(String)power +","+(String)Wh +","+(String)bill_amount +","+(String)Wh +","+(String)bill_amount;
            Serial.print("Sending --> ");
            Serial.println(datastring);
            microgear.chat(ALIAS,datastring);
            timer = 0;
        } 
        else timer += 100;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    dummy++;
    if (dummy == 1000){
      dummy = 0;
    }
    delay(100);
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
  if (val < 0){
    val = 0;
  }
  return val;
}

double getC() {
  int a = readSig(14);
  double v = (a / 1024.0) * 3300;
  double c = (v - offset) / sensitive;
  return c;
}
