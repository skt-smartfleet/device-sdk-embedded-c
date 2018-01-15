
## Arduino Source for Smart[Fleet]

본 코드는 Smart[Fleet] 기반의 아두이노 SDK(C++)를 제공합니다.

<br>
1. Configure

##### 1.1 MQTT Broker 정보

|Attribute | Value | Note |
| --- | --- | --- |
|Host Name | smartfleet.sktelecom.com |`MQTT_SERVER_HOST`|
|Port | 1883|`MQTT_SERVER_PORT`|
|UserName | 00000000000000000001 |`MQTT_USER_NAME`|



##### 1.2 MQTT 설정

|Attribute | Value | Note |
| --- | --- | --- |
|QoS | 1 |`MQTT_QOS`|
|Microtrip QoS | 0 |`MQTT_MICROTRIP_QOS`|
|timeout | 15 |`MQTT_TIMEOUT_S`|
|keepalive | 60 |`MQTT_KEEP_ALIVE_TIME_S`|


##### 1.3 NTP 설정

|Attribute | Value | Note |
| --- | --- | --- |
|Interval | 60 |`NTP_INTERVAL_S`|
|Timezone | 9 |`NTP_TIMEZONE_OFFSET_H`|
|NTP Server | pool.ntp.org |`NTP_SERVER`|



`$SmartfleetClient/examples/SmartFleet_Example/SmartFleet_Example.ino`:
```
#define MQTT_SERVER_HOST "smartfleet.sktelecom.com"
#define MQTT_SERVER_PORT 1883
#define MQTT_USER_NAME "00000000000000000001"
```

`$SmartfleetClient/src/wrapper/Smartfleet_Type.h`:
```
/**
 * @brief Smartfleet MQTT option
 */

#define MQTT_QOS 1
#define MQTT_MICROTRIP_QOS 0
#define MQTT_TIMEOUT_S 15
#define MQTT_KEEP_ALIVE_TIME_S 60

/**
 * @brief Network Time Protocol option
 */
#define NTP_INTERVAL_S 60       		/// update interval(sec)
#define NTP_TIMEZONE_OFFSET_H 9  		/// UTC+9   Korea
#define NTP_SERVER "pool.ntp.org"		/// NTP Server
```
<br>
2. Example
------------------------------------

`$SmartfleetClient/examples/SmartFleet_Example/SmartFleet_Example.ino`:

##### 네트워크 연결
`Wi-Fi`, `Ethernet` 등 Arduino 에서 사용가능한 네트워크 실드를 사용해야 합니다.

<br>
###### WiFi TCP Client, UDP Object 생성
MQTT에 사용할 TCP Client로 사용할 `client` object와 NTP time protocol에서 사용할 `udp` object를 생성합니다.
```
WiFiClient client;
WiFiUDP udp;
```

<br>
###### WiFi Serial init
네트워크 실드를 사용하기 위해서 `init` 과정을 거칩니다. 본 예제에서는 Wi-Fi 실드를 사용했습니다.
```
Serial3.begin(115200);
WiFi.init(&Serial3);
```

<br>
###### Network 연결 절차
`WiFi.begin` 함수로 네트워크 연결 준비를 합니다.

```
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

```

<br><br>
#### Smart[Fleet] Client

<br>
###### Smart[Fleet] Object 생성
```
smartfleet sf(client, udp);
```

<br>
###### Smart[Fleet] init & RPC callback 등록
```
sf.begin();
sf.setRPCCallback(RPCDeviceActivation, RPCFirmwareUpdate, RPCOBDReset, RPCDeviceSerialNumberCheck, RPCClearDeviceData, RPCFirmwareUpdateChunk, RPCVendorSpecific);
```

<br>
###### Smart[Fleet] 연결

```
sf.connectSmartFleet(MQTT_SERVER_HOST, MQTT_SERVER_PORT, MQTT_USER_NAME);
```

<br>
###### Smart[Fleet] Process loop
응용 프로그램에서 수행하며, `MQTT`와 `NTP`, `RPC` 메시지 처리등을 aync로 처리합니다.
```
sf.superloop();
```

<br>
###### Smart[Fleet] send Trip 메시지

Trip 메시지를 전송할 때는 각각의 함수를 사용합니다.

