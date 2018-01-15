#include <Arduino.h>
#include <WizFi310.h>
#include <WizFi310Udp.h>
#include <WizFi310Client.h>

#include <SmartfleetClient.h>

char ssid[] = "SSID";            // your network SSID (name)
char pass[] = "PASSWORD";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

IPAddress ip(192,168,1,12);
#define MQTT_SERVER_HOST "iot.eclipse.org"
#define MQTT_SERVER_PORT 1883
#define MQTT_USER_NAME "00000000000000000001"

// Initialize the WiFi object
WiFiClient client;
WiFiUDP udp;

smartfleet sf(client, udp);

void associate();
void sendTripProcess(int step);

// callback function
void RPCDeviceActivation(const char* topic, const char* request_id, const char* method, void* message);
void RPCFirmwareUpdate(const char* topic, const char* request_id, const char* method, void* message);
void RPCOBDReset(const char* topic, const char* request_id, const char* method, void* message);
void RPCDeviceSerialNumberCheck(const char* topic, const char* request_id, const char* method, void* message);
void RPCClearDeviceData(const char* topic, const char* request_id, const char* method, void* message);
void RPCFirmwareUpdateChunk(const char* topic, const char* request_id, const char* method, void* message);
void RPCVendorSpecific(const char* topic, const char* request_id, const char* method, void* message);

void description_cert();

void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  //WizFi310
  Serial3.begin(115200);
  WiFi.init(&Serial3);
    
  associate();

  sf.begin();
  sf.setRPCCallback(RPCDeviceActivation, RPCFirmwareUpdate, RPCOBDReset, RPCDeviceSerialNumberCheck, RPCClearDeviceData, RPCFirmwareUpdateChunk, RPCVendorSpecific);

  sf.connectSmartFleet(ip, MQTT_SERVER_PORT, MQTT_USER_NAME);

  Serial.println("\r\npress \'h\' to print how to test");
}

void loop()
{

	if(Serial.available())
	{
		char c = (char)Serial.read();

		if(c >= '1' && c <= '9')
		{
			sendTripProcess((int)(c-'0'));
		}
		else if( c == 'h' || c == 'H')
		{
			description_cert();
		}
	}

	sf.superloop();
}

void sendTripProcess(int step)
{
	switch(step)
	{
	case 1:
	{
		sf.sendMicroTrip(223, 11, 12.33, 44.33, 66, 3434, 88, 43, 87, 77, 66, "xyzzz", 3344.22, 42);
		break;
	}
	case 2:
	{
		sf.sendTrip(123, 223, 2234, 66, 234, 88, 9998.997, 8888.8888, 777.332, 666.111, 555, 32324, 333, 2222, 23, 2222, 33.3423, 444.22, 555, 77, 77, "12ffsdf3", 77);
		break;
	}
	case 3:
	{
		sf.sendDiagnosticInfomation(1, "AA", 0, 2);
		break;
	}
	case 4:
	{
		sf.sendBatteryWarning(232);
		break;
	}
	case 5:
	{
		sf.sendUnpluggedWarning(888, 777);
		break;
	}
	case 6:
	{
		sf.sendTurnoffWarning("daniel");
		break;
	}
	case 7:
	{
		sf.sendHFDCapabilityInfomation(3945);
		break;
	}
	case 8:
	{
		sf.sendDrivingCollisionWarning(999, 3321.332, 834.22);
		break;
	}
	case 9:
	{
		sf.sendParkingCollisionWarning(123.333, 456.777);
		break;
	}
	default:
		break;
	}

}


void RPCDeviceActivation(const char* topic, const char* request_id, const char* method, void* message)
{
  Serial.println("========== Device Activation ==========");
  Serial.print("topic  ");
  Serial.println(topic);
  Serial.print("request_id  ");
  Serial.println(request_id);
  Serial.print("method  ");
  Serial.println(method);
  Serial.print("message  ");
  DeviceActivation* da = (DeviceActivation*) message;
  Serial.println(da->vid);
  Serial.println(da->upp);
  Serial.println(da->elt);
  Serial.println(da->fut);
  Serial.println(da->cyl);
  Serial.println(da->mty);
  Serial.println("=======================================");

  char resultTopic[128];
  sprintf(resultTopic, "%s%s", topic, request_id);
  sf.resultDeviceActivation("250660", resultTopic);
}


void RPCFirmwareUpdate(const char* topic, const char* request_id, const char* method, void* message)
{
	Serial.println("========== Firmware Update ==========");
	Serial.print("topic  ");
	Serial.println(topic);
	Serial.print("request_id  ");
	Serial.println(request_id);
	Serial.print("method  ");
	Serial.println(method);
	Serial.print("message  ");
	FirmwareUpdate* fu = (FirmwareUpdate*) message;
	Serial.println(fu->pkv);
	Serial.println(fu->url);
	Serial.println("=======================================");

	char resultTopic[128];
	sprintf(resultTopic, "%s%s", topic, request_id);
	sf.resultFirmwareUpdate(resultTopic);
}

