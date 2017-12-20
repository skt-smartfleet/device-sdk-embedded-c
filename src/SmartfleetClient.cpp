/*
 * SmartfleetClient.cpp
 *
 *  Created on: 2017. 12. 7.
 *      Author: Daniel
 */

#include "SmartfleetClient.h"

void smartfleet::superloop()
{
	_mqttwrapper.mqtt_yield();
	NTPClient::update();
}

SF_ERROR smartfleet::setMqttParam(const char* server_host, const int server_port, const char* user_name)
{
	_mqttwrapper.setHost(server_host);
	_mqttwrapper.setPort(server_port);
}

SF_ERROR smartfleet::setMqttTopic(const char* pub_topic, const char* sub_topic)
{
	_pubTopic = pub_topic;
	_subTopic = sub_topic;
	_mqttwrapper.setTopic(_subTopic);
}


void smartfleet::begin()
{
	_mqttwrapper.begin(*_client);
	_mqttwrapper.setMessageHandler(onRPCMessageArrived);
	
	NTPClient::begin();
	NTPClient::forceUpdate();
}

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

SF_ERROR smartfleet::setRPCCallback(onDeviceActivation_cb da, onFirmwareUpdate_cb fu, onOBDReset_cb odbr, onDeviceSerialNumberCheck_cb dsnc, onClearDeviceData_cb cdd, onFirmwareUpdateChunk_cb fuc)
{
	onDeviceActivation = da;
	onFirmwareUpdate = fu;
	onOBDReset = odbr;
	onDeviceSerialNumberCheck = dsnc;
	onClearDeviceData = cdd;
	onFirmwareUpdateChunk = fuc;
}

SF_ERROR smartfleet::isMqttConnectStatus( void )
{
	
}

void smartfleet::pubtest(JsonObject& json, char* topic, int qos)
{

	Serial.println("====PUBLISH====");
	Serial.println(topic);
	Serial.println(qos);

	json.prettyPrintTo(Serial);

	Serial.println();

}

SF_ERROR smartfleet::publishTrip(TripType eventType, int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, int fwv, int dtvt)
{
	Trip trip_obj(tid, stt, edt, dis, tdis, fc, stlat, stlon, edlat, edlon, ctp, coe, fct, hsts, mesp, idt, btv, gnv, wut, usm, est, fwv, dtvt);

	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	_mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime() , eventType, (void*)&trip_obj), _pubTopic, 0);

	return ret_ok;
}


