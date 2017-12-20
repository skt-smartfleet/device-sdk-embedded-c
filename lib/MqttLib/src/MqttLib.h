  #include <WiFiEspClient.h>
  #include <MQTTClient.h>

  typedef void (*MqttLibCallback)(const char* topic, const char* payload);
  typedef void (*MqttLibErrorCallback)();

  class MqttLib {

  public:
    MqttLib();
    void init(char* host, int  port, char* username, char* password);
    bool connect();
    void loop();
    void publish(const char* topic, const char* message);
    void subscribe(const char* topic);
    void setCallback(MqttLibCallback _callback);
    void setErrorCallback(MqttLibErrorCallback _errorCallback);
    static MqttLibCallback _callback;
    static MqttLibErrorCallback _errorCallback;

    // 연결
    void TRE_Connect(char* host, int port, char* username);
    // 연결 해제
    void TRE_Disconnect();
    // Trip 전송
    void TRE_SendTrip(Trip data);
    // MicroTrip 전송
    void TRE_SendMicroTrip(MicroTrip data);
    //  High Frequency Diag-nostic전송
    void TRE_SendHfd(HFDCapabilityInfomation data);
    //  Diagnostic Info 전송
    void TRE_SendDiagInfo(DiagnosticInfomation data);
    // Collision Warning (Driv-ing) 전송
    void TRE_SendDrivingCollisionWarning(DrivingCollisionWarning data);
    // Collision Warning (Park-ing) 전송
    void TRE_SendParkingCollisionWarning(ParkingCollisionWarning data);
    // Battery Warning 전송
    void TRE_SendBatteryWarning(BatteryWarning data);
    // Unplugged warning 전송
    void TRE_SendUnpluggedWarning(UnpluggedWarning data);
    // trun off warning 전송
    void TRE_SendTurnOffWarning(TurnoffWarning data);

    // Device Activation
    // 차량용 센서를 차량에 부착한 후 활성화하기 위해 필요한 RPC
    void RESPONSE_DeviceActivation(DeviceActivation data,char* topic);
    void RESULT_DeviceActivation(DeviceActivation data char* topic);

    // Firmware Update
    // 차량용 OBD의 펌웨어 업데이트를 위한 RPC
    void RESPONSE_FirmwareUpdate(char* topic);
    void RESULT_FirmwareUpdate(char* topic);

    // OBD Reset
    // 차량용 OBD의 재시작을 위한 RPC 메시지
    void RESPONSE_OBDReset(char* topic);
    void RESULT_OBDReset(char* topic);

    // Device Serial Number Check
    // 차량용 OBD의 시리얼 번호 확인용 RPC
    void RESPONSE_DeviceSerialNumberCheck(char* topic);
    void RESULT_DeviceSerialNumberCheck(DeviceSerialNumberCheck data,char* topic);

    // Clear Device Data
    // 차량용 OBD 데이터 삭제
    void RESPONSE_ClearDeviceData(char* topic);
    void RESULT_ClearDeviceData(char* topic);

    // Firmware Update (Chunk-based)
    // Chunk 기반으로 차량용 OBD의 펌웨어 업데이트를 위한 RPC
    void RESPONSE_FirmwareUpdateChunk(char* topic);
    void RESULT_FirmwareUpdateChunk(har* topic);
    protected:
  };
