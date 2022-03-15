/*
 Name:		    msgTelegram_BOT.ino
 Created:	    14/03/2022
 Author:	    Paulo Fernando <pfsf07@gmail.com>
 Description: 	MCU(Esp32 in this case) that sends a message to a telegram bot when the motion sensor(HC-SR501) detects moviment
 Connections
	HC-SR501      		->     ESP32(WROOM MODULE)
	VCC    				-> 	   Vin, when powered by USB or 5V source
	GND    				->     ESP32 GND
	Output(3V3 Logic) 	-> 	   GPIO 27 
*/
//Telegram Bot library
#include "CTBot.h"

//Interruption pin for the motion sensor
#define PIR   27
//Initialize the library to communicate with the telegram bot 
CTBot myBot;
//Flag to be updated in interruption function 
bool pir_presence_flag = false;
//Function to send messages to telegram bot
void msgTelegramBot(void);
//A way to quickly change WiFi config
//#define HOME  1
#ifdef HOME
String ssid  = ""; // Replace with your WiFi SSID
String pass  = ""; // Replace with your WiFi PASSWORD
#else
String ssid  = ""; //Replace with your WiFi SSID
String pass  = ""; //Replace with your WiFi PASSWORD
#endif
//Replace with the Telgram Bot Token
String token = ""; 
//Interruption function,as short as possible 
void IRAM_ATTR ISR_0(){
    pir_presence_flag = true;
}
//SetUp configurations
void setup(){
	//Interruption pin 
	pinMode(PIR, INPUT_PULLDOWN);
  	//Set motion sensor pin as interrupt, assign interrupt function and set RISING mode
	attachInterrupt(PIR, ISR_0, RISING);
	//Initialize the serial to debug
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");
	//Connect to the WiFi 
	myBot.wifiConnect(ssid, pass);
	//Telegram bot Token generate when you use "Bot Father" in telegram App
	myBot.setTelegramToken(token);
	//Test connection to the bot
	if(myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
	//Initialize 
	msgTelegramBot();	 
}

void loop(){	
}
//Verify bot connection. Just get out when the bot connection is restored
bool reconnectTelgramBot(){
	while(!myBot.testConnection()){
		Serial.println("");
		//Retry WiFi connection
		if(myBot.wifiConnect(ssid, pass)){
			Serial.println("Connection restored");
		}
		else{
			Serial.println("");
		}
	}
	return true;
}

void msgTelegramBot(){
	//Variable to store telegram data
	TBMessage msg;
	while(1){
		//Check incoming message- A first message is needed to start the bot
		if(CTBotMessageText == myBot.getNewMessage(msg)){
			////Send message back to the bot
			myBot.sendMessage(msg.sender.id, msg.text);
			//When a first message is received the MCU starts to monitor the motion sense and send the messages to the bot
			while(1){
				//Motion detected
				if(pir_presence_flag){
					Serial.println("FLAG!");
					pir_presence_flag = false;
					if(!myBot.sendMessage(msg.sender.id, "Motion Detected!")){
						Serial.println("Fail to send the message!");
						//Verify connection with the bot
						while(!reconnectTelgramBot()){
							delay(10);
						}
					}
					delay(5000);
				}
				delay(10);
			}
		}
		delay(10);
	}
}