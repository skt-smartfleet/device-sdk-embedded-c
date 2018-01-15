#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_UNPLUGGEDWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_UNPLUGGEDWARNING_H_

class UnpluggedWarning
{
public:
	int unpt;
    int pt;

    UnpluggedWarning(int unpt, int pt)
    {
        this->unpt = unpt;
        this->pt = pt;
    }

    ~UnpluggedWarning(){};
};



#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_UNPLUGGEDWARNING_H_ */
