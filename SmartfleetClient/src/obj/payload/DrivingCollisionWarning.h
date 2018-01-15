#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_DRIVINGCOLLISIONWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_DRIVINGCOLLISIONWARNING_H_

class DrivingCollisionWarning
{
public:
	int tid;
	double dclat;
	double dclon;

    DrivingCollisionWarning(int tid, double dclat, double dclon)
    {
        this->tid = tid;
        this->dclat = dclat;
        this->dclon = dclon;
    }

    ~DrivingCollisionWarning(){};
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_DRIVINGCOLLISIONWARNING_H_ */
