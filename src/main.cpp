#include <Arduino.h>                //include basic Arduino library
#include <SmartLeds.h>              //SmartLeds - library for controll intelligent leds (NEOIPIXEL) maked by: https://github.com/yaqwsx
#include <WiFi.h>                   //basic library for control WiFi on ESP32
#include <AsyncTCP.h>               //must have library for Asynchronous Web Server maked by: https://github.com/me-no-dev
#include <ESPAsyncWebServer.h>      //library for Asynchronous Web Server on ESP32 maked by: https://github.com/me-no-dev
#include <webpage.h>                //header file with web page, which will ESP send to user device

AsyncWebServer server(80);          //starts web server on port 80

#define LED_PIN 32                  //data pin for intelligent leds at the top of hat
#define BATTERY_PIN 27              //pin for measure battery voltage
#define LED_COUNT 23                //number of leds at the top of hat
#define CHANNEL 0                   //channel of SmartLeds controller for top of hat
#define LED_REAR_PIN 5              //data pin for leds at the rear of hat
#define LED_REAR_COUNT 6            //num. of leds at rear of the hat
#define CHANNEL_1 1                 //channel of SmartLeds controller for rear of the hat

SmartLed leds (LED_WS2812, LED_COUNT, LED_PIN, CHANNEL, DoubleBuffer);                  //creates member called leds - top of the hat
SmartLed rear (LED_WS2812, LED_REAR_COUNT, LED_REAR_PIN, CHANNEL_1, DoubleBuffer);      //creates member called rear - rear of the hat

const char *ssid = "Klobouk";           //change here for WiFi AP SSID
const char *password = "Robotika";      //change here for WiFi AP password

volatile int brightness = 255;          //default brightness (0-255, 255 = full)
volatile int STEP = 10;                 //step for brightness regulation
volatile uint8_t mode, hue, randHue;    //mode selection, hue of color, hue for disco
volatile bool lowBat = 0;               //status flag for battery control

volatile int snakePosition = 5;                     //starting snake position (maybe it can be 0??)
volatile uint8_t beatPosition = 0;                  //beat starting value
volatile int beatCount = 1;                         //beat count up (== 1) or count down (== -1)
volatile bool rearLED, rearLED_last = 0;            //statuses of rear leds

int readBattery(){                          //read battery voltage 300 times and return average value
    int meas = 0;
    for (int i = 0; i != 300; ++i)
        meas += analogRead(BATTERY_PIN);
    int voltage = meas / 300;
return voltage;
}

void clearLeds()                            //makes leds at the top clean
{
    for (int i = 0; i != LED_COUNT; ++i)
        leds[i] = Hsv {0, 0, 0};
    leds.show();
}

