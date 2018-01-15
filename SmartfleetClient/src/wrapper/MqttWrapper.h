#ifndef SKT_SMARTFLEET_WRAPPER_MQTTWRAPPER_H_
#define SKT_SMARTFLEET_WRAPPER_MQTTWRAPPER_H_

#include <Arduino.h>
#include <Stream.h>

#include "../util/json/ArduinoJson.h"

#include "../network/mqtt/MQTTClient.h"
#include "../network/Network.h"
#include "../network/Timer.h"
#include "../wrapper/Smartfleet_Type.h"

typedef enum USED_IP
{
	MQTT_NOT_SET,
	MQTT_USED_IP,
	MQTT_USED_DOMAIN
};

typedef void (*rcv_message_cb_t)(const char* topic, const char* payload);

class mqttWrapper
{
public:

	mqttWrapper(Client& client);
	mqttWrapper(){ }
	~mqttWrapper(){ }

	/**
	 * @brief mqtt init
	 * @param $client TCP Client class
	 * @return void
	 */
	void begin(void);
	void begin(Client& client);

	/**
	 * @brief MQTT Client 정보 설정
	 * @param $ip
	 * 		  $host
	 *        $port
	 *        $username
	 *        $password
	 *        $clientid
	 * @return void
	 */
	void setIP(IPAddress ip);
	void setHost(const char* host);
	void setPort(const int port);
	void setUser(const char* username, const char* password);
	void setClientId(const char* clientid);

	/**
	 * @brief MQTT 접속 후 자동 구독할 토픽 등록
	 * @param $topic 구독할 topic
	 * @return void
	 */
	void setSubscribeTopic(const char* topic);

	/**
	 * @brief mqtt init
	 * @param void
	 * @return void
	 */
	void initialize(void);

	/**
	 * @brief MQTT 메시지 수신시 callback 등록
	 * @param $cb callback
	 * @return void
	 */
	void setMessageHandler(rcv_message_cb_t cb);

	/**
	 * @brief MQTT 연결 상태 확인
	 * @param void
	 * @return true/false
	 */
	bool isConnected(void);

	/**
	 * @brief MQTT 연결, 설정되어있는 MQTT정보로 접속 시도
	 * @param void
	 * @return 0(ok)/-1(error)
	 */
	int connect(void);

	/**
	 * @brief MQTT 연결
	 * @param $host
	 * 		  $port
	 * 		  $clientid
	 * 		  $username
	 * 		  $password
	 * @return 0(ok)/-1(error)
	 */
	int connect(IPAddress ip, const int port, const char* clientid, const char* username, const char* password);
	int connect(const char* host, const int port, const char* clientid, const char* username, const char* password);

	/**
	 * @brief MQTT disconnect
	 * @param void
	 * @return 0(ok)/-1(error)
	 */
	int disconnect(void);

	/**
	 * @brief MQTT topic 구독 요청
	 * @param $topic
	 *        $qos
	 * @return 0(ok)/-1(error)
	 */
	int subscribeTopic(const char* topic, int qos);

	/**
	 * @brief MQTT topic 구독 해제
	 * @param $topic
	 * @return 0(ok)/-1(error)
	 */
	int unsubscribeTopic(const char* topic);

	/**
	 * @brief MQTT JsonObject publish
	 * @param $pubMessage JsonObject
	 *        $topic
	 *        $qos
	 * @return 0(ok)/-1(error)
	 */
	int publish(ArduinoJson::JsonObject& pubMessage, const char* topic, int qos);

	/**
	 * @brief MQTT plain text publish
	 * @param $pubMessage 메시지
	 *        $topic
	 *        $qos
	 * @return 0(ok)/-1(error)
	 */
	int publish(const char* pubMessage, const char* topic, int qos);

	/**
	 * @brief MQTT yield, MQTT 프로토콜 수행
	 * @param void
	 * @return void
	 */
	void mqtt_yield(void);

private:
	IPAddress _ip;
	char* _host = 0;
	USED_IP _used_ip = MQTT_NOT_SET;

	int _port = 0;
	char* _username = 0;
	char* _password = 0;
	char _clientid[40];
	char* _topic = 0;

	rcv_message_cb_t rcv_message_cb = NULL;

	Client* _client;
    Network _network;
    MQTT::Client<mqttWrapper, Network, Timer, DEFAULT_MQTT_BUFFER_SIZE, 0> *_mqtt;
    MQTTPacket_connectData _mqtt_opt;

    mqttWrapper callbackMessage(MQTT::MessageData& messageData);
};


#endif /* SKT_SMARTFLEET_WRAPPER_MQTTWRAPPER_H_ */
