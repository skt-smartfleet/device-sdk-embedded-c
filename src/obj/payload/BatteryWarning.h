/*
 * BatteryWarning.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_BATTERYWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_BATTERYWARNING_H_

class BatteryWarning
{
public:
	int wbv;

	BatteryWarning()
	{
		;
	};
	BatteryWarning(int wbv)
	{
		this->wbv = wbv;
	}

	void setDemoData()
	{
		this->wbv = 10;
	}

	char* toString(char* buffer)
	{
		String stringBuffer;

		stringBuffer = "wbv="+wbv+"\n";
		strcpy(buffer, stringBuffer.c_str());

		return buffer;
	}
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_BATTERYWARNING_H_ */
