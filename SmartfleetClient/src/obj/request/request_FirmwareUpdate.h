#ifndef SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_FIRMWAREUPDATE_H_
#define SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_FIRMWAREUPDATE_H_

class FirmwareUpdate
{
public:
    char pkv[10];
    char url[128];

    FirmwareUpdate() { };
    FirmwareUpdate(char* pkv, char* url)
    {
    	strcpy(this->pkv, pkv);
    	strcpy(this->url, url);
    }

    FirmwareUpdate& setParams(char* pkv, char* url)
    {
    	strcpy(this->pkv, pkv);
    	strcpy(this->url, url);

    	return *this;
    }

    void clear()
    {
    	memset(this, 0, sizeof(this));
    }


    ~FirmwareUpdate() { };
};

#endif /* SKT_SMARTFLEET_OBJ_REQUEST_REQUEST_FIRMWAREUPDATE_H_ */
