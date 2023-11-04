///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //* Code to get the voltage, current and power from two AC PZEM sensors connected to the Arduino Mega microcontroller, then all the values *//
 //  are concatenated in one char variable in order to send it through serial communication                                                 // 
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
#include  <PZEM004Tv30.h>
#include <EEPROM.h> 
#include <LiquidCrystal_I2C.h>
///////////////////////////////////////////////////////////////////
//const int totalpower = 4;
//int powerNo[totalpower] = {"",""};
//int offsetpower[totalpower] = {0,3,16,29};
//int tempPower= "";
 /////////////////////////////////////////////////////////////////////////////////////////////////////////
int buttonPushCounter = 0; 
// counter for the number of button presses
int address =0;
int addr = 1;
int add1 = 2;
int add2 = 3;
int add3 = 4;
int add4 = 5;
int add5 = 6;
//int approachAddress1 = 3;
//int approachAddress2 = 4;
int remained = 0;
String ijambo;  
String _buffer;

////////////////////////////////////////////////////////////////////// //////////////////////////////////////////// 
 String data; 
 float V, V1;
 float i, i1;
 float p, p1;
 float e, e1;

 
 
 int saved_phone1;
//////////////////////////////////////////////////////////////////////
PZEM004Tv30 pzem(10,11); //(RX TX
PZEM004Tv30 pzem1(12,13); //(RX TX)
/////////////////////////////////////////////////////////////////////
// defines variables
int _timeout;
int index = 0;
String number = ""; //incoming number
String message = "";
String mynbr1 = "+250783159293";// user number one
//String mynbr2 = "+250785955783";// user number two
//String mynbr3 = "+250780988553";// user number two
char incomingByte;
String incomingData;
bool atCommand = true;
//String _buffer;
////////////////////////////////////////////////////////////////////////////////
#define SIM800_TX_PIN 11
#define SIM800_RX_PIN 10
SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);
///////////////////////////////////////////////////////////////////////////////
int device_1 = 7; // attach pin D13 of Arduino to Device-1
int device_2 = 6; // attach pin D13 of Arduino to Device-2
float energ1=0;
float energ2=0;
float current_value=0;
float new_value1;
float new_value2;

float inter_data;
int fata=0;
float saved1;
float saved2;
float Ec1;
float Ec2;
float bara1=0;
float bara2=0;
int x;
float umubare=0;
float usigaye;
LiquidCrystal_I2C lcd(0x27,20,4);
//////////////////////////////////////////////////////////////////////////////
int bougth1=0;
int bougth2=0;
////////////////////////////
 int a;
  int b;


int j=0;
int k=0;
int l=0;
int n=0;
int v=0;
  
///////////////////////////////////////////////////////////////////////////////
int new_1=555;
 void setup() {
   Serial.begin (112500);
   mySerial.begin(9600); 
   lcd.init();                      // initialize the lcd 
   lcd.init();
   lcd.backlight();
   lcd.setCursor(1,0);
   lcd.print("SMART ENERGY METER ");
   lcd.setCursor(0,1);
   lcd.print("USERS ");
   lcd.setCursor(10,1); 
   lcd.print("POWER"); 
   pinMode(device_1,OUTPUT); 
   pinMode(device_2,OUTPUT);
   digitalWrite(device_1,HIGH);
    digitalWrite(device_2,HIGH); 
    Serial.print("Start running");
    delay(10000);         
   // Serial Communication for GSM Module is starting with 9600 of baudrate speed 
   // Check if you're currently connected to SIM800L
    mySerial.println("AT+CMGF=1");  //Set SMS Text Mode
    delay(1000);
    mySerial.println("AT+CNMI=1,2,0,0,0");  //procedure, how to receive messages from the network
    delay(1000);
    mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read unread messages
    Serial.println("Ready to received Commands..");
   // lcd2(new_data2);
    // lcd1(new_data1);
//
    //////////////////////////////////////////////////////////////////////

EEPROM.write(add3,new_1);
 callNumber();

 }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void loop() {
 
  
 
   Serial.print("runing");


int new_data3=0;
int new_data2=0;

 if (mySerial.available()) {
    delay(100);
    // Serial buffer
    while (mySerial.available()) {
      incomingByte = mySerial.read();
      incomingData += incomingByte;
    }
    delay(10);
    if (atCommand == false) {
    receivedMessage(incomingData);
    } else {
      atCommand = false;
    }
    //delete messages to save memory
    if (incomingData.indexOf("OK") == -1) {
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
      delay(1000);
      atCommand = true;
    }
     incomingData = "";
     
  }  


//////////////////////////////////////////////////////////////////////////////////////
  //Serial.print("Saved is:");
  //Serial.println(saved1);
/////////////////////////////////////////////////////////////////////////////////////////////////
  if (message.indexOf("RB") > -1 && number== mynbr1) {
    subiza();
 EEPROM.write(add2,0);
   }

    if (message.indexOf("RA") > -1&& number== mynbr1) {
      subiza();
 EEPROM.write(address,0);
   }
  
   if (message.indexOf("5A") > -1 && number== mynbr1) {
        
       new_data3=2;
       EEPROM.write(address,new_data3);
       // a=   EEPROM.read(new_data3);
       Serial.print(new_data3);
       Serial.print("power received");
       //unit(new_data3,new_data2);

//////////////////////////////////////////////////////////////////
 }

  if (message.indexOf("5B") > -1 && number==mynbr1) {
        new_data2=1;
        EEPROM.write(add2,new_data2 );
        Serial.print("new data 2  is:");
        Serial.println(new_data2);
     //unit(a,b);
     //unit(new_data3,new_data2);
    // for(int a = )
   
}


if (message.indexOf("D") > -1  ) {
   subiza();     
   
}



 



unit(saved2,saved1);

lcd1();
lcd2();

//EEPROM.read(add2);
saved2=EEPROM.read(address);
//usigaye=EEPROM.read(add2);
saved1=EEPROM.read(add2);



 Serial.println("uwaguzwe1");
 Serial.println(saved2);
 Serial.println("uwaguzwe2");
 Serial.println(saved1);
  //Serial.println("add3");
 //Serial.println(new_1);
delay(1000);
 // e1 = pzem1.energy();
 // e = pzem.energy();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////  

if(saved2== 0){
  
     digitalWrite(device_1,LOW);
     Serial.println("new_data3 is Low");
  
  
  }

  if(saved2>0){
      Serial.println("new_data3 is High");
      digitalWrite(device_1,HIGH);
      //delay(10000);
      //digitalWrite(device_1,LOW);
      //EEPROM.write(address,0);
    }

    if(saved1== 0){
      //digitalWrite(device_1,LOW);
      Serial.println("new_data2 is Low");
      digitalWrite(device_2,LOW);
  
  
  }
  

  if(saved1>0){
     //digitalWrite(device_1,LOW);
     Serial.println("new_data2 is High");
        digitalWrite(device_2,HIGH);
       //  delay(20000);
      //digitalWrite(device_2,LOW);
      //EEPROM.write(add2,0);
    }
  
    }
    