```
sf.sendMicroTrip(223, 11, 12.33, 44.33, 66, 3434, 88, 43, 87, 77, 66, "xyzzz", 3344.22, 42);
sf.sendTrip(123, 223, 2234, 66, 234, 88, 9998.997, 8888.8888, 777.332, 666.111, 555, 32324, 333, 2222, 23, 2222, 33.3423, 444.22, 555, 77, 77, "12ffsdf3", 77);
sf.sendDiagnosticInfomation(1, "AA", 0, 2);
sf.sendBatteryWarning(232);
sf.sendUnpluggedWarning(888, 777);
sf.sendTurnoffWarning("test");
sf.sendHFDCapabilityInfomation(3945);
sf.sendDrivingCollisionWarning(999, 3321.332, 834.22);
sf.sendParkingCollisionWarning(123.333, 456.777);
```

<br>
###### Smart[Fleet] RPC 메시지 callback (DeviceActivation)

`setRPCCallback` 함수를 사용해 callback을 등록했다면 아래와 같이 RPC 메시지를 수신할 수 있습니다.

```
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

  char resultTopic[64];
  sprintf(resultTopic, "%s%s", topic, request_id);
  sf.resultDeviceActivation("vehicle_id", resultTopic);
}
```

<br><br><br>
3. Smartfleet API
------------------------------------
`Smart[Fleet]` Proxy에 접속, 메시지 전송, RPC 요청 수신을 위해 `SmartfleetClient` Class를 제공합니다.

`$SmartfleetClient/src/SmartfleetClient.h`:

##### 3.1 Return code

| code | description |
| --- | --- |
| -6 | `RET_ERROR_PROCESS_OVERFLOW` |
| -5 | `RET_ERROR_MQTT_CONNECTION_FAIL` |
| -4 | `RET_ERROR_MQTT_SUBSCRIBE_FAIL`|
| -3 | `RET_ERROR_TRIP_SEND_FAIL` |
| -2 | `RET_ERROR_RESPONSE_SEND_FAIL` |
| -1 | `RET_ERROR_RESULT_SEND_FAIL` |
| 0 | `RET_NOT_CONNECTED`  |
| 1 | `RET_SUCCESS` |

<br>
##### 3.2 Smartfleet Function

###### superloop
>SmartfleetClient의 MQTT, NTP등 주요 기능들을 non-blocking으로 수행합니다.
응용프로그램에서 주기적으로 실행해주어야 합니다.

>@param `void`
>@return `void`

```
void superloop(void);
```

<br>
###### begin
>SmartfleetClient init 함수 MQTT, NTP init

>@param `void`
>@return `void`

```
void begin(void);
```

<br>
###### setRPCCallback
>RPC 메시지 수신시  user callback을 등록하는 함수

>@param RPC user callback
>@param :`$da` / `$fu` / `$odbr` / `$dsnc` / `$cdd` / `$da` / `$fuc` / `$vs`
>@return :`void`

```
void setRPCCallback(onDeviceActivation_cb da = NULL, onFirmwareUpdate_cb fu = NULL, onOBDReset_cb odbr = NULL, onDeviceSerialNumberCheck_cb dsnc = NULL, onClearDeviceData_cb cdd = NULL, onFirmwareUpdateChunk_cb fuc = NULL, onVendorSpecific_cb vs = NULL);
```

<br>
###### connectSmartFleet
>smartfleet으로 MQTT를 연결하고 RPC Topic 구독합니다.

>@param :`$mqtt_host` / `$mqtt_port` / `$mqtt_username` / `$mqtt_password`
>@return :`RET_ERROR_MQTT_CONNECTION_FAIL` / `RET_ERROR_MQTT_SUBSCRIBE_FAIL` / `RET_SUCCESS`

```
SF_ERROR connectSmartFleet(const char* mqtt_host, const int mqtt_port, const char* mqtt_username, const char* mqtt_password = NULL);
```

<br>
###### disconnectSmartFleet
>smartfleet 연결 해제합니다.

>@param : `void`
>@return : `RET_ERROR_MQTT_CONNECTION_FAIL` / `RET_SUCCESS`

```
SF_ERROR disconnectSmartFleet(void);
```

<br>
###### isMqttConnectStatus
>smartfleet 연결 상태 확인

>@param : `void`
>@return : `RET_NOT_CONNECTED` / `RET_SUCCESS`

```
SF_ERROR isMqttConnectStatus(void);
```

<br>
###### Trip Object 전송
>Trip 메시지를 Object로 전송합니다.

>@param : 각 메시지별 `Obj`
>@return : `RET_ERROR_PROCESS_OVERFLOW` / `RET_ERROR_TRIP_SEND_FAIL` , `RET_SUCCESS`

