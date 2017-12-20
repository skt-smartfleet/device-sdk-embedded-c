/*
 * RPCMessageRequest.cpp
 *
 *  Created on: 2017. 12. 18.
 *      Author: Daniel
 */

#include "RPCMessageRequest.h"
#include <Arduino.h>

DeviceActivation& RPCMessageRequest_Base::parseDeviceActivationObject(JsonObject& jsonObj, DeviceActivation* DeviceActivation)
{
	DeviceActivation->setParams(jsonObj["vid"], jsonObj["upp"], jsonObj["elt"], jsonObj["fut"], jsonObj["mty"], jsonObj["cyl"]);
	return *DeviceActivation;
}
