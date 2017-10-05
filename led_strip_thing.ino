#include <FastLED.h>
#include "Constants.h"
#include "DataStructures.h"

#define LED_PIN 5
#define LED_AMOUNT 8
#define BRIGHTNESS 64
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define MAX_CMD_SIZE 128

CRGB leds[LED_AMOUNT];
float animationSpeed = 10;
bool readingCommand = false;
String commandBuffer = "";

void setup() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_AMOUNT);
    FastLED.setBrightness(BRIGHTNESS);
    Serial.begin(9600);
}

void loop() {
   processSerial(); 
}

/**
 * Animations
 */
void randomColors(){
    for(int i = 0; i < LED_AMOUNT; i++){
        leds[i] = randomColor();
    }
    FastLED.show();
}
void colorGradient(CRGB from, CRGB to){
    int deltaR = to.r - from.r;
    int deltaG = to.g - from.g;
    int deltaB = to.b - from.b;
    deltaR /= LED_AMOUNT; 
    deltaG /= LED_AMOUNT; 
    deltaB /= LED_AMOUNT;
    CRGB cur = from;
    for(int i = 0; i < LED_AMOUNT; i++){
        leds[i] = cur;
        cur.r += deltaR;
        cur.g += deltaG;
        cur.b += deltaB;
    }
    FastLED.show();
}
void colorSweep(CRGB sweepTo, int slowdown){
    for(int i = 0; i < LED_AMOUNT; i++){
        leds[i] = sweepTo;
        FastLED.show();
        if(slowdown > 0) delay(slowdown);
    }
}
/*
 * Utility methods
 */
CRGB randomColor(){
    return randomColor(false);
}
CRGB randomColor(bool includeBlack){
    int rnd = random(includeBlack ? -1 : 0, 7);
    switch(rnd){
        case 0: return CRGB::Red;
        case 1: return CRGB::Green;
        case 2: return CRGB::Blue;
        case 3: return CRGB::Yellow;
        case 4: return CRGB::White;
        case 5: return CRGB::Purple;
        case 6: return CRGB::Brown;
        case 7: return CRGB::Aqua;
        default: return CRGB::Black;
    }
}
/*
 * Serial
 */
void processSerial(){
    char data;
    int cur;
    while((cur = Serial.available()) >= 0){
        data = Serial.read();
        if(data == '/') readingCommand = true;
        if(readingCommand){
            if(data == '\n' || data == '\r' || data == ';'){
                readingCommand = false;
                Command cmd = parseIntoCommand(commandBuffer);
                return;
            }
            else if(data < ' ' || data > '~') continue;
            else{
                commandBuffer += data;
                if(commandBuffer.length() > MAX_CMD_SIZE){
                    Serial.println("Stopped reading command, commands must be UNDER " + String(MAX_CMD_SIZE) + " bytes!");
                    readingCommand = false;
                    return;
                }
            }
        }
    }
}
Command parseIntoCommand(String text){
    int cmdSeperator = 0, sepInst = 0;
    String cmdName = "", par1 = "", par2 = "", par3 = "", par4 = "";
    for(int i = 0; i < text.length(); i++){
        cmdSeperator = i;
        if(text.charAt(i) == ' '){
            cmdName = text.substring(1, cmdSeperator);
            sepInst++;
        }
    }
    String cmdName = text.substring(1, cmdSeperator);
    Serial.println("Got command: " + cmdName);
    return new Command(cmdName, par1, par2, par3, par4);
}
void processCommand(Command cmd){
    
}
void printHelp(){
    Serial.println("Help:");
    Serial.println("Set animation speed - /speed <amount>");
    Serial.println("Set animation - /anim <animatio id>");
    Serial.println("Set brightness - /brightness <percent (0 to 100)>");
    Serial.println("Set individual LED - /led <num> <r> <g> <b>");
    Serial.println("Set all LEDs - /all <r> <g> <b>");
    Serial.println("View this again - /help");
}

