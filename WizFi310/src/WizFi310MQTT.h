/*
 * Copyright (C) WIZnet, Inc. All rights reserved.
 * Use is subject to license terms.
 */



#include "Arduino.h"
#include "Print.h"
#include "IPAddress.h"


class WizFi310MQTT
{
public:
    WizFi310MQTT();
	
	static int begin (const char *username, const char *passphrase, const char *clientid, int alivetime);
	static int connect (IPAddress ip);
	int subscription(const char *topic);
	
    virtual int available();
    
    /*
    * Read the next byte received from the server the client is connected to (after the last call to read()).
    * Returns the next byte (or character), or -1 if none is available.
    */
    virtual int read();
    virtual int read(uint8_t *buf, size_t size);
    
    
	static int   connectTP(int keepalive, const char *thingplugID, const char *credentialID, const char *serviceID, const char *deviceID);
	static int   createDev(const char *deviceID);
	static int   deleteDev(const char *deviceID, const char *serviceAE);
	static int   createCon(const char *contatiner);
	static int   deleteCon(const char *contatiner);
	static int   sendData(const char *contatiner, const char *data);
	static int   createCmd(const char *cmd);
	static int   deleteCmd(const char *cmd);
	static int   cmdResult(const char *cmd, int exs, int exr);
    

    
    /*
    * Returns the remote IP address.
    */
    IPAddress remoteIP();
    


private:
	uint8_t _sock;     // connection id
    
    

};



