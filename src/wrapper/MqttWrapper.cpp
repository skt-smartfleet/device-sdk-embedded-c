/*
 * MqttWrapper.cpp
 *
 *  Created on: 2017. 12. 10.
 *      Author: Daniel
 */

#include "MqttWrapper.h"


mqttWrapper::mqttWrapper(Client& client)
{
	_client = &client;
}

void mqttWrapper::begin()
{
	this->initialize();
}

void mqttWrapper::begin(Client& client)
{
	_client = &client;
	this->initialize();
}

void mqttWrapper::setHost(const char* host)
{
//	strcpy( _host, host );
	_host = host;

}
void mqttWrapper::setPort(const int port)
{
	_port = port;
}

void mqttWrapper::setUser(const char* username, const char* password)
{
//	strcpy(_username, username);
//	strcpy(_password, password);

	_username = username;
	_password = password;
}

void mqttWrapper::setToken(const char* token)
{
//	strcpy( _token, token );
	_token = token;

}
void mqttWrapper::setTopic(const char* topic)
{
//	strcpy( _topic, topic );
	_topic = topic;
}

void mqttWrapper::setMessageHandler(rcv_message_cb_t cb)
{
	rcv_message_cb = cb;
}

mqttWrapper mqttWrapper::callbackMessage(MQTT::MessageData& messageData)
{
	MQTT::Message &message = messageData.message;


	int len = messageData.topicName.lenstring.len;
	char topic[len+1];

	memcpy(topic, messageData.topicName.lenstring.data, (size_t)len);
	topic[len] = '\0';

	char * payload = (char *)message.payload;
	payload[message.payloadlen] = '\0';

	rcv_message_cb(topic, payload);
}



void mqttWrapper::initialize()
{

    this->_mqtt = new MQTT::Client<mqttWrapper, Network, Timer, DEFAULT_BUFFER_SIZE, 0>(_network);
    this->_network.setClient(_client);
    this->_mqtt_opt = MQTTPacket_connectData_initializer;
    this->_mqtt->defaultMessageHandler.attach<mqttWrapper>(this, &mqttWrapper::callbackMessage);

}

void mqttWrapper::finalize()
{

}

bool mqttWrapper::isConnected()
{
	if( _mqtt->isConnected() == true )
	{
		return true;
	}

	return false;
}

void mqttWrapper::connect()
{
	this->connect(_host, _port, _username, _password);
}

void mqttWrapper::connect(const char* host, const int port, const char* username, const char* password)
{
	int ret = 0;
	char client[] = "5d354a80961d4256a29ed5f52c1b98d4";
	this->setHost(host);
	this->setPort(port);
	this->setUser(username, password);

	if(_network.connect((char*)_host, (int)_port) == 0)
	{
		DBG_P("TCP connection Fail");
	}

	_mqtt_opt.clientID.cstring = client;
	_mqtt_opt.username.cstring = (char*)username;
	_mqtt_opt.password.cstring = (char*)password;
	_mqtt_opt.keepAliveInterval = 120;
	_mqtt_opt.MQTTVersion = 4;

//	 optional will flag
//	_mqtt_opt.willFlag = 0x01;
//	_mqtt_opt.will.topicName.cstring = (char*)_topic;
//	_mqtt_opt.will.message.cstring = (char*)"offline";
//	_mqtt_opt.will.retained = 0x01;

	if(_mqtt->connect(_mqtt_opt) == 0)
	{
		DBG_P("Connect successfully");
	}
}

void mqttWrapper::disconnect()
{

}

void mqttWrapper::subscribeTopic(const char* topic, int qos)
{

	if( _mqtt->isConnected() == false )
	{
		return;
	}

	_mqtt->subscribe(topic, qos, NULL);
}

void mqttWrapper::unsubscribeTopic(const char* topic)
{
	if( _mqtt->isConnected() == false )
	{
		return;
	}

	_mqtt->unsubscribe(topic);
}

void mqttWrapper::subscribewithcallback(const char* topic, int qos, void* cb)
{

	if( _mqtt->isConnected() == false )
	{
		return;
	}

	_mqtt->subscribe(topic, qos, cb);

}


void mqttWrapper::publish(JsonObject& pubMessage, const char* topic, int qos)
{
	int ret;
	char buffer[512] = {0,};
	pubMessage.printTo(buffer, sizeof(buffer));

    MQTT::Message message;
    message.qos = qos;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buffer;
    message.payloadlen = strlen(buffer)+1;

	DBG((char*)message.payload);

    ret = _mqtt->publish(topic, message);
    if( ret != MQTT::SUCCESS )
    	DBG_P("Fail to publish");
}


void mqttWrapper::publish(const char* pubMessage, const char* topic, int qos)
{
	int ret;
    MQTT::Message message;
    message.qos = qos;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)pubMessage;
    message.payloadlen = strlen(pubMessage)+1;

	DBG((char*)message.payload);

    ret = _mqtt->publish(topic, message);
    if( ret != MQTT::SUCCESS )
    	DBG_P("fail to publish");
}

void mqttWrapper::mqtt_yield()
{

	if( _mqtt->isConnected() == false )
	{
		DBG_P("Connecting to Broker..");

		this->connect();
		this->subscribeTopic(_topic, 0);
	}

    if(!_network.connected() && _mqtt->isConnected()) {
    	_mqtt->disconnect();
    }

	_mqtt->yield(3000);
}


