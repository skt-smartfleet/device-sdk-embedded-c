#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_TURNOFFWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_TURNOFFWARNING_H_

class TurnoffWarning
{
public:
    char* rs;

    TurnoffWarning(char* rs)
    {
        this->rs = rs;
    }

    ~TurnoffWarning(){};
};




#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_TURNOFFWARNING_H_ */
