#ifndef SKT_SMARTFLEET_OBJ_RESULT_RESULT_DEVICEACTIVATION_H_
#define SKT_SMARTFLEET_OBJ_RESULT_RESULT_DEVICEACTIVATION_H_


class RPCDeviceActivation {
public:

    char* vid;

    RPCDeviceActivation(){ };
    RPCDeviceActivation(char* vid)
    {
        this->vid = vid;
    }

    RPCDeviceActivation& setParams(char* vid)
    {
    	this->vid = vid;
        return *this;
    }
};

#endif /* SKT_SMARTFLEET_OBJ_RESULT_RESULT_DEVICEACTIVATION_H_ */
