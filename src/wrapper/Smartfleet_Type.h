/*
 * Smartfleet_Type.h
 *
 *  Created on: 2017. 12. 10.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_WRAPPER_SMARTFLEET_TYPE_H_
#define SKT_SMARTFLEET_WRAPPER_SMARTFLEET_TYPE_H_

#include "../util/LogPrint.h"

#define DEFAULT_BUFFER_SIZE 512

typedef enum TripType
{
    TRIP_ALL,
	TRIP_TRIP,
	TRIP_MICRO_TRIP,
	TRIP_HFD_CAPABILITY_INFORMATION,
	TRIP_HFD_DATA,
	TRIP_DIAGNOSTIC_INFORMATION,
	TRIP_DRIVING_COLLISION_WARNING,
	TRIP_PARKING_COLLISION_WARNING,
	TRIP_BATTERY_WARNING,
	TRIP_UNPLUGGED_WARNING,
	TRIP_TURNOFF_WARNING

};


typedef enum RPCType
{
    RPC_ACTIVIATION_REQ,
	RPC_RESET,
	RPC_SERIAL,
	RPC_GET_RADIO_USAGE,
	RPC_GET_DEV_INFO,
	RPC_CLEAR_DATA,
	RPC_STOP_PUSH,
	RPC_SEND_CAR_DB,
	RPC_FW_UP_CHUCK,
	RPC_GET_MICRO_TRIP,
	RPC_GET_TRIP
};

//class Trip
//{
//    int tid;
//    long stt;
//    long edt;
//    int dis;
//    int tdis;
//    int fc;
//    double stlat;
//    double stlon;
//    double edlat;
//    double edlon;
//    int ctp;
//    double coe;
//    int fct;
//    int hsts;
//    int mesp;
//    int idt;
//    double btv;
//    double gnv;
//    int wut;
//    int usm;
//    int est;
//    String fwv;
//    int dtvt;
//
//    Trip(int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, String fwv, int dtvt)
//    {
//        this->tid = tid;
//        this->stt = stt;
//        this.edt = edt;
//        this.dis = dis;
//        this.tdis = tdis;
//        this.fc = fc;
//        this.stlat = stlat;
//        this.stlon = stlon;
//        this.edlat = edlat;
//        this.edlon = edlon;
//        this.ctp = ctp;
//        this.coe = coe;
//        this.fct = fct;
//        this.hsts = hsts;
//        this.mesp = mesp;
//        this.idt = idt;
//        this.btv = btv;
//        this.gnv = gnv;
//        this.wut = wut;
//        this.usm = usm;
//        this.est = est;
//        this.fwv = fwv;
//        this.dtvt = dtvt;
//
//    }
//    ~Trip();
//};

//class MicroTrip
//{
//	int tid;
//	int fc;
//	double lat;
//	double lon;
//	int lc;
//	long clt;
//	int cdit;
//	int rpm;
//	int sp;
//	int em;
//	int el;
//	String xyz;
//	double vv;
//	int tpos;
//};
//
//class HFDCapabilityInfomation
//{
//	int cm;
//};
//
//class DiagnosticInfomation
//{
//    int tid;
//    String dtcc;
//    int dtck;
//    int dtcs;
//};
//
//class DrivingCollisionWarning
//{
//    int tid;
//    double dclat;
//    double dclon;
//};
//
//class ParkingCollisionWarning
//{
//    double pclat;
//    double pclon;
//};
//
//
//
//class BatteryWarning
//{
//	int wbv;
//};
//
//class UnpluggedWarning
//{
//	int unpt;
//	int pt;
//};
//
//class TurnoffWarning
//{
//	String rs;
//};
//
////not define in java sdk
//class Attribute
//{
//	int a;
//};
//
//class Telemetry
//{
//	int a;
//};
//
//class ProcessRpc
//{
//	int a;
//};
//
//class RpcResult
//{
//	int a;
//};

#endif /* SKT_SMARTFLEET_WRAPPER_SMARTFLEET_TYPE_H_ */