```
SF_ERROR sendTrip(Trip Obj);
SF_ERROR sendMicroTrip(MicroTrip Obj);
SF_ERROR sendHFDCapabilityInfomation(HFDCapabilityInfomation Obj);
SF_ERROR sendDiagnosticInfomation(DiagnosticInfomation Obj);
SF_ERROR sendDrivingCollisionWarning(DrivingCollisionWarning Obj);
SF_ERROR sendParkingCollisionWarning(ParkingCollisionWarning Obj);
SF_ERROR sendBatteryWarning(BatteryWarning Obj);
SF_ERROR sendUnpluggedWarning(UnpluggedWarning Obj);
SF_ERROR sendTurnoffWarning(TurnoffWarning Obj);

```

<br>
###### Trip 메시지 raw parameters 전송
>Trip 메시지를 raw parameter로 전송합니다.

>@param : 각 메시지별 raw parameters
>@return : `RET_ERROR_PROCESS_OVERFLOW` / `RET_ERROR_TRIP_SEND_FAIL` , `RET_SUCCESS`

```
SF_ERROR sendTrip(int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, char* fwv, int dtvt);

SF_ERROR sendMicroTrip(int tid, int fc, double lat, double lon, int lc, long clt, int cdit, int rpm, int sp, int em, int el, char* xyz, double vv, int tpos);

SF_ERROR sendHFDCapabilityInfomation(int cm);

SF_ERROR sendDiagnosticInfomation(int tid, char* dtcc, int dtck, int dtcs);

SF_ERROR sendDrivingCollisionWarning(int tid, double dclat, double dclon);

SF_ERROR sendParkingCollisionWarning(double pclat, double pclon);

SF_ERROR sendBatteryWarning(int wbv);

SF_ERROR sendUnpluggedWarning(int unpt, int pt);

SF_ERROR sendTurnoffWarning(char* rs);
```


<br>
###### isRPCMessage
>RPC 요청 수신시 유저 callback을 실행합니다.

>@param : `void`
>@return : `true`(RPC 수신시)/`false`(비 수신시)

```
SF_ERROR isRPCMessage(void);
```

<br>
###### RPC Response
>RPC 요청에 대한 response를 자동으로 전송합니다.

>@param : `$topic` response topic
>@return : `RET_ERROR_PROCESS_OVERFLOW` / `RET_ERROR_RESPONSE_SEND_FAIL` / `RET_SUCCESS`

```
SF_ERROR responseDeviceActivation(const char* topic);
SF_ERROR responseFirmwareUpdate(const char* topic);
SF_ERROR responseOBDReset(const char* topic);
SF_ERROR responseDeviceSerialNumberCheck(const char* topic);
SF_ERROR responseClearDeviceData(const char* topic);
SF_ERROR responseFirmwareUpdateChunk(const char* topic);

```

<br>
###### RPC Result
>RPC 요청을 처리하고 요청에 대한 result를 전송합니다.

>@param : `$topic` result topic
>@return : `RET_ERROR_PROCESS_OVERFLOW` / `RET_ERROR_RESULT_SEND_FAIL` / `RET_SUCCESS`

```
SF_ERROR resultDeviceActivation(const char* vid, const char* topic);
SF_ERROR resultFirmwareUpdate(const char* topic);
SF_ERROR resultOBDReset(const char* topic);
SF_ERROR resultDeviceSerialNumberCheck(const char* sn, const char* topic);
SF_ERROR resultClearDeviceData(const char* topic);
SF_ERROR resultFirmwareUpdateChunk(const char* topic);

```

<br><br><br>
4. Config Library
------------------------------------
수정이 필요한 경우 수정할 포인트는 다음과 같습니다.

##### 4.1 Log/Debug 메시지 프린트

아래 Define 된 `_PRINTLOG_`의 값을 수정해 디버그 레벨을 조정할 수 있습니다.

| value | Description |
| --- | --- |
| 1 | Log Print |
| 2 | Debug + Log Print |

`$SmartfleetClient/src/util/LogPrint.h`:
```
/**
 * @brief _PRINTLOG_으로  디버그 프린트
 *        1: LOG Print
 *        2: Debug Print
 */

#define _PRINTLOG_ 2
```

<br>
##### 4.2 Vendor Specific RPC 추가

Vendor Specifig RPC를 사용할 경우 원하는 method를 아래 경로에서 수정할 수 있습니다.

`$SmartfleetClient/src/wrapper/Smartfleet_Type.h`:
```
#define VENDOR_SPECIFIC_STR 			"test"
```
