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
	_host = host;
	_used_ip = MQTT_USED_DOMAIN;
}

void mqttWrapper::setIP(IPAddress ip)
{
	_ip = ip;
	_used_ip = MQTT_USED_IP;
}

void mqttWrapper::setPort(const int port)
{
	_port = port;
}

void mqttWrapper::setUser(const char* username, const char* password)
{
	_username = username;
	_password = password;
}

void mqttWrapper::setClientId(const char* clientid)
{
	strcpy(_clientid, clientid);
}

void mqttWrapper::setSubscribeTopic(const char* topic)
{
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

	PRINT_DBG(payload);
}

void mqttWrapper::initialize()
{
    this->_mqtt = new MQTT::Client<mqttWrapper, Network, Timer, DEFAULT_MQTT_BUFFER_SIZE, 0>(_network);
    this->_network.setClient(_client);
    this->_mqtt_opt = MQTTPacket_connectData_initializer;
    this->_mqtt->defaultMessageHandler.attach<mqttWrapper>(this, &mqttWrapper::callbackMessage);
}


bool mqttWrapper::isConnected()
{
	if( _mqtt->isConnected() == true )
	{
		return true;
	}

	return false;
}

int mqttWrapper::connect()
{
	int ret = MQTT::FAILURE;

	if(_network.connected() == false)
	{
		if(_used_ip == MQTT_USED_IP)
		{
			ret = _network.connect(_ip, (int)_port);
		}
		else if(_used_ip == MQTT_USED_DOMAIN)
		{
			ret = _network.connect((char*)_host, (int)_port);
		}

		if(ret == 0)
		{
			PRINT_LOG(F("TCP connection Fail"));
			_network.disconnect();

			return MQTT::FAILURE;
		}
	}

	_mqtt_opt.clientID.cstring = _clientid;
	_mqtt_opt.username.cstring = (char*)_username;
	_mqtt_opt.password.cstring = (char*)_password;
	_mqtt_opt.keepAliveInterval = MQTT_KEEP_ALIVE_TIME_S;
	_mqtt_opt.MQTTVersion = 4;
	_mqtt_opt.cleansession = 1;


	ret = _mqtt->connect(_mqtt_opt);

    if( ret == MQTT::SUCCESS )
    {
    	PRINT_LOG(F("Connect successfully"));

    }
    else
    {
    PRINT_LOG(F("Fail to connect"));
    }

	return ret;
}

int mqttWrapper::connect(IPAddress ip, const int port, const char* clientid, const char* username, const char* password)
{
	this->setIP(ip);
	this->setPort(port);
	this->setClientId(clientid);
	this->setUser(username, password);

	return this->connect();
}


int mqttWrapper::connect(const char* host, const int port, const char* clientid, const char* username, const char* password)
{
	this->setHost(host);
	this->setPort(port);
	this->setClientId(clientid);
	this->setUser(username, password);

	return this->connect();
}

int mqttWrapper::disconnect()
{
	int ret = MQTT::FAILURE;

	if( _mqtt->isConnected() == true )
		ret = this->_mqtt->disconnect();

	return ret;
}

int mqttWrapper::subscribeTopic(const char* topic, int qos)
{
	int ret;

	if( _mqtt->isConnected() == false )
	{
		return MQTT::FAILURE;
	}

	ret = _mqtt->subscribe(topic, qos, NULL);

    if( ret != MQTT::SUCCESS )
    	PRINT_LOG(F("Fail to subscribe"));

    return ret;
}

int mqttWrapper::unsubscribeTopic(const char* topic)
{
	int ret;

	if( _mqtt->isConnected() == false )
	{
		return MQTT::FAILURE;
	}

	ret = _mqtt->unsubscribe(topic);
    if( ret != MQTT::SUCCESS )
    	PRINT_LOG(F("Fail to unsubscribe"));

    return ret;
}

int mqttWrapper::publish(ArduinoJson::JsonObject& pubMessage, const char* topic, int qos)
{
	int ret;
	char buffer[DEFAULT_TRIP_BUFFER_SIZE] = {0,};

	if( _mqtt->isConnected() == false )
	{
		return MQTT::FAILURE;
	}

	pubMessage.printTo(buffer, sizeof(buffer));

    MQTT::Message message;
    message.qos = qos;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buffer;
    message.payloadlen = strlen(buffer);

    PRINT_DBG((char*)message.payload);

    ret = _mqtt->publish(topic, message);
    if( ret != MQTT::SUCCESS )
    	PRINT_LOG(F("Fail to publish"));

    return ret;
}


int mqttWrapper::publish(const char* pubMessage, const char* topic, int qos)
{
	int ret;

	if( _mqtt->isConnected() == false )
	{
		return MQTT::FAILURE;
	}

    MQTT::Message message;
    message.qos = qos;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)pubMessage;
    message.payloadlen = strlen(pubMessage);

    PRINT_DBG((char*)message.payload);

    ret = _mqtt->publish(topic, message);
    if( ret != MQTT::SUCCESS )
    	PRINT_LOG(F("fail to publish"));

    return ret;
}

void mqttWrapper::mqtt_yield(void)
{
	if( _network.connected() == true && _mqtt->isConnected() == true )
	{
		_mqtt->yield(MQTT_TIMEOUT_MS);
	}
	else if(_network.connected() == false && _mqtt->isConnected() == true)
	{
		_mqtt->disconnect();
	}
	else
	{
		PRINT_LOG(F("Connecting to Broker.."));
		_network.disconnect();
		this->connect();
		this->subscribeTopic(_topic, 0);
	}
}


