#include "WizFi310MQTT.h"

#include "utility/WizFi310Drv.h"
#include "utility/debug.h"


WizFi310MQTT::WizFi310MQTT()
{

}


int WizFi310MQTT::begin (const char *username, const char *passphrase, const char *clientid, int alivetime) //tested by tom 17.09.18
{
	if ( WizFi310Drv::mqttSet(username, passphrase, clientid, alivetime) )
        return MQ_CONNECTED;

    return MQ_CONNECT_FAILED;
}

int WizFi310MQTT::connect (IPAddress ip)
{
	if ( WizFi310Drv::mqttConnect(ip) )
        return MQ_CONNECTED;

    return MQ_CONNECT_FAILED;
}

int WizFi310MQTT::available()
{
	int bytes = WizFi310Drv::availData();
	if (bytes > 0)
	{
		return bytes;
	}
    return 0;
}

int WizFi310MQTT::subscription(const char *topic)
{
	if ( WizFi310Drv::mqttSub(topic) )
        return MQ_SUB_OK;

    return MQ_SUB_FAILED;
}

int WizFi310MQTT::read()
{
    uint8_t b;
    if (!available())
        return -1;

    bool connClose = false;
    if( WizFi310Drv::getData(_sock, &b, false, &connClose) == false )
        return -1;

    if (connClose)
    {
        WizFi310Drv::_state[_sock] = NA_STATE;
        _sock = 255;
    }

    return b;
}

int WizFi310MQTT::read(uint8_t* buf, size_t size)
{
    return WizFi310Drv::getDataBuf(_sock, buf, size);
}

int WizFi310MQTT::connectTP(int keepalive, const char *thingplugID, const char *credentialID, const char *serviceID, const char *deviceID)
{
	if ( WizFi310Drv::connectThingPlug(keepalive, thingplugID, credentialID, serviceID, deviceID) )
        return MQ_CONNTECTED_THINGPLUG;

    return MQ_CONNTECTED_THINGPLUG_FAILED;
}

int WizFi310MQTT::createDev(const char *deviceID)
{
	if ( WizFi310Drv::createDevice(deviceID) )
        return MQ_CREATE_DEVICE_OK;

    return MQ_CREATE_DEVICE_FAILED;
}
int WizFi310MQTT::deleteDev(const char *deviceID, const char *serviceAE)
{
	if ( WizFi310Drv::deleteDevice(deviceID, serviceAE) )
        return MQ_DELETE_DEVICE_OK;

    return MQ_DELETE_DEVICE_FAILED;
}
int WizFi310MQTT::createCon(const char *contatiner)
{
	if ( WizFi310Drv::createContainer(contatiner) )
        return MQ_CREATE_CONTAINER_OK;

    return MQ_CREATE_CONTAINER_FAILED;
}
int WizFi310MQTT::deleteCon(const char *contatiner)
{
	if ( WizFi310Drv::deleteContainer(contatiner) )
        return MQ_DELETE_CONTATINER_OK;

    return MQ_DELETE_CONTATINER_FAILED;
}
int WizFi310MQTT::sendData(const char *contatiner, const char *data)
{
	if ( WizFi310Drv::send(contatiner, data) )
        return MQ_SEND_TO_THINGPLUG_OK;

    return MQ_SEND_TO_THINGPLUG_FAILED;
}
	
	
int WizFi310MQTT::createCmd(const char *cmd)
{
	if ( WizFi310Drv::createCommand(cmd) )
        return MQ_REGISTER_CMD_OK;

    return MQ_REGISTER_CMD_FAILED;
}
int WizFi310MQTT::deleteCmd(const char *cmd)
{
	if ( WizFi310Drv::deleteCommand(cmd) )
        return MQ_DELETE_CMD_OK;

    return MQ_DELETE_CMD_FAILED;
}
int WizFi310MQTT::cmdResult(const char *cmd, int exs, int exr)
{
	if ( WizFi310Drv::commandResult(cmd, exs, exr) )
        return MQ_CMD_RESILT_OK;

    return MQ_CMD_RESILT_FAILED;
}