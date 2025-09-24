#include <Arduino.h> //platformio needs this headerfile (for setup and loop pre functions)

namespace SmartLight
{
    class SmartLight
    {

    public:

        //class public variables to declare type
        bool LEDLight;
        double LightLevel;
        bool Light;
        bool LightSensorStateOn;
        bool StartSmartLight;
        int LedPin;
        const int PhotoResistorPin;


        SmartLight()
           : PhotoResistorPin(A2)
        {
            LedPin = D7;
            StartSmartLight = false;
            LightSensorStateOn = true;
            LEDLight = false;
            LightLevel = 0.0;
            Light = false;
        }



        bool LightSensor()
        /*
BEGIN LightSensor
    \\ process to request light from sensor and determine if light is on or off
    READ LightLevel FROM sensor  \\ sensor will return light intensity

    \\ determine if to mark as light detected or not to avoid false positive
    IF LightLevel > 150 THEN
       RETURN  Light = True
       Display "Sensor is detecting light!"
    ELSE
       RETURN  Light = False
       Display "No light detected"
    ENDIF
END LightSensor
*/
        {
            LightLevel = analogRead(PhotoResistorPin);
            if (LightLevel > 150) {
                Serial.println("Sensor is detecting light!");
                return Light = true;
            }
            else {
                Serial.println("No light detected");
                return Light = false;
            }
        }


         bool setup()
        /*
\\ Ardunio setup process only executes once
BEGIN setup
     \\ safety checks to check if product sensors are working
     READ MotionSensorStatus FROM sensor
     READ LightSensorStatus FROM sensor

     IF MotionSensorStatus = True THEN
         Sensor1 = True
         Display "Motion sensor detected!"
     ELSE
         Display "Motion sensor not detected!"
     ENDIF

     IF LightSensorStatus = True THEN
         Sensor2 = True
         Display "Light sensor detected!"
     ELSE
         Display "Light sensor not detected!"
     ENDIF

     IF Sensor1 AND Sensor2 = True THEN
         RETURN  StartSmartLight = True
         Display "Smart Light is now active!"
     ENDIF
END setup
*/
        {
            // Serial must start first
            Serial.begin(9600);
            delay(500); // give serial time to initialize
            Serial.println("Initializing SmartLight setup!");

            pinMode(LedPin, OUTPUT);

            // Initial sensor checks
            LightSensor();


            if (LightSensorStateOn) {
                Serial.println("Light Sensor is ON!");
                return StartSmartLight = true;
            }
            Serial.println("Light Sensor is OFF");
            return StartSmartLight = false;
        }

        void loop()
        /*
\\ process to perform real time checks if any change in environment
BEGIN loop
    IF StartSmartLight = True THEN \\ only start if all sensors work
       IF Motion AND Light = True THEN
          Display " LED light on!"
          LEDLight = On
       ELSE
           Display "LED light off"
           LEDLight = off
       ENDIF
    ENDIF
END Loop
*/
        {
            if (StartSmartLight) {
                Light = LightSensor();

                if (Light == false) {
                    Serial.println("LED ON");
                    digitalDisplay(LedPin, HIGH);
                } else {
                    Serial.println("LED OFF");
                    digitalDisplay(LedPin, LOW);
                }
            }
            delay(1500);
        }
    };
};

SmartLight::SmartLight SmartLightSystem;
//outside of namespace for same method
//for compiling method
void setup() {SmartLightSystem.setup();};
void loop() {SmartLightSystem.loop();};



/*
LEDLight = off
LightLevel = 0
Light = False
Motion = False

BEGIN PhotoResistor
    \\ process to request light from sensor and determine if light is on or off
    LightLevel = READ LightLevel FROM sensor  \\ sensor will return light intensity

    \\ determine if to mark as light detected or not to avoid false positive
    IF LightLevel > 150 THEN
       RETURN  Light = True
       Display "Sensor is detecting light!"
    ELSE
       RETURN  Light = False
       Display "No light detected"
    ENDIF
END PhotoResistor


BEGIN MotionSensor
    \\ process to perform motion check
    READ Motion from sensor

    IF Motion THEN
        RETURN  Motion = True
        Display "Motion detected!"
    ELSE
        RETURN  Motion = False
        Display "No motion detected"
    ENDIF
END MotionSensor

\\ Ardunio setup process only executes once
BEGIN setup
     \\ safety checks to check if product sensors are working
     MotionSensorStatus = get from sensor
     LightSensorStatus = get from sensor 

     IF MotionSensorStatus = True THEN
         Sensor1 = True
         Display "Motion sensor detected!"
     ELSE
         Display "Motion sensor not detected!"
     ENDIF

     IF LightSensorStatus = True THEN
         Sensor2 = True
         Display "Light sensor detected!"
     ELSE
         Display "Light sensor not detected!"
     ENDIF

     IF Sensor1 AND Sensor2 = True THEN
         Display "Smart Light is now active!"
RETURN  StartSmartLight = True	
     ENDIF
END setup




\\ process to perform real time checks if any change in environment
BEGIN loop
    IF StartSmartLight = True THEN \\ only start if all sensors work
       IF MOTION AND LIGHT = True THEN
          Display " LED light on!"
          LEDLight = On
       ELSE
           Display "LED light off"
           LEDLight = off
       ENDIF
    ENDIF
END Loop





 */