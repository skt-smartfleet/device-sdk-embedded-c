/*
 * RPCMessageRequest.h
 *
 *  Created on: 2017. 12. 18.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_RPCMESSAGEREQUEST_H_
#define SKT_SMARTFLEET_OBJ_RPCMESSAGEREQUEST_H_


#include "../util/json/ArduinoJson.h"

#include "request/DeviceActivation.h"
#include "request/FirmwareUpdate.h"
#include "request/FirmwareUpdateChunk.h"

class RPCMessageRequest_Base
{
public:

	DeviceActivation& parseDeviceActivationObject(JsonObject& jsonObj, DeviceActivation* DeviceActivation);
//	JsonObject& parseDeviceActivationObject(JsonObject& jsonObj, char* mtd, void* parObj);
	JsonObject& parseFirmwareUpdateObject(JsonObject& jsonObj, char* mtd, void* parObj);
	JsonObject& parseFirmwareUpdateChunkObject(JsonObject& jsonObj, char* mtd, void* parObj);


//	JsonObject& createTripObject(JsonObject& jsonObj, long ts, int ty, void* pldObj);
//	JsonObject& createMicroTripObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createHFDCapabilityInfomationObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createDiagnosticInfomationObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createDrivingCollisionWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createParkingCollisionWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createBatteryWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createUnpluggedWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createTurnoffWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
};

#endif /* SKT_SMARTFLEET_OBJ_RPCMESSAGEREQUEST_H_ */
