  #include <ESP8266WiFi.h>
  #include <MicroGear.h>
  #include <DHT.h>
  // ----- Change following 6 config variables ---------------------
  const char* ssid     = "Preaw_wanida";       // WiFi ssid
  const char* password = "0819877021";   // WiFi password
  #define APPID   "TggsApp"              // use group AppID 
  #define KEY     "wBmh3QVpjLpwFs5"                // use group Key
  #define SECRET  "5zxEVwawr1R6OuJvxvi9zAwRz"             // use group Secret
  #define ALIAS   "A01"  // your device name, ex. "A01"
  // -------------------------------------------------------------------
  #define DHTDATATOPIC "/dht/" ALIAS         // topic for dht
  #define DHTPIN    D7        // DHT data pin
  #define DHTTYPE   DHT22     // e.g. DHT11, DHT21, DHT22
  DHT dht(DHTPIN, DHTTYPE);
  WiFiClient client;
  int timer = 0;
  int lastDHTRead = 0;
  MicroGear microgear(client);


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
    /* Add Event listeners */

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
    dht.begin(); // initialize DHT Sensor
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
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
        ReadDHTandSend();

    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}

void ReadDHTandSend () {if(millis() - lastDHTRead > 2000){        // setup a 2-second period
    float humid = dht.readHumidity();     // read humidity
    float temp  = dht.readTemperature();  // read temperature
    lastDHTRead = millis();
          
    Serial.print("Humid: "); Serial.print(humid); Serial.print(" %, ");
    Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C ");
    
    if (isnan(humid) || isnan(temp)) { // check humid/temp is valid or not
      Serial.println("Failed to read from DHT sensor!");
    }
    else{
      // from a string in this format --> "{humid},{temp}"
      String datastring = (String)humid+","+(String)temp;
      Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(DHTDATATOPIC,datastring);             }
    }  
}
