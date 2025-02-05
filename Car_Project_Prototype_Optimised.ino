#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>  
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//SCREEN
#define OLED_ADDR   0x3C
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

int DataPick = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, -1);

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.println(bus);
}
//SCREEN 


//This is a character buffer that will store the data from the serial port
char rxData[20];
char rxIndex=0;



//Variables to hold car data
int vehicleSpeed=0; //Works
int vehicleRPM=0;   //Works
int engineTemp=0;   //Works
int fuelPress=0;    //Nope
int airIntakePress=0; //Nope
int aitIntakeTemp=0;  //Nope
int throttlePos=0;    //Nope
int fuelTankLvl = 0;  //Nope
int massairflow = 0;  //Nope
int timesinceStart = 0; //Nope
int fuellevel2 = 0;   //Nope

int maxSpeed = 0;
int maxRPM = 0;
int maxTemp = 0;

void setup(){
  //Both the Serial LCD and the OBD-II-UART use 9600 bps.
  Serial.begin(9600); //OBD BUS
  Serial1.begin(115200);  //Communication with ESP32

  

//SCREEN
Wire.begin();

//Prepare the LCD screens
TCA9548A(0);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
{
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
delay(100);
display.clearDisplay();
TCA9548A(1);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
{
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
delay(100);
display.clearDisplay();
TCA9548A(2);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
{
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
delay(100);
display.clearDisplay();
TCA9548A(3);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
{
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
delay(100);
display.clearDisplay();
TCA9548A(4);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
{
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
delay(100);
display.clearDisplay();
TCA9548A(5);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
{
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
delay(100);
display.clearDisplay();


//Test the screens
//SCREEN 1
  TCA9548A(0);
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println("0 OK");
  display.display(); 

//SCREEN 1

//SCREEN 2
  TCA9548A(1);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("1 OK");
  display.display(); 
//SCREEN 2
//SCREEN

TCA9548A(2);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("2 OK");
  display.display(); 
  
  TCA9548A(3);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("3 OK");
  display.display(); 

  TCA9548A(4);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("4 OK");
  display.display(); 

  TCA9548A(5);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("5 OK");
  display.display(); 

  TCA9548A(6);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("6 OK");
  display.display(); 

  TCA9548A(7);
  display.clearDisplay();  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);//x, y (x,128) (y,64)
  display.println("7 OK");
  display.display(); 
  
  //Wait for a little while before sending the reset command to the OBD-II-UART
  delay(1500);
  //Reset the OBD-II-UART
  Serial.println("ATZ");

  //Wait for a bit before starting to send commands after the reset.
  delay(1000);



  //Delete any data that may be in the serial port before we begin.
  while (Serial.available()) Serial.read();
  delay(20);
}
void loop()
{
    
    
    //Delete any data that may be in the serial port before we begin.  
    delay(30);
    while (Serial.available()) Serial.read();
    //delay(30);
    //Get RPM data
    Serial.println("010C"); 

    //Read the response
    getResponse();
    getResponse();

    //Convert it to readable data
    vehicleRPM = ((strtol(&rxData[6],0,16)*256)+strtol(&rxData[9],0,16))/4;
     
    //Print the rpm data
    //Serial.print("RPM: ");
    //Serial.println(vehicleRPM); 
      
    
    //SCREEN 0
    TCA9548A(0);
    display.clearDisplay();
    display.setTextSize(5);
    display.fillRect(0, 0, map(vehicleRPM,0,5000,0,128), 15, WHITE);
    display.setCursor(0, 20);
    display.println(vehicleRPM);
    display.setCursor(85, 40);
    display.display();
    //SCREEN 0

    delay(30);
    while (Serial.available()) Serial.read();
    //delay(30);
    //Speed in KMs/h
    Serial.println("010D"); 
    
    getResponse();
    getResponse();
    //Read the response
    vehicleSpeed = strtol(&rxData[6],0,16);
    //Serial.print(vehicleSpeed);
    //Convert it to Ms/h
    if(vehicleSpeed != 0)
    {
      vehicleSpeed = vehicleSpeed / 1.6094;
    }
    
    //SCREEN 1
    TCA9548A(1);
    display.clearDisplay();
    display.setTextSize(6);
    display.fillRect(0, 0, map(vehicleSpeed,0,80,0,128), 15, WHITE);   
    display.setCursor(10, 20);
    if(vehicleSpeed < 70)
    {
      display.println(vehicleSpeed );       
    } 
    else
    {
      display.println("LOL"); 
    }
    display.setCursor(85, 40);
    display.setTextSize(2);
    display.println("mph");  
    display.display(); 
    //SCREEN 1

    delay(30);
    while (Serial.available()) Serial.read();
    //delay(30);
    Serial.println("0105"); //Engine Temp
    
    
    getResponse();
    getResponse();
    
    //Read the response
    engineTemp = strtol(&rxData[6],0,16);
    
    //Convert data to correct temperature
    engineTemp = engineTemp - 40; 

    //Serial.print("engineTemp: ");
    //Serial.println(engineTemp); 

    //SCREEN 2
    TCA9548A(2);
    display.clearDisplay();
    display.setTextSize(5);
    display.fillRect(0, 0, map(engineTemp,0,110,0,128), 15, WHITE);
    display.setCursor(0, 20);
    display.println(engineTemp);
    display.setCursor(85, 40);
    display.setTextSize(2);
    display.println("C");
    display.display();
    //SCREEN 2
    

    // delay(30);
    // while (Serial.available()) Serial.read();

    // Serial.println("0110"); //Get mass airflow

    // //Read the response
    // getResponse();
    // getResponse();

    // //Convert it to readable data
    // massairflow = ((strtol(&rxData[6],0,16)*256)+strtol(&rxData[9],0,16))/100;
     
    // //SCREEN 3
    // TCA9548A(3);
    // display.clearDisplay();
    // display.setTextSize(5);
    // display.fillRect(0, 0, map(massairflow,0,655,0,128), 15, WHITE);
    // display.setCursor(0, 20);
    // display.println(massairflow);
    // display.setCursor(85, 40);
    // display.setTextSize(2);
    // display.println("C");
    // display.display();
    // //SCREEN 3

  


    // delay(30);
    // while (Serial.available()) Serial.read();

    // Serial.println("011F"); //Get time since start

    // //Read the response
    // getResponse();
    // getResponse();

    // //Convert it to readable data
    // timesinceStart = ((strtol(&rxData[6],0,16)*256)+strtol(&rxData[9],0,16));

    // //SCREEN 4
    // TCA9548A(4);
    // display.clearDisplay();
    // display.setTextSize(5);
    // display.fillRect(0, 0, map(timesinceStart,0,65535,0,128), 15, WHITE);
    // display.setCursor(0, 20);
    // display.println(timesinceStart);
    // display.setCursor(85, 40);
    // display.setTextSize(2);
    // display.println("C");
    // display.display();
    // //SCREEN 4


    
    
    // delay(30);
    // while (Serial.available()) Serial.read();

    // Serial.println("012F"); //Get fuel

    // //Read the response
    // getResponse();
    // getResponse();

    // //Convert it to readable data
    // fuellevel2 = (100/255)*(strtol(&rxData[6],0,16));
      
    // //SCREEN 5
    // TCA9548A(5);
    // display.clearDisplay();
    // display.setTextSize(5);
    // display.fillRect(0, 0, map(fuellevel2,0,100,0,128), 15, WHITE);
    // display.setCursor(0, 20);
    // display.println(fuellevel2);
    // display.setCursor(85, 40);
    // display.setTextSize(2);
    // display.println("C");
    // display.display();
    //SCREEN 5
  if (vehicleSpeed > maxSpeed)
  {
    maxSpeed = vehicleSpeed;
  }
  if (vehicleRPM > maxRPM)
  {
    maxRPM = vehicleRPM;
  }
  if (engineTemp > maxTemp)
  {
    maxTemp = engineTemp;
  }

  senddata();
}

void senddata(void)
{
  Serial1.print("Max RPM : ");
  Serial1.print(maxRPM);
  Serial1.print(" | Max Speed : ");
  Serial1.print(maxSpeed);
  Serial1.print(" | Max Temp : ");
  Serial1.println(maxTemp);
  delay(600);
  
}
//The getResponse function collects incoming data from the UART into the rxData buffer
// and only exits when a carriage return character is seen. Once the carriage return
// string is detected, the rxData buffer is null terminated (so we can treat it as a string)
// and the rxData index is reset to 0 so that the next string can be copied.
void getResponse(void){
  char inChar=0;
  //Keep reading characters until we get a carriage return
  while(inChar != '\r'){
    //If a character comes in on the serial port, we need to act on it.
    if(Serial.available() > 0){
      //Start by checking if we've received the end of message character ('\r').
      if(Serial.peek() == '\r'){
        //Clear the Serial buffer
        inChar=Serial.read();
        //Put the end of string character on our data string
        rxData[rxIndex]='\0';
        //Reset the buffer index so that the next character goes back at the beginning of the string.
        rxIndex=0;
      }
      //If we didn't get the end of message character, just add the new character to the string.
      else{
        //Get the new character from the Serial port.
        inChar = Serial.read();
        //Add the new character to the string, and increment the index variable.
        rxData[rxIndex++]=inChar;
      }
    }
  }
}
 
