/*
 * MicroTrip.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_MICROTRIP_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_MICROTRIP_H_

#define MAX_MICROTRIP_MEMBER 14

class MicroTrip
{
public:
	int tid;
	int fc;
	double lat;
	double lon;
	int lc;
	long clt;
	int cdit;
	int rpm;
	int sp;
	int em;
	int el;
	String xyz;
	double vv;
	int tpos;

	MicroTrip(int tid, int fc, double lat, double lon, int lc, long clt, int cdit, int rpm, int sp, int em, int el, String xyz, double vv, int tpos) {
	        this->tid = tid;
	        this->fc = fc;
	        this->lat = lat;
	        this->lon = lon;
	        this->lc = lc;
	        this->clt = clt;
	        this->cdit = cdit;
	        this->rpm = rpm;
	        this->sp = sp;
	        this->em = em;
	        this->el = el;
	        this->xyz = xyz;
	        this->vv = vv;
	        this->tpos = tpos;
	}

    int getVariableCount()
    {
    	int count_zero_member = 0;

//    	if( this->usm == 0) count_zero_member++;
//    	if( this->est == 0) count_zero_member++;
//    	if( this->fwv == 0) count_zero_member++;
//    	if( this->dtvt == 0) count_zero_member++;

    	return MAX_MICROTRIP_MEMBER - count_zero_member;
    };

	~MicroTrip();
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_MICROTRIP_H_ */
