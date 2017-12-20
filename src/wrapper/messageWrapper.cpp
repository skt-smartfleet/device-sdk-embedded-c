/*
 * messageWrapper.cpp
 *
 *  Created on: 2017. 12. 14.
 *      Author: Daniel
 */


#include "messageWrapper.h"


JsonObject& tripMessage::messagePackage(JsonObject& jsonObj, long ts, TripType ty, void* pldObj)
{

	if( ty >= 1)
	{
		switch(ty)
		{
		case TRIP_TRIP:
			createTripObject(jsonObj, ts, ty, pldObj);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			break;
		};


	}



	return jsonObj;

}






JsonObject& arrivedRPCMessage::messageUnpackage(JsonObject& jsonObj, void* messageObj)
{

	_mtd = jsonObj["method"];
	JsonObject& params = jsonObj["params"];

	if(strcmp(_mtd, "activationReq") == 0)
	{

		parseDeviceActivationObject(params, (DeviceActivation*)messageObj);
	}
}


//
//JsonObject& messagePackage(JsonObject& jsonObj, long ts, int ty, void* pldObj)
//{
//
//	StaticJsonBuffer<200> jsonBuffer;
////	DynamicJsonBuffer  jsonBuffer(200);
//
//	JsonObject& root = jsonBuffer.createObject();
//
//	root["sensor"] = "gps";
//	root["time"] = 1351824120;
//
//	JsonArray& data = root.createNestedArray("data");
//	data.add(48.756080);
//	data.add(2.302038);
//
////	root.printTo(Serial);
////
////	Serial.println();
////
////	root.prettyPrintTo(Serial);
//
//	return root;
//}

