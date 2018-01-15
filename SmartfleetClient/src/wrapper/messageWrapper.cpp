#include "messageWrapper.h"

JsonObject& tripMessage::messagePackage(JsonObject& jsonObj, long ts, TripType ty, void* tripObj)
{
	char* sid = TRIP_SID_STR;

	if( ty >= 1)
	{
		switch(ty)
		{
		case TRIP:
			createTripObject(jsonObj, sid, ts, ty, tripObj);
			break;
		case MICRO_TRIP:
			createMicroTripObject(jsonObj, sid, ts, ty, tripObj);
			break;
		case HFD_CAPABILITY_INFORMATION:
			createHFDCapabilityInfomationObject(jsonObj, tripObj);
			break;
		case DIAGNOSTIC_INFORMATION:
			createDiagnosticInfomationObject(jsonObj, tripObj);
			break;
		case DRIVING_COLLISION_WARNING:
			createDrivingCollisionWarningObject(jsonObj, tripObj);
			break;
		case PARKING_COLLISION_WARNING:
			createParkingCollisionWarningObject(jsonObj, tripObj);
			break;
		case BATTERY_WARNING:
			createBatteryWarningObject(jsonObj, tripObj);
			break;
		case UNPLUGGED_WARNING:
			createUnpluggedWarningObject(jsonObj, tripObj);
			break;
		case TURNOFF_WARNING:
			createTurnoffWarningObject(jsonObj, tripObj);
			break;
		default:
			break;

		};
	}

	return jsonObj;

}

JsonObject& rpcMessage::messagePackage(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	if( ty >= 1)
	{
		switch(ty)
		{
		case DEVICE_ACTIVATION:
			createDeviceActivationObject(jsonObj, code, ty, addInfoObj);
			break;
		case FIRMWARE_UPDATE:
			createFirmwareUpdateObject(jsonObj, code, ty, addInfoObj);
			break;
		case ODB_RESET:
			createOBDResetObject(jsonObj, code, ty, addInfoObj);
			break;
		case DEVICE_SERIAL_NUMBER_CHECK:
			createDeviceSerialNumberCheckObject(jsonObj, code, ty, addInfoObj);
			break;
		case CLEAR_DEVICE_DATA:
			createClearDeviceDataObject(jsonObj, code, ty, addInfoObj);
			break;
		case FIRMWARE_UPDATE_CHUNK:
			createFirmwareUpdateChunkObject(jsonObj, code, ty, addInfoObj);
			break;
		default:
			break;
		};
	}
	else if(ty == 0)
	{
		createResponseObject(jsonObj, code);
	}

	return jsonObj;
}

JsonObject& arrivedRPCMessage::messageUnpackage(JsonObject& jsonObj, RPCType ty, void* messageObj)
{
	if( ty >= 1)
	{
		switch(ty)
		{
		case DEVICE_ACTIVATION:
			parseDeviceActivationObject(jsonObj, messageObj == NULL ? (DeviceActivation*)&g_da : (DeviceActivation*)messageObj);
			break;
		case FIRMWARE_UPDATE:
			parseFirmwareUpdateObject(jsonObj, messageObj == NULL ? (FirmwareUpdate*)&g_fu : (FirmwareUpdate*)messageObj);
			break;
		case ODB_RESET:
			parseDefaultObject(jsonObj, messageObj == NULL ? (char*)&g_buffer : (char*)messageObj);
			break;
		case DEVICE_SERIAL_NUMBER_CHECK:
			parseDefaultObject(jsonObj, messageObj == NULL ? (char*)&g_buffer : (char*)messageObj);
			break;
		case CLEAR_DEVICE_DATA:
			parseDefaultObject(jsonObj, messageObj == NULL ? (char*)&g_buffer : (char*)messageObj);
			break;
		case FIRMWARE_UPDATE_CHUNK:
			parseFirmwareUpdateChunkObject(jsonObj, messageObj == NULL ? (FirmwareUpdateChunk*)&g_fuc : (FirmwareUpdateChunk*)messageObj);
			break;
		case VENDOR_SPECIFIC:
			parseDefaultObject(jsonObj, messageObj == NULL ? (char*)&g_buffer : (char*)messageObj);
			break;
		default:
			break;
		};
	}

	return jsonObj;
}

char* arrivedRPCMessage::getMethod(JsonObject& jsonObj, char* mtd)
{
	char* method = jsonObj[JSON_RPC_METHOD];

	if(method != NULL)
	{
		strcpy(mtd, method);
		return mtd;
	}
	return (char*)0;
}

char* arrivedRPCMessage::getReqId(const char* topic, char* req_id)
{
	if (strncmp(topic, RPC_REQUEST_TOPIC, strlen(RPC_REQUEST_TOPIC)) == 0 )
	{
		strcpy(req_id, topic + strlen((char*)RPC_REQUEST_TOPIC));
		return req_id;
	}
	return (char*)0;
}
