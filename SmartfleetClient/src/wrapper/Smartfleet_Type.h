#ifndef SKT_SMARTFLEET_WRAPPER_SMARTFLEET_TYPE_H_
#define SKT_SMARTFLEET_WRAPPER_SMARTFLEET_TYPE_H_

#include "../util/LogPrint.h"

#define DEFAULT_MQTT_BUFFER_SIZE 512
#define DEFAULT_TRIP_BUFFER_SIZE 400
#define DEFAULT_RESP_BUFFER_SIZE 80 //128
#define DEFAULT_RPC_BUFFER_SIZE  256 //512

/**
 * @brief Smartfleet State
 */
typedef enum SMARTFLEET_STATE
{
	STATE_NOTCONNECTED,
	STATE_IDLE,
	STATE_DOWORK
};


/**
 * @brief Smartfleet Trip message
 */
typedef enum TripType
{
    ALL,
    TRIP,
    MICRO_TRIP,
    HFD_CAPABILITY_INFORMATION,
    DIAGNOSTIC_INFORMATION,
    DRIVING_COLLISION_WARNING,
    PARKING_COLLISION_WARNING,
    BATTERY_WARNING,
    UNPLUGGED_WARNING,
    TURNOFF_WARNING
};

#define TRIP_SID_STR			"sid"

/**
 * @brief Smartfleet RPC message
 */
typedef enum RPCType
{
	RSP_NULL,
    DEVICE_ACTIVATION = 1,
    FIRMWARE_UPDATE,
    ODB_RESET,
    DEVICE_SERIAL_NUMBER_CHECK,
    CLEAR_DEVICE_DATA,
    FIRMWARE_UPDATE_CHUNK,
	VENDOR_SPECIFIC
};


#define DEVICE_ACTIVATION_STR			"activationReq"
#define FIRMWARE_UPDATE_STR				"fwupdate"
#define OBD_RESET_STR 					"reset"
#define DEVICE_SERIAL_NUMBER_CHECK_STR 	"serial"
#define CLEAR_DEVICE_DATA_STR 			"cleardata"
#define FIRMWARE_UPDATE_CHUNK_STR 		"fwupchunk"
#define VENDOR_SPECIFIC_STR 			"test"

typedef void (*onDeviceActivation_cb)(const char* topic, const char* request_id, const char* method, void* message);
typedef void (*onFirmwareUpdate_cb)(const char* topic, char* request_id, char* method, void* message);
typedef void (*onOBDReset_cb)(const char* topic, char* request_id, char* method, void* message);
typedef void (*onDeviceSerialNumberCheck_cb)(const char* topic, char* request_id, char* method, void* message);
typedef void (*onClearDeviceData_cb)(const char* topic, char* request_id, char* method, void* message);
typedef void (*onFirmwareUpdateChunk_cb)(const char* topic, const char* request_id, const char* method, void* message);
typedef void (*onVendorSpecific_cb)(const char* topic, const char* request_id, const char* method, void* message);

typedef struct RPC_STATE
{
	RPCType rpc_type;
	char* method;
	void (*callback)(const char* topic, const char* request_id, const char* method, void* message);
};

static RPC_STATE RPCState[] =
{
		{RSP_NULL, NULL, NULL},
		{DEVICE_ACTIVATION, 			DEVICE_ACTIVATION_STR, 				NULL},
		{FIRMWARE_UPDATE, 				FIRMWARE_UPDATE_STR, 				NULL},
		{ODB_RESET, 					OBD_RESET_STR, 						NULL},
		{DEVICE_SERIAL_NUMBER_CHECK,	DEVICE_SERIAL_NUMBER_CHECK_STR,		NULL},
		{CLEAR_DEVICE_DATA, 			CLEAR_DEVICE_DATA_STR, 				NULL},
		{FIRMWARE_UPDATE_CHUNK, 		FIRMWARE_UPDATE_CHUNK_STR,			NULL},
		{VENDOR_SPECIFIC, 				VENDOR_SPECIFIC_STR,				NULL},
		{NULL, NULL, NULL}
};

#define JSON_RESPONSE_CODE "result"
#define JSON_RESULT_CODE "results"
#define JSON_RESULT_BODY "additionalInfo"

#define JSON_RPC_METHOD "method"
#define JSON_RPC_PARAMS "params"


/**
 * @brief Smartfleet Response/Result code
 */
#define SUCCESS_RESPONSE_CODE 2000
#define SUCCESS_RESULT_CODE 2000


/**
 * @brief Smartfleet MQTT Topic
 */
#define PUBLISH_TOPIC_TRE 			"v1/sensors/me/tre"
#define PUBLISH_TOPIC_TELEMETRY 	"v1/sensors/me/telemetry"
#define PUBLISH_TOPIC_ATTRIBUTES 	"v1/sensors/me/attributes"

#define SUBSCRIBE_TOPIC 			"v1/sensors/me/rpc/request/+"
#define RPC_RESONSE_TOPIC 			"v1/sensors/me/rpc/response/"
#define RPC_RESULT_TOPIC 			"v1/sensors/me/rpc/result/"
#define RPC_REQUEST_TOPIC 			"v1/sensors/me/rpc/request/"


/**
 * @brief Smartfleet MQTT option
 */

#define MQTT_QOS 1
#define MQTT_MICROTRIP_QOS 0
#define MQTT_TIMEOUT_S 15
#define MQTT_KEEP_ALIVE_TIME_S 60


/**
 * @brief Network Time Protocol option
 */
#define NTP_INTERVAL_S 60       		/// update interval(sec)
#define NTP_TIMEZONE_OFFSET_H 9  		/// UTC+9   Korea
#define NTP_SERVER "pool.ntp.org"		/// NTP Server
//#define NTP_SERVER "time.nist.gov"
//#define NTP_SERVER "time.google.com"


#define MQTT_TIMEOUT_MS (MQTT_TIMEOUT_S * 1000)
#define NTP_INTERVAL_MS (NTP_INTERVAL_S * 1000)       /// update interval(ms)
#define NTP_TIMEZONE_OFFSET (NTP_TIMEZONE_OFFSET_H * 3600)


#endif /* SKT_SMARTFLEET_WRAPPER_SMARTFLEET_TYPE_H_ */
