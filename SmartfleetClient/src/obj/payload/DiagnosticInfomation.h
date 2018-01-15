#ifndef SKT_SMARTFLEET_OBJ_PAYLOAD_DIAGNOSTICINFOMATION_H_
#define SKT_SMARTFLEET_OBJ_PAYLOAD_DIAGNOSTICINFOMATION_H_

class DiagnosticInfomation
{
public:
    int tid;
    char* dtcc;
    int dtck;
    int dtcs;

    DiagnosticInfomation(int tid, char* dtcc, int dtck, int dtcs)
    {
        this->tid = tid;
        this->dtcc = dtcc;
        this->dtck = dtck;
        this->dtcs = dtcs;
    }

    ~DiagnosticInfomation(){};
};




#endif /* SKT_SMARTFLEET_OBJ_PAYLOAD_DIAGNOSTICINFOMATION_H_ */
