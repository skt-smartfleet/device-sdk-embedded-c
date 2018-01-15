#include "SmartfleetClient.h"


void smartfleet::superloop()
{
	_mqttwrapper.mqtt_yield();
	isRPCMessage();
	NTPClient::update();
}

void smartfleet::begin()
{
	_mqttwrapper.begin(*_client);
	_mqttwrapper.setMessageHandler(onRPCMessageArrived);

	NTPClient::begin();
	NTPClient::forceUpdate();

	_state = STATE_NOTCONNECTED;
}

SF_ERROR smartfleet::connectSmartFleet(IPAddress mqtt_ip, const int mqtt_port, const char* mqtt_username, const char* mqtt_password = NULL)
{
	int ret;
	char mqtt_client_id[30] = {0,};

	sprintf(mqtt_client_id, "TRE%lu",NTPClient::getEpochTime());

	ret = _mqttwrapper.connect(mqtt_ip, mqtt_port, mqtt_client_id, mqtt_username, "");

	if(ret != MQTT::SUCCESS)
	{
		return RET_ERROR_MQTT_CONNECTION_FAIL;
	}

	_mqttwrapper.setSubscribeTopic(SUBSCRIBE_TOPIC);
	ret = _mqttwrapper.subscribeTopic(SUBSCRIBE_TOPIC, 0);

	if(ret != MQTT::SUCCESS)
	{
		return RET_ERROR_MQTT_SUBSCRIBE_FAIL;
	}

	return RET_SUCCESS;
}

SF_ERROR smartfleet::connectSmartFleet(const char* mqtt_host, const int mqtt_port, const char* mqtt_username, const char* mqtt_password = NULL)
{
	int ret;
	char mqtt_client_id[30] = {0,};

	sprintf(mqtt_client_id, "TRE%lu",NTPClient::getEpochTime());

	ret = _mqttwrapper.connect(mqtt_host, mqtt_port, mqtt_client_id, mqtt_username, "");

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_MQTT_CONNECTION_FAIL;
	}

	_mqttwrapper.setSubscribeTopic(SUBSCRIBE_TOPIC);
	ret = _mqttwrapper.subscribeTopic(SUBSCRIBE_TOPIC, 0);

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_MQTT_SUBSCRIBE_FAIL;
	}

	return RET_SUCCESS;
}

SF_ERROR smartfleet::disconnectSmartFleet()
{
	int ret;
	ret = _mqttwrapper.disconnect();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_MQTT_CONNECTION_FAIL;
	}

	_state = STATE_NOTCONNECTED;
	return RET_SUCCESS;
}



int smartfleet::isRPCMessage()
{
	char topic[128] = {0,};

	if( isIdleState() == false ) return false;

	RPCType rpc_type = getRPCType();

	switch(rpc_type)
	{
	case RSP_NULL:
		return false;
	case DEVICE_ACTIVATION:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		responseDeviceActivation(topic);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, DEVICE_ACTIVATION_STR, (void*)&g_da);
		g_da.clear();
		break;
	}
	case FIRMWARE_UPDATE:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		responseFirmwareUpdate(topic);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, FIRMWARE_UPDATE_STR, (void*)&g_fu);
		g_fu.clear();
		break;
	}
	case ODB_RESET:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		responseOBDReset(topic);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, OBD_RESET_STR, NULL);
		memset(g_buffer, 0, sizeof(g_buffer));
		break;
	}
	case DEVICE_SERIAL_NUMBER_CHECK:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		responseDeviceSerialNumberCheck(topic);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, DEVICE_SERIAL_NUMBER_CHECK_STR, NULL);
		memset(g_buffer, 0, sizeof(g_buffer));
		break;
	}
	case CLEAR_DEVICE_DATA:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		responseClearDeviceData(topic);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, CLEAR_DEVICE_DATA_STR, NULL);
		memset(g_buffer, 0, sizeof(g_buffer));
		break;
	}
	case FIRMWARE_UPDATE_CHUNK:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		responseFirmwareUpdateChunk(topic);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, FIRMWARE_UPDATE_CHUNK_STR, (void*)&g_fuc);
		g_fuc.clear();
		break;
	}
	case VENDOR_SPECIFIC:
	{
		sprintf(topic, "%s%s", RPC_RESONSE_TOPIC, g_req_id);
		RPCState[rpc_type].callback(RPC_RESULT_TOPIC, g_req_id, VENDOR_SPECIFIC_STR, (void*)g_buffer);
		memset(g_buffer, 0, sizeof(g_buffer));
		break;
	}
	default:
		break;
	}

	setRPCType(RSP_NULL);
	return true;
}

