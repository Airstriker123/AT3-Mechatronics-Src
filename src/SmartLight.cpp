#include <any>
#include <Arduino.h>
#include <print.h>

namespace SmartLight
{
    class SmartLight
    {

    public:

        //class public variables to declare type
        bool LEDLight;
        double LightLevel;
        bool Light;
        bool Motion;
        bool MotionSensorStateOn;
        bool LightSensorStateOn;
        bool StartSmartLight;
        const int PhotoResistorpin; //define the pin
        const int MotionSensorPin; //  define the pin
        int Motionstate; //define pin = 0


        SmartLight() //constructor
        {
            //predefine variables
            StartSmartLight = false;
            MotionSensorStateOn = true;
            LightSensorStateOn = true;
            LEDLight = false;
            LightLevel = 0.0;
            Light = false;
            Motion = false;
            Motionstate = 0;
            // Declare and initialize the state variable
        }


        bool LightSensor()
        /*

*/
        {
            try {
                Serial.begin(9600);
                if (const int LightLevel = analogRead(PhotoResistorpin); LightLevel > 150){
                    // condition for light detection
                    return Light = true;
                    Serial.print("Sensor is detecting light!");
                }
                // if not above 150 return no light detected
                return Light = false;
                Serial.print("Sensor is not detecting light");
                // Wait for 1 second before the next loop iteration
                delay(1000);
            }
            catch (...) {
                // incase sensor fails to notify me to fix it!
                Serial.println("Light Sensor could not be detected");
                return LightSensorStateOn = false;
            }
            return Light = false;
        }

          bool MotionSensor()
        /*

         */
        {
            try {
                delay(1000);
                Motionstate = digitalRead(MotionSensorPin);         // Read the state of the PIR sensor
                if (Motionstate == HIGH) {                 // If the PIR sensor detects movement (state = HIGH)
                    return Motion = true;
                    Serial.print("Motion is detecting motion!");
                }
                return Motion = false;
                Serial.println("Monitoring...");
            } catch (...) { //incase sensor fails to notify me to fix it!
                return MotionSensorStateOn = false;
                Serial.println("Motion Sensor could not be detected");
            }
            return Motion = false;
        }

         bool setup()
            /*

             */
        {
            pinMode(MotionSensorPin, INPUT);  // Set the PIR pin as an input
            Serial.begin(9600);
            Serial.println("initializing SmartLight setup!");

            if (MotionSensorStateOn == true) {
                Serial.println("Motion Sensor is on!");
            }
            else {
                Serial.println("Motion Sensor is off");
            }
            if (LightSensorStateOn == true) {
                Serial.println("Light Sensor is on!");
            }
            else {
                Serial.println("Light Sensor is off");
            }
            if (LightSensorStateOn == true && MotionSensorStateOn == true) {
                Serial.println("All sensors work!");
                Serial.println("Starting smartlight!");
                return StartSmartLight = true;
            }
        }



        void loop()
        /*
\\ process to perform real time checks if any change in environment
BRGIN loop
    IF StartSmartLight = True THEN \\ only start if all sensors work
       IF MOTION AND LIGHT = True THEN
          write " LED light on!"
          SmartLight = True
          LEDLight = On
       ELSE
           write "LED light off"
           SmartLight = False
           LEDLight = off
       ENDIF
    ENDIF
END Loop
*/
        {
            // write your code here
        }
    };
};






