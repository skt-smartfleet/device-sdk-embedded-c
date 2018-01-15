#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_TRIP_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_TRIP_H_

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
    char* fwv;
    int dtvt;

	Trip(int tid, long stt, long edt, int dis, int tdis, int fc, double stlat, double stlon, double edlat, double edlon, int ctp, double coe, int fct, int hsts, int mesp, int idt, double btv, double gnv, int wut, int usm, int est, char* fwv, int dtvt)
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

    ~Trip(){};
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_TRIP_H_ */
