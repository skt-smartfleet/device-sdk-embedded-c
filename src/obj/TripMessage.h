/*
 * TripMessage.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_TRIPMESSAGE_H_
#define SKT_SMARTFLEET_OBJ_TRIPMESSAGE_H_

#include "../util/json/ArduinoJson.h"


#include "payload/Trip.h"

#include "payload/DrivingCollisionWarning.h"


// object include





class tripMessage_Base
{
public:
	JsonObject& createTripObject(JsonObject& jsonObj, long ts, int ty, void* pldObj);
//	JsonObject& createMicroTripObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createHFDCapabilityInfomationObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createDiagnosticInfomationObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createDrivingCollisionWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createParkingCollisionWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createBatteryWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createUnpluggedWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
//	JsonObject& createTurnoffWarningObject(JsonObject& buffer, time_t ts, int ty, void* obj);
};



#endif /* SKT_SMARTFLEET_OBJ_TRIPMESSAGE_H_ */
