# Telegram_Bot
- Description: 	MCU(Esp32 in this case) that sends a message to a telegram bot when the motion sensor(HC-SR501) detects movement. When motion is detected an interruption is triggered and over a WiFi connection the ESP32 sends a message to the Telegram Bot.

- Connections:
	
  HC-SR501 ->     ESP32(WROOM MODULE)
	
  VCC -> 	   Vin, when powered by USB or 5V source
	
  GND ->     ESP32 GND
	
  Output(3V3 Logic) -> 	   GPIO 27 

- Dependencies:
     - Installing ESP32 board in Arduino IDE   : https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
     - Arduino library to manage Telegram Bots : https://github.com/shurillu/CTBot
     - Creating Telegram Bot with Bot Father   : https://sendpulse.com/knowledge-base/chatbot/create-telegram-chatbot~
