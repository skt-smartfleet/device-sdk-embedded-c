/*
 * FirmwareUpdateChunk.h
 *
 *  Created on: 2017. 12. 18.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_OBJ_REQUEST_FIRMWAREUPDATECHUNK_H_
#define SKT_SMARTFLEET_OBJ_REQUEST_FIRMWAREUPDATECHUNK_H_

class FirmwareUpdateChunk {

    int tsz;
    int csz;
    int idx;
    char* pyd;

    FirmwareUpdateChunk(int tsz, int csz, int idx, char* pyd) {
        this->tsz = tsz;
        this->csz = csz;
        this->idx = idx;
        this->pyd = pyd;
    }
};

#endif /* SKT_SMARTFLEET_OBJ_REQUEST_FIRMWAREUPDATECHUNK_H_ */