/////////////////////////////////////////////////////////////////////////////////////////////////////
 void subiza(){
  
  if(n==0){
    Reply("User1 Remains:",saved2,"User2 Remains:",saved1);
  n=1;
  }
  else{
    n=0;
    }
  }
  //////////////////////////////////////////////
void pzeem2(){
 V=pzem.voltage(); //voltage obtained from the pzem library
 i = pzem.current(); //current obtained from the pzem library
 p = pzem.power();//power obtained from the pzem library
 e = pzem.energy();//energy obtained from the pzem library 
 delay(1000);
 
Serial.print("V: "); Serial.println(V);
Serial.print("I: "); Serial.println(i);
Serial.print("P: "); Serial.println(p); 
Serial.print("E: "); Serial.println(e); 
Serial.print("");


////////////////////////////////////////////////////////////
  
 
  }

  void pzeem1(){
    
    V1=pzem1.voltage(); //voltage obtained from the pzem library
 i1 = pzem1.current(); //current obtained from the pzem library
 p1 = pzem1.power();//power obtained from the pzem library
 e1 = pzem1.energy();//energy obtained from the pzem library  
 delay(1000);

Serial.print("V1: "); Serial.println(V1);
Serial.print("I1: "); Serial.println(i1);
Serial.print("P1: "); Serial.println(p1); 
//Serial.print("E11: "); Serial.println(energ2); 
Serial.print("E1: "); Serial.println(e1);
Serial.print("");


    
    }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
void receivedMessage(String inputString) {

  //Get The number of the sender
  index = inputString.indexOf('"') + 1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0, index);
  Serial.println("Number: " + number);
  //Get The Message of the sender
  index = inputString.indexOf("\n") + 1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);
  message.toUpperCase(); // uppercase the message received

}

////////////////////////////////////////////////////////////////////////////////////////////
void lcd1(){
     lcd.setCursor(0,2); 
     lcd.print("User A:");
     /////////////////////

}
  void lcd2(){
    
     lcd.setCursor(0,3);
     lcd.print("User B:");
 
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////
 
    void unit(float eng1, float eng2){

     lcd.setCursor(17,2); 
     lcd.print("mwh");
     lcd.setCursor(17,3); 
     lcd.print("mwh");
     lcd.setCursor(10,2);
     lcd.print(eng1); 
     lcd.setCursor(10,3); 
     lcd.print(eng2);
      }

 
 


void Reply(String text,float umuriro,String text1,float umuriro1)
{
  
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
    mySerial.print("AT+CMGS=\""+number+"\"\r");
    delay(1000);
    mySerial.print(text);
    mySerial.print(umuriro);
    mySerial.print("\n");
    mySerial.print(text1);
    mySerial.print(umuriro1);
    delay(100);
    mySerial.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
    delay(1000);
    //Serial.println("SMS Sent Successfully.");
}

String _readSerial() {
  _timeout = 0;
  while  (!mySerial.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (mySerial.available()) {
    return mySerial.readString();
  }
}
  
  
  void callNumber() {
  mySerial.print (F("ATD"));
  mySerial.print (mynbr1);
  mySerial.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}
