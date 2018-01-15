#ifndef SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_FIRMWAREUPDATECHUNK_H_
#define SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_FIRMWAREUPDATECHUNK_H_

class FirmwareUpdateChunk
{
public:
    int tsz;
    int csz;
    int idx;
    char pyd[128];

    FirmwareUpdateChunk() {};
    FirmwareUpdateChunk(int tsz, int csz, int idx, char* pyd)
    {
        this->tsz = tsz;
        this->csz = csz;
        this->idx = idx;
        strcpy(this->pyd, pyd);
    }

    FirmwareUpdateChunk& setParams(int tsz, int csz, int idx, char* pyd)
    {
        this->tsz = tsz;
        this->csz = csz;
        this->idx = idx;
        strcpy(this->pyd, pyd);

        return *this;
    }

    void clear()
    {
    	memset(this, 0, sizeof(this));
    }

    ~FirmwareUpdateChunk() {};
};

#endif /* SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_FIRMWAREUPDATECHUNK_H_ */
