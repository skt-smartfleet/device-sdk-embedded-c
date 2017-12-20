#include <WizFi310.h>
#include <WizFi310Udp.h>
#include <WizFi310Client.h>

#include <SmartfleetClient.h>

char ssid[] = "Dap";            // your network SSID (name)
char pass[] = "00001111";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// Initialize the WiFi object
WiFiClient client;
WiFiUDP udp;

smartfleet sf(client, udp);

void associate();
static void RPCDeviceActivation(DeviceActivation da);

void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  //    WizFi310
  Serial3.begin(115200);
  WiFi.init(&Serial3);
    
  associate();
 
  sf.begin();
  sf.setMqttParam(MQTT_SERVER_HOST, MQTT_SERVER_PORT, MQTT_USER_NAME);
  sf.setMqttTopic(MQTT_PUBLISH_TOPIC, MQTT_SUBSCRIBE_TOPIC);

//  sf.setRPCCallback(RPCDeviceActivation);
}

void loop()
{
    static long prev = millis();
    if((prev + 10000) < millis())
    {
      Serial.println("10 sec");

      sf.publishTrip(TRIP_TRIP, 123, 4444, 55555, 66, 777, 88, 9998.997, 8888.8888, 777.7777, 666.666, 555, 4444444, 333, 2222, 1111, 2222, 33.3333, 444.4444, 555, 77, 77, 77, 77);
      prev = millis();
    }
    else
    {
      sf.superloop();
    }
}


static void RPCDeviceActivation(DeviceActivation da)
{
  Serial.println("========== Devica Activation ==========");
  Serial.print("vid = ");
  Serial.println(da.vid);
  Serial.print("upp = ");
  Serial.println(da.upp);
  Serial.print("elt = ");
  Serial.println(da.elt);
  Serial.print("fut = ");
  Serial.println(da.fut);
  Serial.print("mty = ");
  Serial.println(da.mty);
  Serial.println("=======================================");
}


void associate()
{
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
  
  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

