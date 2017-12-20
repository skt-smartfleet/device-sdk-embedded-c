/*
 * TripMessage.cpp
 *
 *  Created on: 2017. 12. 15.
 *      Author: Daniel
 */

#include "TripMessage.h"


JsonObject& tripMessage_Base::createTripObject(JsonObject& jsonObj, long ts, int ty, void* pldObj)
{

	Trip* trip = (Trip*)pldObj;
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
//
//JsonObject& tripMessage_Base::createTripObject(JsonObject& jsonObj, long ts, int ty, void* pldObj)
//{
//
//	Trip trip = (Trip&)pldObj;
//	jsonObj["ts"] = ts;
//	jsonObj["ty"] = ty;
//
//	JsonObject& pld = jsonObj.createNestedObject("pld");
//
//	//mandatory parameter
//	pld["tid"] = trip.tid;
//	pld["stt"] = trip.stt;
//	pld["edt"] = trip.edt;
//	pld["dis"] = trip.dis;
//	pld["tdis"] = trip.tdis;
//	pld["fc"] = trip.fc;
//	pld["stlat"] = trip.stlat;
//	pld["stlon"] = trip.stlon;
//	pld["edlat"] = trip.edlat;
//	pld["edlon"] = trip.edlon;
//	pld["ctp"] = trip.ctp;
//	pld["coe"] = trip.coe;
//	pld["hsts"] = trip.hsts;
//	pld["mesp"] = trip.mesp;
//	pld["idt"] = trip.idt;
//	pld["btv"] = trip.btv;
//	pld["gnv"] = trip.gnv;
//	pld["wut"] = trip.wut;
//
//	//optional parameter
//	if( trip.usm != 0) pld["usm"] = trip.usm;
//	if( trip.est != 0) pld["est"] = trip.est;
//	if( trip.fwv != 0) pld["fwv"] = trip.fwv;
//	if( trip.dtvt != 0) pld["dtvt"] = trip.dtvt;
//
//	return jsonObj;
//}