void smartfleet::setRPCCallback(onDeviceActivation_cb da, onFirmwareUpdate_cb fu, onOBDReset_cb odbr, onDeviceSerialNumberCheck_cb dsnc, onClearDeviceData_cb cdd, onFirmwareUpdateChunk_cb fuc, onVendorSpecific_cb vs)
{
	RPCState[DEVICE_ACTIVATION].callback = da;
	RPCState[FIRMWARE_UPDATE].callback = fu;
	RPCState[ODB_RESET].callback = odbr;
	RPCState[DEVICE_SERIAL_NUMBER_CHECK].callback = dsnc;
	RPCState[CLEAR_DEVICE_DATA].callback = cdd;
	RPCState[FIRMWARE_UPDATE_CHUNK].callback = fuc;
	RPCState[VENDOR_SPECIFIC].callback = vs;
}

SF_ERROR smartfleet::isMqttConnectStatus( void )
{
	if (_mqttwrapper.isConnected() == true )
		return RET_SUCCESS;
	else
		return RET_NOT_CONNECTED;
}

SF_ERROR smartfleet::sendTrip(Trip Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), TRIP, (void*)&Obj), PUBLISH_TOPIC_TRE, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send Trip"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendTrip(int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, char* fwv, int dtvt)
{
	Trip trip_obj(tid, stt, edt, dis, tdis, fc, stlat, stlon, edlat, edlon, ctp, coe, fct, hsts, mesp, idt, btv, gnv, wut, usm, est, fwv, dtvt);
	return this->sendTrip(trip_obj);
}

SF_ERROR smartfleet::sendMicroTrip(MicroTrip Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), MICRO_TRIP, (void*)&Obj), PUBLISH_TOPIC_TRE, MQTT_MICROTRIP_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send Microtrip"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendMicroTrip(int tid, int fc, double lat, double lon, int lc, long clt, int cdit, int rpm, int sp, int em, int el, char* xyz, double vv, int tpos)
{
	MicroTrip microtrip_obj(tid, fc, lat, lon, lc, clt, cdit, rpm, sp, em, el, xyz, vv, tpos);
	return this->sendMicroTrip(microtrip_obj);
}

SF_ERROR smartfleet::sendHFDCapabilityInfomation(HFDCapabilityInfomation Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), HFD_CAPABILITY_INFORMATION, (void*)&Obj), PUBLISH_TOPIC_TELEMETRY, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send HFDCapabilityInfomation"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendHFDCapabilityInfomation(int cm)
{
	HFDCapabilityInfomation hfd_obj(cm);
	return this->sendHFDCapabilityInfomation(hfd_obj);
}

SF_ERROR smartfleet::sendDiagnosticInfomation(DiagnosticInfomation Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), DIAGNOSTIC_INFORMATION, (void*)&Obj), PUBLISH_TOPIC_TELEMETRY, MQTT_QOS);

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send DiagnosticInfomation"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendDiagnosticInfomation(int tid, char* dtcc, int dtck, int dtcs)
{
	DiagnosticInfomation diagInfo_obj(tid, dtcc, dtck, dtcs);
	return this->sendDiagnosticInfomation(diagInfo_obj);
}

SF_ERROR smartfleet::sendDrivingCollisionWarning(DrivingCollisionWarning Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), DRIVING_COLLISION_WARNING, (void*)&Obj), PUBLISH_TOPIC_TELEMETRY, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send DrivingCollisionWarning"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendDrivingCollisionWarning(int tid, double dclat, double dclon)
{
	DrivingCollisionWarning drivingCollisionWarning_obj(tid, dclat, dclon);
	return this->sendDrivingCollisionWarning(drivingCollisionWarning_obj);
}

