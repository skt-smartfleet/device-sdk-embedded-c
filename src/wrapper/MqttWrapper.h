/*
 * MqttWrapper.h
 *
 *  Created on: 2017. 12. 10.
 *      Author: Daniel
 */

#ifndef SKT_SMARTFLEET_WRAPPER_MQTTWRAPPER_H_
#define SKT_SMARTFLEET_WRAPPER_MQTTWRAPPER_H_

#include <Arduino.h>
#include <Stream.h>

#include "../util/json/ArduinoJson.h"

#include "../network/mqtt/MQTTClient.h"
#include "../network/Network.h"
#include "../network/Timer.h"
#include "../wrapper/Smartfleet_Type.h"


typedef void (*rcv_message_cb_t)(const char* topic, const char* payload);

class mqttWrapper
{
public:

	mqttWrapper(Client& client);
	mqttWrapper(){ }
	~mqttWrapper(){ }

	void begin();
	void begin(Client& client);
	void setHost(const char* host);
	void setPort(const int port);
	void setUser(const char* username, const char* password);

	void setToken(const char* token);
	void setTopic(const char* topic);

	rcv_message_cb_t rcv_message_cb;
	void setMessageHandler(rcv_message_cb_t cb);

	void initialize();
	void finalize();

	bool isMqttConnectStatus();
	bool isConnected();

	void connect();
	void connect(IPAddress ip, const int port, const char* username, const char* password);
	void connect(const char* host, const int port, const char* username, const char* password);

	void disconnect();


	void subscribeTopic(const char* topic, int qos);
	void unsubscribeTopic(const char* topic);
	void subscribewithcallback(const char* topic, int qos, void* cb);
	void publish(JsonObject& pubMessage, const char* topic, int qos);
	void publish(const char* pubMessage, const char* topic, int qos);


	void subscribeLinkId();
	void subscribeLinkId(const char* linkId);
	void unsubscribex(const char* linkId);

	void mqtt_yield();

private:
	char* _host;
	int _port;
	char* _username;
	char* _password;
	char* _token;
	char* _topic;

	Client* _client;
    Network _network;
    MQTT::Client<mqttWrapper, Network, Timer, DEFAULT_BUFFER_SIZE, 0> *_mqtt;
    MQTTPacket_connectData _mqtt_opt;



    mqttWrapper callbackMessage(MQTT::MessageData& messageData);

};


#endif /* SKT_SMARTFLEET_WRAPPER_MQTTWRAPPER_H_ */
