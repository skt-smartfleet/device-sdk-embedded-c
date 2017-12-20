#ifndef SMARTFLEET_CLIENT_H_
#define SMARTFLEET_CLIENT_H_

#include <Arduino.h>
#include <Stream.h>
#include <Client.h>
#include <Udp.h>

#include "Config.h"
#include "wrapper/Smartfleet_Type.h"

#include "util/json/ArduinoJson.h"
#include "util/ntp/NTPClient.h"

#include "wrapper/MqttWrapper.h"
#include "wrapper/messageWrapper.h"

#define DEFAULT_BUF_SIZE 50
//#define DEFAULT_BUFFER_SIZE 256



typedef enum SF_ERROR
{
	ret_connection_fail = -5,
	ret_error = 0,
	ret_ok = 1,
};




typedef void (*onDeviceActivation_cb)(DeviceActivation da);
typedef void (*onFirmwareUpdate_cb)(FirmwareUpdate fu);
typedef void (*onOBDReset_cb)(const char* topic);
typedef void (*onDeviceSerialNumberCheck_cb)(const char* topic);
typedef void (*onClearDeviceData_cb)(const char* topic);
typedef void (*onFirmwareUpdateChunk_cb)(FirmwareUpdateChunk fuc);


class smartfleet : public NTPClient {

public:
	smartfleet(Client& client, UDP& udp) : NTPClient(udp, NTP_SERVER, NTP_TIMEZONE_OFFSET, NTP_INTERVAL_MS)
	{
		_client = &client;
		_udp = &udp;	
	}

	~smartfleet(){}
	
	static void onRPCMessageArrived(const char* topic, const char* payload);
	

	SF_ERROR setRPCCallback(onDeviceActivation_cb da = NULL, onFirmwareUpdate_cb fu = NULL, onOBDReset_cb odbr = NULL, onDeviceSerialNumberCheck_cb dsnc = NULL, onClearDeviceData_cb cdd = NULL, onFirmwareUpdateChunk_cb fuc = NULL);
	
	void superloop();


	void begin();
	SF_ERROR setMqttParam(const char* server_host, const int server_port, const char* user_name);
	SF_ERROR setMqttTopic(const char* pub_topic, const char* sub_topic);
	
	SF_ERROR isMqttConnectStatus( void );
	void pubtest(JsonObject& json, char* topic, int qos);
	
	SF_ERROR publishTrip(TripType eventType, int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, int fwv, int dtvt);
	SF_ERROR publishMicroTrip(TripType eventType, int tid, int fc, double lat, double lon, int lc, long clt, int cdit, int rpm, int sp, int em, int el, String xyz, double vv, int tpos);
	SF_ERROR publishHFDCapabilityInfomation(TripType eventType, int cm);
	SF_ERROR publishDiagnosticInfomation(TripType eventType, int tid, String dtcc, int dtck, int dtcs);
	SF_ERROR publishDrivingCollisionWarning(TripType eventType, int tid, double dclat, double dclon);
	SF_ERROR publishParkingCollisionWarning(TripType eventType, double pclat, double pclon);
	SF_ERROR publishBatteryWarning(TripType eventType, int wbv);
	SF_ERROR publishUnpluggedWarning(TripType eventType, int unpt, int pt);
	SF_ERROR publishTurnoffWarning(TripType eventType, String rs);

	SF_ERROR publishActivation(RPCType eventType, String vid, int upp, int engLiter, int fuelType, int misType, int cylinder);
	SF_ERROR publishReset(RPCType eventType);
	SF_ERROR publishSerial(RPCType eventType);
	SF_ERROR publishRadioUsage(RPCType eventType);
	SF_ERROR publishDeviceInfo(RPCType eventType);
	SF_ERROR publishClearData(RPCType eventType);
	SF_ERROR publishStopPush(RPCType eventType);
	SF_ERROR publishCarDBUpdate(RPCType eventType, int totSize, int chSize, int chInx, String pyl);
	SF_ERROR publishFwUpdate(RPCType eventType, int totSize, int chSize, int chInx, String pyl);
	SF_ERROR publishGetMicroTrip(RPCType eventType, int lastos);
	SF_ERROR publishGetTrip(RPCType eventType, int lastos);



private:
//	void clearProfile();
	//shared preference;
//	char _serverHost[DEFAULT_BUF_SIZE];
//	int  _serverPort;
//	char _userName[DEFAULT_BUF_SIZE];
//	char _topic[DEFAULT_BUF_SIZE];
	char* _pubTopic;
	char* _subTopic;
	
	
	//RPC Callback;
	onDeviceActivation_cb onDeviceActivation;
	onFirmwareUpdate_cb onFirmwareUpdate;
	onOBDReset_cb onOBDReset;
	onDeviceSerialNumberCheck_cb onDeviceSerialNumberCheck;
	onClearDeviceData_cb onClearDeviceData;
	onFirmwareUpdateChunk_cb onFirmwareUpdateChunk;


	Client* _client;
	UDP* _udp;
	mqttWrapper _mqttwrapper;

	unsigned long currentTime;
};

#endif /* SMARTFLEET_CLIENT_H_ */