void controlLeds()                      //main function to drive all leds effects 
{
    if (lowBat != 1){                   //???? turn this function only if battery is OK - doesn't work yet!!!
        switch (mode){
            case 0:     //nothing - "Budiž tma"
                for (int i = 0; i != LED_COUNT; ++i)
                    leds[i] = Hsv {0, 0, 0};
                leds.show();
                for (int i = 0; i != LED_COUNT; ++i)
                    leds[i] = Hsv {0, 0, 0};
                leds.show();
                break;
            case 1:     //find - "Přivolávač kamarádů"
                for (int i = 0; i != 3; ++i){
                    for (int j = 0; j != LED_COUNT; ++j)
                        leds[j] = Hsv {0, 0, 255};
                    leds.show();
                    ledcWrite(0, 255);
                    ledcWriteTone(0, 3000);
                    delay(100);
                    for (int j = 0; j != LED_COUNT; ++j)
                        leds[j] = Hsv {0, 0, 0};
                    leds.show();
                    ledcWriteTone(0, 0);
                    delay(300);
                }
                mode = 0;
                break;
            case 2:     //wave - "Chci být duha"
                ++hue;
                for (int i = 0; i != LED_COUNT; ++i)
                    leds[i] = Hsv {static_cast< uint8_t >(hue + 10 * i), 255, brightness};
                leds.show();
                delay(10);
                break;
            case 3:     //snake - "Jdu si hrát na policajty"
                leds [snakePosition] = Hsv {(hue + 10), 255, brightness};
                leds.show();
                leds.wait();
                for (int i = 0; i != LED_COUNT; ++i)
                    leds [i] = Hsv {0, 0, 0};
                snakePosition++;
                if (snakePosition == LED_COUNT){
                    snakePosition = 0;
                    hue += 10;
                }
                delay(20);
                break;
            case 4:     //disco - "Uděláme diskošku"
                randHue = random(0, 255);
                for (int i = 0; i != LED_COUNT; ++i)
                    leds[i] = Hsv {randHue, 255, brightness};
                leds.show();
                delay(200);
                break;
            case 5:     //beat - "Moje klidná mysl"
                for(int i = 0; i != LED_COUNT; ++i)
                    leds [i] = Hsv {(hue + 10), 255, beatPosition};
                leds.show();
                delay(3);
                for (int i = 0; i != LED_COUNT; ++i)
                    leds [i] = Hsv {0, 0, 0};
                if (beatPosition == 0){
                    beatCount = 1;
                    hue += 10;
                }
                if (beatPosition >= brightness)
                    beatCount = -1;
                beatPosition += beatCount;
                break;


            default:        //default = nothing lights
                for (int i = 0; i != LED_COUNT; ++i)
                    leds[i] = Hsv {0, 0, 0};
                leds.show();
                break;
        }

        if (rearLED == 1 && !rearLED_last == 1){        //turn full white rear leds
            for (int i = 0; i != LED_REAR_COUNT; ++i)
                rear [i] = Hsv {0, 0, 255};
            rear.show();
            rearLED_last = 1;
        }

        if (rearLED == 0){                              //turn off rear leds
            for (int i = 0; i != LED_REAR_COUNT; ++i)
                rear [i] = Hsv {0, 0, 0};
            rear.show();
            rearLED_last = 0;
        }

    }
    else{                                       //if battery isn't ok flash red top leds
        for (int i = 0; i != LED_COUNT; ++i)
            leds[i] = Rgb {brightness, 0, 0};
        leds.show();
        delay(300);
        for (int i = 0; i != LED_COUNT; ++i)
            leds[i] = Rgb {0, 0, 0};
        leds.show();
        delay(200);
    }
}

void setup ()
{
    analogReadResolution(11);           //setup ADC resolution to 11 bits (0 - 2047)
    analogSetAttenuation(ADC_11db);     //sets ADC attenuation to 11db (0 - 3v3)
    // pinMode(BATTERY_PIN, INPUT);
    ledcSetup(0, 3500, 8);              //setup PWM to piezo (channel, frequency, resolution)
    ledcAttachPin(16, 0);               //attach pin 16 to PWM channel 0
    Serial.begin(115200);               //begin Serial line with baudrate 115200
    WiFi.softAP(ssid, password);        //create WiFi AP
    Serial.println(WiFi.softAPIP());    //print IP addres of ESP to debug Serial line

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){       //while webserver catches /GET request, procces this function

        int paramsNr = request->params();                   //store number of parameters from user
        Serial.println(paramsNr);                           //print it to debug serial
        for(int i=0; i != paramsNr; ++i){                   //process all parameters
            AsyncWebParameter* p = request->getParam(i);    //store actual parameter to 'p' 
            if (p->name() != "cmd")                         //if name of parameter == "cmd" continue
                continue;
            String cmd = p->value();                        //parse parameter value to separate string called "cmd"
            if (cmd == "find"){                             //check cmd value and switch mode, add or substract brightness....
                mode = 1;
            }
            else if (cmd == "wave"){
                mode = 2;
            }
            else if (cmd == "snake"){
                mode = 3;
            }
            else if (cmd == "disco"){
                mode = 4;
            }
            else if (cmd == "beat"){
                mode = 5;
            }
            else if (cmd == "off"){
                clearLeds();
                mode = 0;
                clearLeds();
            }
            else if (cmd == "up"){
                brightness += STEP;
                if (brightness > 255)
                    brightness = 255;
            }
            else if (cmd == "down"){
                brightness -= STEP;
                if (brightness < 0)
                    brightness = 0;
            }

            else if (cmd == "rearon"){
                rearLED = 1;
            }

            else if (cmd == "rearoff"){
                rearLED = 0;
            }

        }
        request->send_P(200, "text/html", index_html);      //sends HTML page to user
    });

    server.begin();         //start webserver
}

void loop ()
{
    controlLeds();          //periodiccaly turns function to control all effects....LEDs, piezo
}