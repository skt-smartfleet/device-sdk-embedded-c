#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_PARKINGCOLLISIONWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_PARKINGCOLLISIONWARNING_H_

class ParkingCollisionWarning
{
public:
    double pclat;
    double pclon;

    ParkingCollisionWarning(double pclat, double pclon)
    {
        this->pclat = pclat;
        this->pclon = pclon;
    }

    ~ParkingCollisionWarning(){};
};




#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_PARKINGCOLLISIONWARNING_H_ */