void RPCOBDReset(const char* topic, const char* request_id, const char* method, void* message)
{
	Serial.println("========== OBD Reset ==========");
	Serial.print("topic  ");
	Serial.println(topic);
	Serial.print("request_id  ");
	Serial.println(request_id);
	Serial.print("method  ");
	Serial.println(method);
	Serial.println("=======================================");

	char resultTopic[128];
	sprintf(resultTopic, "%s%s", topic, request_id);
	sf.resultOBDReset(resultTopic);
}

void RPCDeviceSerialNumberCheck(const char* topic, const char* request_id, const char* method, void* message)
{
	Serial.println("========== Device Serial Number Check ==========");
	Serial.print("topic  ");
	Serial.println(topic);
	Serial.print("request_id  ");
	Serial.println(request_id);
	Serial.print("method  ");
	Serial.println(method);
	Serial.println("=======================================");

	char resultTopic[128];
	sprintf(resultTopic, "%s%s", topic, request_id);
	sf.resultDeviceSerialNumberCheck("1234567890",resultTopic);
}

void RPCClearDeviceData(const char* topic, const char* request_id, const char* method, void* message)
{
	Serial.println("========== Clear Device Data ==========");
	Serial.print("topic  ");
	Serial.println(topic);
	Serial.print("request_id  ");
	Serial.println(request_id);
	Serial.print("method  ");
	Serial.println(method);
	Serial.println("=======================================");

	char resultTopic[128];
	sprintf(resultTopic, "%s%s", topic, request_id);
	sf.resultClearDeviceData(resultTopic);
}

void RPCFirmwareUpdateChunk(const char* topic, const char* request_id, const char* method, void* message)
{
	Serial.println("========== Firmware Update Chunk ==========");
	Serial.print("topic  ");
	Serial.println(topic);
	Serial.print("request_id  ");
	Serial.println(request_id);
	Serial.print("method  ");
	Serial.println(method);
	Serial.print("message  ");
	FirmwareUpdateChunk* fuc = (FirmwareUpdateChunk*) message;
	Serial.println(fuc->tsz);
	Serial.println(fuc->pyd);
	Serial.println("=======================================");

	char resultTopic[128];
	sprintf(resultTopic, "%s%s", topic, request_id);
	sf.resultFirmwareUpdateChunk(resultTopic);

}

void RPCVendorSpecific(const char* topic, const char* request_id, const char* method, void* message)
{
	Serial.println("========== Vendor Specific ==========");
	Serial.print("topic  ");
	Serial.println(topic);
	Serial.print("request_id  ");
	Serial.println(request_id);
	Serial.print("method  ");
	Serial.println(method);
	Serial.print("message  ");
	Serial.println((char*)message);
	Serial.println("=======================================");

}

void associate()
{
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
//    status = WiFi.begin(ssid);
  }
  
  // you're connected now, so print out the data
  Serial.println(F("You're connected to the network"));
  
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print(F("Signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}

void description_cert()
{
	Serial.println();
	Serial.println(F("=== SmartFleet Certification Test Description ==="));
	Serial.println(F("> SF-CON-VT-01 : Device will be connected to SmartFleet with Function \"connectSmartFleet\""));
	Serial.println(F("> SF-CON-VT-02 : Auto Subscription Topic after MQTT Connection in Function \"connectSmartFleet\""));

	Serial.println(F("> SF-REG-VT-01 : Can be received REG message after MQTT Subscription"));
	Serial.println(F("> SF-REG-VT-02 : Can be received REG message after MQTT Subscription"));

	Serial.println(F("> SF-DU-VT-01 : Press \'1\' to send MicroTrip"));
	Serial.println(F("> SF-DU-VT-02 : Press \'2\' to send Trip"));

	Serial.println(F("> SF-EV-VT-01 : Press \'3\' to send DiagnosticInfo"));
	Serial.println(F("> SF-EV-VT-02 : Press \'4\' to send BatteryWarning"));
	Serial.println(F("> SF-EV-VT-03 : Press \'5\' to send UnpluggedWarning"));
	Serial.println(F("> SF-EV-VT-04 : Press \'6\' to send TurnoffWarning"));

	Serial.println(F("> SF-RPC-VT-01 : Can be received REG message after MQTT Subscription"));
	Serial.println(F("> SF-RPC-VT-02 : Can be received REG message after MQTT Subscription"));
	Serial.println(F("> SF-RPC-VT-03 : Can be received REG message after MQTT Subscription"));
	Serial.println();
}
