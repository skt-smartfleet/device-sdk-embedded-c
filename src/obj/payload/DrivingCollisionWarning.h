/*
 * DrivingCollisionWarning.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_DRIVINGCOLLISIONWARNING_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_DRIVINGCOLLISIONWARNING_H_

class DrivingCollisionWarning
{
public:
    DrivingCollisionWarning()
	{
//    	this->setDemoData();
    	;
	};

    DrivingCollisionWarning(int tid, double dclat, double dclon)
    {
        this->tid = tid;
        this->dclat = dclat;
        this->dclon = dclon;
    }

    void setDemoData(){
        this->tid = 12345;
        this->dclat = 37.380005;
        this->dclon = 127.118527;
    }

    char* toString(char* buffer)
    {
		String stringBuffer;

		stringBuffer = tid;
		stringBuffer += dclat;
		stringBuffer += dclon;
		stringBuffer += "\n";

		strcpy(buffer, stringBuffer.c_str());

		return buffer;
    }

private:
	int tid;
	double dclat;
	double dclon;
};

#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_DRIVINGCOLLISIONWARNING_H_ */