SF_ERROR smartfleet::sendParkingCollisionWarning(ParkingCollisionWarning Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), PARKING_COLLISION_WARNING, (void*)&Obj), PUBLISH_TOPIC_TELEMETRY, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send ParkingCollisionWarning"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendParkingCollisionWarning(double pclat, double pclon)
{
	ParkingCollisionWarning parkingCollisionWarning_obj(pclat, pclon);
	return this->sendParkingCollisionWarning(parkingCollisionWarning_obj);
}

SF_ERROR smartfleet::sendBatteryWarning(BatteryWarning Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), BATTERY_WARNING, (void*)&Obj), PUBLISH_TOPIC_ATTRIBUTES, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send BatteryWarning"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendBatteryWarning(int wbv)
{
	BatteryWarning batteryWarning_obj(wbv);
	return this->sendBatteryWarning(batteryWarning_obj);
}

SF_ERROR smartfleet::sendUnpluggedWarning(UnpluggedWarning Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), UNPLUGGED_WARNING, (void*)&Obj), PUBLISH_TOPIC_ATTRIBUTES, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send UnpluggedWarning"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendUnpluggedWarning(int unpt, int pt)
{
	UnpluggedWarning unpluggedWarning_obj(unpt, pt);
	return this->sendUnpluggedWarning(unpluggedWarning_obj);
}

SF_ERROR smartfleet::sendTurnoffWarning(TurnoffWarning Obj)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_TRIP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	tripMessage tripMessage;
	ret = _mqttwrapper.publish(tripMessage.messagePackage(root, NTPClient::getEpochTime(), TURNOFF_WARNING, (void*)&Obj), PUBLISH_TOPIC_ATTRIBUTES, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_TRIP_SEND_FAIL;
	}

	PRINT_LOG(F("Send TurnoffWarning"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::sendTurnoffWarning(char* rs)
{
	TurnoffWarning turnoffWarning_obj(rs);
	return this->sendTurnoffWarning(turnoffWarning_obj);
}


////////////////////////////////////////////////////////////////////////////////

SF_ERROR smartfleet::resultDeviceActivation(const char* vid, const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	RPCDeviceActivation da_obj(vid);

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	rpcMessage rpcMessage;

	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESULT_CODE, DEVICE_ACTIVATION, (void*)&da_obj), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESULT_SEND_FAIL;
	}

	PRINT_LOG(F("Send Result DeviceActivation"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::resultFirmwareUpdate(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	rpcMessage rpcMessage;

	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESULT_CODE, FIRMWARE_UPDATE), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESULT_SEND_FAIL;
	}

	PRINT_LOG(F("Send Result FirmwareUpdate"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::resultOBDReset(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	rpcMessage rpcMessage;

	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESULT_CODE, ODB_RESET), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESULT_SEND_FAIL;
	}

	PRINT_LOG(F("Send Result OBDReset"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::resultDeviceSerialNumberCheck(const char* sn, const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	RPCDeviceSerialNumberCheck dsnc_obj(sn);

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	rpcMessage rpcMessage;

	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESULT_CODE, DEVICE_SERIAL_NUMBER_CHECK, (void*)&dsnc_obj), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESULT_SEND_FAIL;
	}

	PRINT_LOG(F("Send Result DeviceSerialNumberCheck"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::resultClearDeviceData(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	rpcMessage rpcMessage;

	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESULT_CODE, CLEAR_DEVICE_DATA), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESULT_SEND_FAIL;
	}

	PRINT_LOG(F("Send Result ClearDeviceData"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::resultFirmwareUpdateChunk(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	rpcMessage rpcMessage;

	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESULT_CODE, FIRMWARE_UPDATE_CHUNK), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESULT_SEND_FAIL;
	}

	PRINT_LOG(F("Send Result FirmwareUpdateChunk"));
	return RET_SUCCESS;
}



