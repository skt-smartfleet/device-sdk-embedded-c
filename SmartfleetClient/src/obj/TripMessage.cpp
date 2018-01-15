#include "TripMessage.h"

JsonObject& tripMessage_Base::createTripObject(JsonObject& jsonObj, char* sid, long ts, int ty, void* tripObj)
{

	Trip* trip = (Trip*)tripObj;

	jsonObj["sid"] = sid;
	jsonObj["ts"] = ts;
	jsonObj["ty"] = ty;

	JsonObject& pld = jsonObj.createNestedObject("pld");

	//mandatory parameter
	pld["tid"] = trip->tid;
	pld["stt"] = trip->stt;
	pld["edt"] = trip->edt;
	pld["dis"] = trip->dis;
	pld["tdis"] = trip->tdis;
	pld["fc"] = trip->fc;
	pld["stlat"] = trip->stlat;
	pld["stlon"] = trip->stlon;
	pld["edlat"] = trip->edlat;
	pld["edlon"] = trip->edlon;
	pld["ctp"] = trip->ctp;
	pld["coe"] = trip->coe;
	pld["fct"] = trip->fct;
	pld["hsts"] = trip->hsts;
	pld["mesp"] = trip->mesp;
	pld["idt"] = trip->idt;
	pld["btv"] = trip->btv;
	pld["gnv"] = trip->gnv;
	pld["wut"] = trip->wut;

	//optional parameter
	if( trip->usm != 0) pld["usm"] = trip->usm;
	if( trip->est != 0) pld["est"] = trip->est;
	if( trip->fwv != 0) pld["fwv"] = trip->fwv;
	if( trip->dtvt != 0) pld["dtvt"] = trip->dtvt;

	return jsonObj;
}

JsonObject& tripMessage_Base::createMicroTripObject(JsonObject& jsonObj, char* sid, long ts, int ty, void* tripObj)
{
	MicroTrip* trip = (MicroTrip*)tripObj;

	jsonObj["sid"] = sid;
	jsonObj["ts"] = ts;
	jsonObj["ty"] = ty;
	jsonObj["ap"] = 0;

	JsonObject& pld = jsonObj.createNestedObject("pld");

	//mandatory parameter
	pld["tid"] = trip->tid;
	pld["fc"] = trip->fc;
	pld["lat"] = trip->lat;
	pld["lon"] = trip->lon;
	pld["lc"] = trip->lc;
	pld["clt"] = trip->clt;
	pld["cdit"] = trip->cdit;
	pld["rpm"] = trip->rpm;
	pld["sp"] = trip->sp;
	pld["em"] = trip->em;
	pld["el"] = trip->el;
	pld["vv"] = trip->vv;


	//optional parameter
//	if( trip->usm != 0) pld["usm"] = trip->usm;
//	if( trip->est != 0) pld["est"] = trip->est;
//	if( trip->fwv != 0) pld["fwv"] = trip->fwv;
//	if( trip->dtvt != 0) pld["dtvt"] = trip->dtvt;

	return jsonObj;
}

JsonObject& tripMessage_Base::createHFDCapabilityInfomationObject(JsonObject& jsonObj, void* tripObj)
{
	HFDCapabilityInfomation* trip = (HFDCapabilityInfomation*)tripObj;

	jsonObj["cm"] = trip->cm;

	return jsonObj;
}

JsonObject& tripMessage_Base::createDiagnosticInfomationObject(JsonObject& jsonObj, void* tripObj)
{
	DiagnosticInfomation* trip = (DiagnosticInfomation*)tripObj;

	jsonObj["tid"] = trip->tid;
	jsonObj["dtcc"] = trip->dtcc;
	jsonObj["dtck"] = trip->dtck;
	jsonObj["dtcs"] = trip->dtcs;

	return jsonObj;
}

JsonObject& tripMessage_Base::createDrivingCollisionWarningObject(JsonObject& jsonObj, void* tripObj)
{
	DrivingCollisionWarning* trip = (DrivingCollisionWarning*)tripObj;

	jsonObj["tid"] = trip->tid;
	jsonObj["dclat"] = trip->dclat;
	jsonObj["dclon"] = trip->dclon;

	return jsonObj;
}

JsonObject& tripMessage_Base::createParkingCollisionWarningObject(JsonObject& jsonObj, void* tripObj)
{
	ParkingCollisionWarning* trip = (ParkingCollisionWarning*)tripObj;

	jsonObj["pclat"] = trip->pclat;
	jsonObj["pclon"] = trip->pclon;

	return jsonObj;
}

JsonObject& tripMessage_Base::createBatteryWarningObject(JsonObject& jsonObj, void* tripObj)
{
	BatteryWarning* trip = (BatteryWarning*)tripObj;

	jsonObj["wbv"] = trip->wbv;

	return jsonObj;
}

JsonObject& tripMessage_Base::createUnpluggedWarningObject(JsonObject& jsonObj, void* tripObj)
{
	UnpluggedWarning* trip = (UnpluggedWarning*)tripObj;

	jsonObj["unpt"] = trip->unpt;
	jsonObj["pt"] = trip->pt;

	return jsonObj;
}

JsonObject& tripMessage_Base::createTurnoffWarningObject(JsonObject& jsonObj, void* tripObj)
{
	TurnoffWarning* trip = (TurnoffWarning*)tripObj;

	jsonObj["rs"] = trip->rs;

	return jsonObj;
}

