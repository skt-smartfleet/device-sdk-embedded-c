#include <Arduino.h>
#include "RPCMessage.h"


JsonObject& RPCMessage_Base::createResponseObject(JsonObject& jsonObj, int code)
{
	jsonObj[JSON_RESPONSE_CODE] = code;
	return jsonObj;
}

JsonObject& RPCMessage_Base::createDeviceActivationObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	RPCDeviceActivation* da = (RPCDeviceActivation*) addInfoObj;

	jsonObj[JSON_RESULT_CODE] = code;

	if( addInfoObj != NULL )
	{
		JsonObject& addInfo = jsonObj.createNestedObject(JSON_RESULT_BODY);
		addInfo["vid"] = da->vid;
	}

	return jsonObj;
}

JsonObject& RPCMessage_Base::createFirmwareUpdateObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	jsonObj[JSON_RESULT_CODE] = code;
	return jsonObj;
}

JsonObject& RPCMessage_Base::createOBDResetObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	jsonObj[JSON_RESULT_CODE] = code;
	return jsonObj;
}

JsonObject& RPCMessage_Base::createDeviceSerialNumberCheckObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	RPCDeviceSerialNumberCheck* dsnc = (RPCDeviceSerialNumberCheck*) addInfoObj;

	jsonObj[JSON_RESULT_CODE] = code;

	if( addInfoObj != NULL )
	{
		JsonObject& addInfo = jsonObj.createNestedObject(JSON_RESULT_BODY);
		addInfo["sn"] = dsnc->sn;
	}

	return jsonObj;
}

JsonObject& RPCMessage_Base::createClearDeviceDataObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	jsonObj[JSON_RESULT_CODE] = code;
	return jsonObj;
}

JsonObject& RPCMessage_Base::createFirmwareUpdateChunkObject(JsonObject& jsonObj, int code, int ty, void* addInfoObj)
{
	jsonObj[JSON_RESULT_CODE] = code;
	return jsonObj;
}


char* RPCMessage_Base::parseDefaultObject(JsonObject& jsonObj, char* _params)
{
	JsonObject& params = jsonObj[JSON_RPC_PARAMS];

	params.printTo(_params, DEFAULT_RPC_BUFFER_SIZE);

	return _params;
}

DeviceActivation& RPCMessage_Base::parseDeviceActivationObject(JsonObject& jsonObj, DeviceActivation* DeviceActivation)
{
	JsonObject& params = jsonObj[JSON_RPC_PARAMS];

	DeviceActivation->setParams(params["vid"], params["upp"], params["elt"], params["fut"], params["mty"], params["cyl"]);
	return *DeviceActivation;
}

FirmwareUpdate& RPCMessage_Base::parseFirmwareUpdateObject(JsonObject& jsonObj, FirmwareUpdate* FirmwareUpdate)
{
	JsonObject& params = jsonObj[JSON_RPC_PARAMS];

	FirmwareUpdate->setParams(params["pkv"], params["url"]);
	return *FirmwareUpdate;
}

FirmwareUpdateChunk& RPCMessage_Base::parseFirmwareUpdateChunkObject(JsonObject& jsonObj, FirmwareUpdateChunk* FirmwareUpdateChunk)
{
	JsonObject& params = jsonObj[JSON_RPC_PARAMS];

	FirmwareUpdateChunk->setParams(params["tsz"], params["csz"], params["idx"], params["pyd"]);
	return *FirmwareUpdateChunk;
}

