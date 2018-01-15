#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_MICROTRIP_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_MICROTRIP_H_

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
	char* xyz;
	double vv;
	int tpos;

	MicroTrip(int tid, int fc, double lat, double lon, int lc, long clt, int cdit, int rpm, int sp, int em, int el, char* xyz, double vv, int tpos)
	{
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

	~MicroTrip(){};
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_MICROTRIP_H_ */
