#include "Motor.h"

/*--------Pins--------*/
#define headLightPin 6
#define batteryPin 0
/*--------Constants--------*/
const int pingTime = 250;
/*--------Timing--------*/
const unsigned long lastDistanceUpdate = 0;
unsigned long lastPing = 0;
/*--------Stuff--------*/
unsigned int batteryVoltage = 0;
bool headlightOn = false;
unsigned int brightness = 1023;
bool debugMode = false;

void setup(){
	Serial.begin(9600);
	pinMode(batteryPin, INPUT);
	pinMode(headLightPin, OUTPUT);
	motorInitiate();
	lastPing = millis();
}
void loop(){
	if(Serial.available()){
		char data = Serial.read();
        processBasicCommand(data);
		if(data == '@'){
			String command = "";
			while(data != ';'){
				data = Serial.read();
				if(data > 33) command = command + data;
			}
			processCommand(command);
            Serial.flush();
		}
		else processBasicCommand(data);
	}
	statUpdate();
}

void processBasicCommand(char data){
    switch(data){
        case '1':
            debug("Motor 1 forward");
            motor1Forward();
            break;
        case '2':
            debug("Motor 1 backward");
            motor1Backward();
            break;
        case '3':
            debug("Motor 2 forward");
            motor2Forward();
            break;
        case '4':
            debug("Motor 2 backward");
            motor2Backward();
            break;
        case '5':
            debug("Motor 1 stopping");
            motor1Stop();
            break;
        case '6':
            debug("Motor 2 stopping");
            motor2Stop();
            break;
        case '7':
            debug("Motor 2 forward");
            motor2Forward();
            break;
        case 'H':
            debug("Headlights enabled");
            analogWrite(headLightPin, brightness);
            headlightOn = true;
            break;
        case 'h':
            debug("Headlights disabled");
            analogWrite(headLightPin, 0);
            headlightOn = false;
            break;
        case '0':
            debug("Motors stopped");
            allMotorStop();
            break;
    }
}
void batteryUpdate(){
	batteryVoltage = ((analogRead(batteryPin) * (5.000 / 1023.000)) * 2.000) * 1000;
	if(batteryVoltage < 6500 && areMotorsEnabled()){
		Serial.print("*tBattery critical!\nShutting down motors!\n*");
		setMotorsEnabled(false);
	}
	Serial.print("*B");
	Serial.print(batteryVoltage);
	Serial.print("*");
}
void statUpdate(){
	if(millis() >= lastPing + pingTime){
        batteryUpdate();
		lastPing = millis();
	}
}
void processCommand(String in){
	if(in.startsWith("debug=")){
		if(in.substring(getCommandInputStart(in)) == "true;"){
			debugMode = true;
			debug("Debug mode enabled!");
		}
		else{
			debug("Debug mode disabled!");
			debugMode = false;
		}
	}
	if(in.startsWith("brightness=")){
		brightness = getCommandInputInt(in);
		if(headlightOn) 
		    analogWrite(headLightPin, brightness);
		debug("Brightness set to: " + String(brightness));
	}
	if(in.startsWith("motorsEnabled=")){
		debug(in.substring(getCommandInputStart(in)));
		if(in.substring(getCommandInputStart(in)) == "true;"){
			setMotorsEnabled(true);
			debug("Motors enabled!");
		}
		else{
			setMotorsEnabled(false);
			debug("Motors disabled!");
		}
	}
	if(in.startsWith("ping")) 
	    Serial.println("pong");
}
int getCommandInputInt(String in){
	return in.substring(getCommandInputStart(in), in.length()).toInt();
}
int getCommandInputStart(String in){
	for(int i = 0; i < in.length(); i++){
		if(in.charAt(i) == '=') 
		    return i + 1;
	}
	return -1;
}
void debug(String in){
	if(debugMode) 
	    Serial.println(in);
}
