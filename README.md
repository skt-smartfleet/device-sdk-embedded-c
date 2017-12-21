#Arduino Source for T-RemotEye

본 코드는 Smart[Fleet] 기반 아두이노 SDK를 제공합니다.

1. Configure
-------------------------------
##### 1.1 MQTT Broker 정보

|Attribute | Value | Note |
| --- | --- | --- |
|IP | smartfleet.sktelecom.com |`MQTT_SERVER_HOST`|
|Port | 1883|`MQTT_SERVER_PORT`|
|UserName | 00000000000000011111 |`MQTT_USER_NAME`|


##### 1.2 MQTT 설정

|Attribute | Value | Note |
| --- | --- | --- |
|QoS | 1 |`qos`|
|Microtrip QoS | 0 |`microTripQos`|
|timeout | 15 |`timeout`|
|keepalive | 60 |`keepalive`|
|cleanSession | true | `setCleanSession(boolean)` |


`$library/src/Config.h`:

```
#define MQTT_SERVER_HOST "iot.eclipse.org"
#define MQTT_SERVER_PORT 1883
#define MQTT_USER_NAME "test_user"
#define MQTT_PASSWORD "password"

#define MQTT_PUBLISH_TOPIC "to/pi/cc/pub"
#define MQTT_SUBSCRIBE_TOPIC "to/pi/cc/rcv"
```

`$library/src/wrapper/MqttWrapper.h`:

```
void mqttWrapper::connect(const char* host, const int port, const char* username, const char* password)
{
	int ret = 0;
	char client[] = "5d354a80961d4256a29ed5f52c1b98d4";
	this->setHost(host);
	this->setPort(port);
	this->setUser(username, password);

	if(_network.connect((char*)_host, (int)_port) == 0)
	{
		DBG_P("TCP connection Fail");
	}

	_mqtt_opt.clientID.cstring = client;
	_mqtt_opt.username.cstring = (char*)username;
	_mqtt_opt.password.cstring = (char*)password;
	_mqtt_opt.keepAliveInterval = 120;
	_mqtt_opt.MQTTVersion = 4;

//	 optional will flag
//	_mqtt_opt.willFlag = 0x01;
//	_mqtt_opt.will.topicName.cstring = (char*)_topic;
//	_mqtt_opt.will.message.cstring = (char*)"offline";
//	_mqtt_opt.will.retained = 0x01;

	if(_mqtt->connect(_mqtt_opt) == 0)
	{
		DBG_P("Connect successfully");
	}
}
```

2. Code Guide
------------------------------------

T-RemotEye Proxy에 접속, 메시지 전송, RPC 요청 수신을 위해 SmartfleetClient Class를 제공한다.


`$library/src/SmartfleetClient.h`:

* 메시지 전송(Trip)


```
SF_ERROR smartfleet::publishTrip(TripType eventType, int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, int fwv, int dtvt)
{
	Trip trip_obj(tid, stt, edt, dis, tdis, fc, stlat, stlon, edlat, edlon, ctp, coe, fct, hsts, mesp, idt, btv, gnv, wut, usm, est, fwv, dtvt);

	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	_mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime() , eventType, (void*)&trip_obj), _pubTopic, 0);

	return ret_ok;
}

```


* RPC 요청 수신

```
static void smartfleet::onRPCMessageArrived(const char* topic, const char* payload)
{

	char* method;
	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(payload);

	arrivedRPCMessage arrivedRPCMessage;
	//arrivedRPCMessage.getMethod(root, method);
	method = root["method"];

	if(strcmp(method, "activationReq") == 0)
	{
		DeviceActivation da;
		arrivedRPCMessage.messageUnpackage(root, (void*)&da);
		
		//recv RPC callback
		DBG_P("Recv DeviceActivation");
		
		//onDeviceActivation(da);
	}
	else if(strcmp(method, "fwupdate") == 0)
	{
//		FirmwareUpdate fu;
//		arrivedRPCMessage.messageUnpackage(root, (void*)&fu);

	}
	else if(strcmp(method, "fwupchunk") == 0)
	{
//		FirmwareUpdateChunk fuc;
//		arrivedRPCMessage.messageUnpackage(root, (void*)&fuc);
	}
}

```


3. 아두이노 Connectivity
------------------------------

##### 3.1 Connectivity 선택

아두이노에서 지원하는 Ethernet, WiFi 중 사용할 Connectivity를 선택합니다.
이번 예제에서는 WizFi310 WiFi 모듈을 사용해 진행했습니다.

그 후 선택한 Connectivity의 아두이노 라이브러리를 설치합니다.


##### 3.2 Network 연결

각 Connectivity에 맞게 아두이노를 네트워크에 연결합니다.


`$examples/SmartFleet_Example.ino`:
```
// Initialize the WiFi object
WiFiClient client;
WiFiUDP udp;

Serial3.begin(115200);
WiFi.init(&Serial3);
WiFi.begin(ssid, pass);
```

4. API
------------------------------

##### 4.1 SmartfleetClient Init

SmartfeetClient로 서비스를 사용하기 위해 T-RemotEye Proxy의 MQTT 정보를 입력합니다.
Config.h 파일의 정보를 사용합니다.

`$examples/SmartFleet_Example.ino`:

```
smartfleet sf(client, udp);

sf.begin();
sf.setMqttParam(MQTT_SERVER_HOST, MQTT_SERVER_PORT, MQTT_USER_NAME);
sf.setMqttTopic(MQTT_PUBLISH_TOPIC, MQTT_SUBSCRIBE_TOPIC);

```
##### 4.3 Connect & Subscribe

MQTT Connect와 Subscribe는 superloop()에서 자동으로 수행합니다.

`$library/src/SmartfleetClient.cpp`:
```
void smartfleet::superloop()
{
	_mqttwrapper.mqtt_yield();
	NTPClient::update();
}
```

* Parameters
	- N/A

* Return
    - N/A


`$library/src/wrapper/MqttWrapper.cpp`:
```
void mqttWrapper::mqtt_yield()
{

	if( _mqtt->isConnected() == false )
	{
		DBG_P("Connecting to Broker..");

		this->connect();
		this->subscribeTopic(_topic, 0);
	}

    if(!_network.connected() && _mqtt->isConnected()) {
    	_mqtt->disconnect();
    }

	_mqtt->yield(3000);
}
```


##### 4.3 Publish

###### 4.3.1 Trip

```
SF_ERROR publishTrip(TripType eventType, int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, int fwv, int dtvt);
```

* Parameters
	- eventType: Trip Event Type
    - tid ~ dtvt: Trip 메시지

* Return
	- SUCCESS: 1
	- FAIL: 0

