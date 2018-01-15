#ifndef SKT_SMARTFLEET_OBJ_TRIPMESSAGE_H_
#define SKT_SMARTFLEET_OBJ_TRIPMESSAGE_H_

#include "../util/json/ArduinoJson.h"


#include "payload/Trip.h"
#include "payload/MicroTrip.h"
#include "payload/HFDCapabilityInfomation.h"
#include "payload/DiagnosticInfomation.h"
#include "payload/DrivingCollisionWarning.h"
#include "payload/ParkingCollisionWarning.h"
#include "payload/BatteryWarning.h"
#include "payload/UnpluggedWarning.h"
#include "payload/TurnoffWarning.h"

class tripMessage_Base
{
public:
	JsonObject& createTripObject(JsonObject& jsonObj, char* sid, long ts, int ty, void* tripObj);
	JsonObject& createMicroTripObject(JsonObject& jsonObj, char* sid, long ts, int ty, void* tripObj);
	JsonObject& createHFDCapabilityInfomationObject(JsonObject& jsonObj, void* tripObj);
	JsonObject& createDiagnosticInfomationObject(JsonObject& jsonObj, void* tripObj);
	JsonObject& createDrivingCollisionWarningObject(JsonObject& jsonObj, void* tripObj);
	JsonObject& createParkingCollisionWarningObject(JsonObject& jsonObj, void* tripObj);
	JsonObject& createBatteryWarningObject(JsonObject& jsonObj, void* tripObj);
	JsonObject& createUnpluggedWarningObject(JsonObject& jsonObj, void* tripObj);
	JsonObject& createTurnoffWarningObject(JsonObject& jsonObj, void* tripObj);
};

#endif /* SKT_SMARTFLEET_OBJ_TRIPMESSAGE_H_ */
