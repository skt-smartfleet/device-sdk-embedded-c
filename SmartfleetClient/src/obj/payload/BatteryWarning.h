#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_BATTERYWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_BATTERYWARNING_H_

class BatteryWarning
{
public:
	int wbv;

	BatteryWarning(int wbv)
	{
		this->wbv = wbv;
	}

    ~BatteryWarning(){};
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_BATTERYWARNING_H_ */
