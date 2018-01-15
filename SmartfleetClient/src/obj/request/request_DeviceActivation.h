#ifndef SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_DEVICEACTIVATION_H_
#define SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_DEVICEACTIVATION_H_

class DeviceActivation
{
public:
    char vid[10];
    int upp;
    int elt;
    int fut;
    char mty[10];
    int cyl;

    DeviceActivation(){ };
    DeviceActivation(char* vid, int upp, int elt, int fut, char* mty, int cyl)
    {
    	strcpy(this->vid, vid);
        this->upp = upp;
        this->elt = elt;
        this->fut = fut;
        strcpy(this->mty, mty);
        this->cyl = cyl;
    }

    DeviceActivation& setParams(char* vid, int upp, int elt, int fut, char* mty, int cyl)
    {
    	strcpy(this->vid, vid);
        this->upp = upp;
        this->elt = elt;
        this->fut = fut;
        strcpy(this->mty, mty);
        this->cyl = cyl;

        return *this;
    }

    void clear()
    {
    	memset(this, 0, sizeof(this));
    }

    ~DeviceActivation(){ };
};

#endif /* SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_DEVICEACTIVATION_H_ */
