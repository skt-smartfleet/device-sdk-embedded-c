#include "SmartfleetClient.h"


DeviceActivation g_da;
FirmwareUpdate g_fu;
FirmwareUpdateChunk g_fuc;
char g_buffer[DEFAULT_RPC_BUFFER_SIZE];
char g_req_id[64];

RPCType _rpc_rsp_type;
SMARTFLEET_STATE _state;

void smartfleet::onRPCMessageArrived(const char* topic, const char* payload)
{
	int i, len;
	char method[32];
	char* ret;

	startWork();

	StaticJsonBuffer<DEFAULT_RPC_BUFFER_SIZE> rpcbuffer;
	JsonObject& rpcjsonObj = rpcbuffer.parseObject(payload);

	if( rpcjsonObj.success() == false )
	{
		PRINT_LOG(F("Receive message, but it isn't Json."));
		return;
	}

	if(rpcjsonObj.containsKey(JSON_RPC_METHOD) == false )
	{
		PRINT_LOG(F("Receive RPC message, but didn't contain method."));
		return;
	}

	arrivedRPCMessage arrivedRPCMessage;
	arrivedRPCMessage.getReqId(topic, g_req_id);
	arrivedRPCMessage.getMethod(rpcjsonObj, method);

	len = strlen(method);
	for(i = 1; i < sizeof(RPCState) / sizeof(RPCState[0]); i++)
	{
		if ( strncmp(method, RPCState[i].method, len) == 0 )
		{
			setRPCType(RPCState[i].rpc_type);
			arrivedRPCMessage.messageUnpackage(rpcjsonObj, RPCState[i].rpc_type);
			break;
		}
	}
	endWork();
}

SF_ERROR smartfleet::responseDeviceActivation(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	rpcMessage rpcMessage;
	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESPONSE_CODE, 0), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESPONSE_SEND_FAIL;
	}

	PRINT_LOG("Send Response DeviceActivation");
	return RET_SUCCESS;
}


SF_ERROR smartfleet::responseFirmwareUpdate(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	rpcMessage rpcMessage;
	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESPONSE_CODE, 0), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESPONSE_SEND_FAIL;
	}

	PRINT_LOG(F("Send Response FirmwareUpdate"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::responseOBDReset(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	rpcMessage rpcMessage;
	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESPONSE_CODE, 0), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESPONSE_SEND_FAIL;
	}

	PRINT_LOG(F("Send Response OBDReset"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::responseDeviceSerialNumberCheck(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	rpcMessage rpcMessage;
	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESPONSE_CODE, 0), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESPONSE_SEND_FAIL;
	}

	PRINT_LOG(F("Send Response DeviceSerialNumberCheck"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::responseClearDeviceData(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	rpcMessage rpcMessage;
	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESPONSE_CODE, 0), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESPONSE_SEND_FAIL;
	}

	PRINT_LOG(F("Send Response ClearDeviceData"));
	return RET_SUCCESS;
}

SF_ERROR smartfleet::responseFirmwareUpdateChunk(const char* topic)
{
	int ret;
	if( startWork() == false )		return RET_ERROR_PROCESS_OVERFLOW;

	StaticJsonBuffer<DEFAULT_RESP_BUFFER_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	rpcMessage rpcMessage;
	ret = _mqttwrapper.publish(rpcMessage.messagePackage(root, SUCCESS_RESPONSE_CODE, 0), topic, MQTT_QOS);

	endWork();

	if( ret != MQTT::SUCCESS )
	{
		return RET_ERROR_RESPONSE_SEND_FAIL;
	}

	PRINT_LOG(F("Send Response FirmwareUpdateChunk"));
	return RET_SUCCESS;
}





bool smartfleet::startWork()
{
	if ( isIdleState() == true )
	{
		_state = STATE_DOWORK;
		return true;
	}
	return false;
}

bool smartfleet::endWork()
{
	if ( getCurrentState() == STATE_DOWORK )
	{
		_state = STATE_IDLE;
		return true;
	}
	return false;
}

bool smartfleet::isIdleState()
{
	if( getCurrentState() == STATE_IDLE )
		return true;
	else false;
}


SMARTFLEET_STATE smartfleet::getCurrentState()
{
	return _state;
}

void smartfleet::setRPCType(RPCType type)
{
	_rpc_rsp_type = type;
}

RPCType smartfleet::getRPCType()
{
	return _rpc_rsp_type;
}
