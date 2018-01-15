#ifndef SKT_SMARTFLEET_OBJ_RESULT_RESULT_DEVICESERIALNUMBERCHECK_H_
#define SKT_SMARTFLEET_OBJ_RESULT_RESULT_DEVICESERIALNUMBERCHECK_H_

class RPCDeviceSerialNumberCheck {
public:

    char* sn;

    RPCDeviceSerialNumberCheck(){ };
    RPCDeviceSerialNumberCheck(char* sn)
    {
        this->sn = sn;
    }

    RPCDeviceSerialNumberCheck& setParams(char* sn)
    {
    	this->sn = sn;
        return *this;
    }
};



#endif /* SKT_SMARTFLEET_OBJ_RESULT_RESULT_DEVICESERIALNUMBERCHECK_H_ */
