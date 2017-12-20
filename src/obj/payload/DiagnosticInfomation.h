/*
 * DiagnosticInfomation.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_DIAGNOSTICINFOMATION_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_DIAGNOSTICINFOMATION_H_

class DiagnosticInfomation {

    int tid;
    String dtcc;
    int dtck;
    int dtcs;

    DiagnosticInfomation()
    {
    		;
	};
    DiagnosticInfomation(int tid, String dtcc, int dtck, int dtcs)
    {
        this->tid = tid;
        this->dtcc = dtcc;
        this->dtck = dtck;
        this->dtcs = dtcs;
    };

   void setDemoData(){
        this->tid = 12345;
        this->dtcc = "1,2,3,4,5";
        this->dtck = 0;
        this->dtcs = 3;
    };


   char* toString(char* buffer)
   {
		String stringBuffer;

		stringBuffer = "tid="+tid+"\n";
		stringBuffer += "dtcc="+dtcc+"\n";
		stringBuffer += "dtck="+dtck+"\n";
		stringBuffer += "dtcs="+dtcs+"\n";

		strcpy(buffer, stringBuffer.c_str());

		return buffer;
    };
};




#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_DIAGNOSTICINFOMATION_H_ */
