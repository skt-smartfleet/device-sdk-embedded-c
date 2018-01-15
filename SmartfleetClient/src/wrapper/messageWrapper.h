#ifndef SKT_SMARTFLEET_WRAPPER_MESSAGEWRAPPER_H_
#define SKT_SMARTFLEET_WRAPPER_MESSAGEWRAPPER_H_

#include "../util/json/ArduinoJson.h"
#include "../wrapper/Smartfleet_Type.h"
#include "../obj/TripMessage.h"
#include "../obj/RPCMessage.h"

class tripMessage : public tripMessage_Base
{
public:
	tripMessage(){};
	~tripMessage(){};

	/**
	 * @brief Trip JsonObject 생성, $tripObj를 Json Object로 생성해서 $jsonObj로 리턴한다
	 * @param $jsonObj JsonObject class
	 *        $ts timestamp
	 *        $ty Trip type
	 *        $tripObj Trip object
	 * @return JsonObject$
	 */
	JsonObject& messagePackage(JsonObject& jsonObj, long ts, TripType ty, void* tripObj);
};


class rpcMessage : public RPCMessage_Base
{
public:
	rpcMessage(){};
	~rpcMessage(){};

	/**
	 * @brief RPC Response, Result JsonObject 생성, $ty에 따라 메시지 생성, $addInfoObj의 데이터가 payload로 추가됨
	 * @param $jsonObj JsonObject class
	 *        $code RPC 리턴 코드
	 *        $ty RPC type, 0이면 response object 생성
	 *        $addInfoObj RPC body
	 * @return JsonObject$
	 */
	JsonObject& messagePackage(JsonObject& jsonObj, int code, int ty, void* addInfoObj = NULL);
};

extern DeviceActivation g_da;
extern FirmwareUpdate g_fu;
extern FirmwareUpdateChunk g_fuc;
extern char g_buffer[DEFAULT_RPC_BUFFER_SIZE];

class arrivedRPCMessage : public RPCMessage_Base
{
public:
	arrivedRPCMessage(){};
	~arrivedRPCMessage(){};

	/**
	 * @brief RPC 메시지를 수신한 $jsonObj를 파싱 후  $messageObj로 각 RPC class로 생성한다.
	 *        $messageObj에 NULL 입력시 extern 되어있는 global class에 정의된다
	 * @param $jsonObj JsonObject class
	 *        $ty RPC type
	 *        $messageObj RPC Object
	 * @return JsonObject$
	 */
	JsonObject& messageUnpackage(JsonObject& jsonObj, RPCType ty, void* messageObj = NULL);

	/**
	 * @brief RPC 메시지를 수신시 메시지에 포함된 method를 파싱 후 포인터 리턴
	 * @param $jsonObj RPC 메시지 jsonObject
	 *        $mtd method 포인터
	 * @return request id ptr
	 */
	char* getMethod(JsonObject& jsonObj, char* mtd);

	/**
	 * @brief RPC 메시지를 수신시 topic에 포함된 request id를 파싱 후 포인터 리턴
	 * @param $topic RPC request topic
	 *        $req_id Request ID
	 * @return request id ptr
	 */
	char* getReqId(const char* topic, char* req_id);

};

#endif /* SKT_SMARTFLEET_WRAPPER_MESSAGEWRAPPER_H_ */
