/*
 * Trip.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_TRIP_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_TRIP_H_

#define MAX_TRIP_MEMBER 23

class Trip
{
public:
    int tid;
    long stt;
    long edt;
    int dis;
    int tdis;
    int fc;
    double stlat;
    double stlon;
    double edlat;
    double edlon;
    int ctp;
    double coe;
    int fct;
    int hsts;
    int mesp;
    int idt;
    double btv;
    double gnv;
    int wut;
    int usm;
    int est;
//    char* fwv;
    int fwv;
    int dtvt;

    Trip(int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm =0, int est = 0, int fwv = 0, int dtvt = 0)
//	Trip(int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm =0, int est = 0, char* fwv = 0, int dtvt = 0)
    {
        this->tid = tid;
        this->stt = stt;
        this->edt = edt;
        this->dis = dis;
        this->tdis = tdis;
        this->fc = fc;
        this->stlat = stlat;
        this->stlon = stlon;
        this->edlat = edlat;
        this->edlon = edlon;
        this->ctp = ctp;
        this->coe = coe;
        this->fct = fct;
        this->hsts = hsts;
        this->mesp = mesp;
        this->idt = idt;
        this->btv = btv;
        this->gnv = gnv;
        this->wut = wut;
        this->usm = usm;
        this->est = est;
        this->fwv = fwv;
        this->dtvt = dtvt;

    }

    int getVariableCount()
    {
    	int count_zero_member = 0;

    	if( this->usm == 0) count_zero_member++;
    	if( this->est == 0) count_zero_member++;
    	if( this->fwv == 0) count_zero_member++;
    	if( this->dtvt == 0) count_zero_member++;

    	return MAX_TRIP_MEMBER - count_zero_member;
    };

    ~Trip(){};

};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_TRIP_H_ */
