#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEUUID serviceID("54d8e679-40e1-40d1-b2ec-e6bd58e9db81");        //Universal read only identifier
BLEUUID readonlyNotifyRPMChairID("28e2baa3-3006-4675-a3b6-ec2bc273e3e5"); //Notify RPM Service
BLEUUID readonlyNotifySpeedChairID("28e2baa3-3006-4675-a3b6-ec2bc273e3e4"); //Notify Speed Service
BLEUUID readonlyNotifyTempChairID("28e2baa3-3006-4675-a3b6-ec2bc273e3e3"); //Notify Temp Service
BLEUUID readonlyChairID("392a3ded-251a-4643-90f0-f0a93603b05e");

//HardwareSerial Serial1(1);

BLECharacteristic *readNotifyRPMCharacteristic;    //Create a notify RPM characteristic outside of the setup function
BLECharacteristic *readNotifySpeedCharacteristic;    //Create a notify Speed characteristic outside of the setup function
BLECharacteristic *readNotifyTempCharacteristic;    //Create a notify Temp characteristic outside of the setup function

uint32_t value = 0;

int speed = 0;
int RPM = 0;
int temp = 0;

void setup() {

  
  Serial.begin(115200);                // USB Serial for debugging
  Serial1.begin(115200, SERIAL_8N1, 16, 17);

  BLEDevice::init("Warp Wormhole"); 

  BLEServer *pServer = BLEDevice::createServer();

  //Create a server with ID
  BLEService *pService = pServer->createService(serviceID);

  readNotifyRPMCharacteristic = pService->createCharacteristic(readonlyNotifyRPMChairID,   BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY ); //set read only and notify characteristic 
  readNotifyRPMCharacteristic -> addDescriptor(new BLE2902()); //Add descriptor. Not sure why. It doesn't work without it.
  readNotifyRPMCharacteristic -> setValue("Waiting for data...");

  readNotifySpeedCharacteristic = pService->createCharacteristic(readonlyNotifySpeedChairID,   BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY ); //set read only and notify characteristic 
  readNotifySpeedCharacteristic -> addDescriptor(new BLE2902()); //Add descriptor. Not sure why. It doesn't work without it.
  readNotifySpeedCharacteristic -> setValue("Waiting for data...");

  readNotifyTempCharacteristic = pService->createCharacteristic(readonlyNotifyTempChairID,   BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY ); //set read only and notify characteristic 
  readNotifyTempCharacteristic -> addDescriptor(new BLE2902()); //Add descriptor. Not sure why. It doesn't work without it.
  readNotifyTempCharacteristic -> setValue("Waiting for data...");
  
  pService->start(); //Start the service

  //Advertising config
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(serviceID);
  pAdvertising->setScanResponse(true);

  //functions that help with Iphone connections issue. LMAO. Apple problem XD

  //Start advertising the device
  BLEDevice::startAdvertising();
  readNotifyRPMCharacteristic -> notify();

  readNotifySpeedCharacteristic -> notify();
  readNotifyTempCharacteristic -> notify();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()) {         // Check if data is available on Serial1
    String incomingData = Serial1.readString();  // Read incoming data
    Serial.print("Received from Mega: "); // Print to Serial Monitor
    //incomingData.trim();
    Serial.println(incomingData);

    int rpmStart = incomingData.indexOf("Max RPM : ") + 10;
    int rpmEnd = incomingData.indexOf(" |", rpmStart);
    RPM = incomingData.substring(rpmStart,rpmEnd).toInt();

    int SpeedStart = incomingData.indexOf("Max Speed : ") + 10;
    int SpeedEnd = incomingData.indexOf(" |", SpeedStart);
    speed = incomingData.substring(SpeedStart,SpeedEnd).toInt();

    int TempStart = incomingData.indexOf("Max Temp : ") + 10;
    int TempEnd = incomingData.indexOf(" |", TempStart);
    temp = incomingData.substring(TempStart,TempEnd).toInt();


    Serial.print("RPM : ");
    Serial.println(RPM);

    Serial.print("Speed : ");
    Serial.println(speed);

    Serial.print("Temp : ");
    Serial.println(temp);

    readNotifyRPMCharacteristic -> setValue("Max RPM: " + String(RPM)); //  Change this characteristic
    readNotifyRPMCharacteristic -> notify(); //Push the new time

    readNotifySpeedCharacteristic -> setValue("Max Speed: " + String(speed)); //  Change this characteristic
    readNotifySpeedCharacteristic -> notify(); //Push the new time
    
    readNotifyTempCharacteristic -> setValue("Max Temperature: " + String(temp)); //  Change this characteristic
    readNotifyTempCharacteristic -> notify(); //Push the new time
  

  }
  //delay(90);
}
