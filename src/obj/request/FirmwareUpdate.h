/*
 * FirmwareUpdate.h
 *
 *  Created on: 2017. 12. 18.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_REQUEST_FIRMWAREUPDATE_H_
#define SKT_SMARTFLEET_OBJ_REQUEST_FIRMWAREUPDATE_H_

class FirmwareUpdate
{
public:
    char* pkv;
    char* url;

    FirmwareUpdate(char* pkv, char* url)
    {
        this->pkv = pkv;
        this->url = url;
    }
};

#endif /* SKT_SMARTFLEET_OBJ_REQUEST_FIRMWAREUPDATE_H_ */
