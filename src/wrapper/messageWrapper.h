/*
 * messageWrapper.h
 *
 *  Created on: 2017. 12. 14.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_WRAPPER_MESSAGEWRAPPER_H_
#define SKT_SMARTFLEET_WRAPPER_MESSAGEWRAPPER_H_

#include "../util/json/ArduinoJson.h"

#include "../wrapper/Smartfleet_Type.h"

#include "../obj/TripMessage.h"
#include "../obj/RPCMessageRequest.h"

class tripMessage : public tripMessage_Base
{
public:
	tripMessage(){};
	~tripMessage(){};
	JsonObject& messagePackage(JsonObject& jsonObj, long ts, TripType ty, void* pldObj);
};


class rpcMessageResponse
{
public:
	rpcMessageResponse(){};
	~rpcMessageResponse(){};
	JsonObject& messagePackage(JsonObject& jsonObj, long ts, int ty, void* pldObj);
};

class arrivedRPCMessage : public RPCMessageRequest_Base
{
public:
	arrivedRPCMessage(){};
	~arrivedRPCMessage(){};
	JsonObject& messageUnpackage(JsonObject& jsonObj, void* messageObj);
	char* getMethod(JsonObject& jsonObj, char* mtd)
	{
		mtd = jsonObj["method"];
		return mtd;
	}
	void* getParams(void* param)
	{

	}

private:
	char* _mtd;

};

//extern tripMessage tripMessage;
//extern rpcMessageResponse rpcMessageResponse;

#endif /* SKT_SMARTFLEET_WRAPPER_MESSAGEWRAPPER_H_ */
