#ifndef SKT_SMARTFLEET_OBJ_RPCMESSAGE_H_
#define SKT_SMARTFLEET_OBJ_RPCMESSAGE_H_

#include "../util/json/ArduinoJson.h"
#include "../wrapper/Smartfleet_Type.h"

#include "result/result_DeviceActivation.h"
#include "result/result_DeviceSerialNumberCheck.h"

#include "request/request_FirmwareUpdate.h"
#include "request/request_FirmwareUpdateChunk.h"
#include "request/request_DeviceActivation.h"

class RPCMessage_Base
{
public:
	//create response object
	JsonObject& createResponseObject(JsonObject& jsonObj, int code);

	//create result object
	JsonObject& createDeviceActivationObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);
	JsonObject& createFirmwareUpdateObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);
	JsonObject& createOBDResetObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);
	JsonObject& createDeviceSerialNumberCheckObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);
	JsonObject& createClearDeviceDataObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);
	JsonObject& createFirmwareUpdateChunkObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);


	//parse rpc message
	char* parseDefaultObject(JsonObject& jsonObj, char* _params);
	DeviceActivation& parseDeviceActivationObject(JsonObject& jsonObj, DeviceActivation* DeviceActivation);
	FirmwareUpdate& parseFirmwareUpdateObject(JsonObject& jsonObj, FirmwareUpdate* FirmwareUpdate);
	FirmwareUpdateChunk& parseFirmwareUpdateChunkObject(JsonObject& jsonObj, FirmwareUpdateChunk* FirmwareUpdateChunk);
};


#endif /* SKT_SMARTFLEET_OBJ_RPCMESSAGE_H_ */
