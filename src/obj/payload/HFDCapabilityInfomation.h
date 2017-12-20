/*
 * HFDCapabilityInfomation.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_HFDCAPABILITYINFOMATION_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_HFDCAPABILITYINFOMATION_H_

#define MAX_HFD _MEMBER 14


class HFDCapabilityInfomation
{

	int cm;

	HFDCapabilityInfomation(int cm)
	{
		this->cm = cm;
	}


};



#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_HFDCAPABILITYINFOMATION_H_ */
