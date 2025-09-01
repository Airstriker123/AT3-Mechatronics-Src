#include <any>
#include <Arduino.h>
#include <print.h>

namespace SmartLight {
    class SmartLight
    {

    public:

        //class public variables to declare type
        bool LEDLight;
        double LightLevel;
        bool Light;
        bool Motion;

        SmartLight() //constructor
        {
            //predefine variables
            LEDLight = false;
            LightLevel = 0.0;
            Light = false;
            Motion = false;
        }


         bool LightSensor()
        /*
BEGIN LightSensor
    \\ process to request light from sensor and determine if light is on or off
    READ LightLevel FROM sensor  \\ sensor will return light intensity

    \\ determine if to mark as light detected or not to avoid false positive
    IF LightLevel > 150 THEN
       Light = True
       write "Sensor is detecting light!"
    ELSE
       Light = False
       write "No light detected"
    ENDIF

    RETURN Light
END PhotoResistor
*/
        {
            return false;

        }

         bool MotionSensor()
        /*
BEGIN MotionSensor
    \\ process to perform motion check
    READ Motion from sensor

    IF Motion THEN
        Motion = True
        write "Motion detected!"
    ELSE
        Motion = False
        write "No motion detected"
    ENDIF

    RETURN Motion
END MotionSensor

         */

        {
            return false;
        }

        static void setup()
        {
            // write your initialization code here

            /*
BEGIN setup
     \\ safety checks to check if product sensors are working
     READ MotionSensorStatus FROM sensor
     READ LightSensorStatus FROM sensor

     IF MotionSensorStatus = True THEN
         Sensor1 = True
         write "Motion sensor detected!"
     ELSE
         write "Motion sensor not detected!"
     ENDIF

     IF LightSensorStatus = True THEN
         Sensor2 = True
         write "Light sensor detected!"
     ELSE
         write "Light sensor not detected!"
     ENDIF

     IF Sensor1 AND Sensor2 = True THEN
         StartSmartLight = True
         write "Smart Light is now active!"
     ENDIF

     RETURN StartSmartLight
END setup
             */
            Serial.println("initializing SmartLight setup!");
            try //prevent any crash if error occurs in selection
            {
                if (MotionSensor() == true)
                    Serial.println("Motion Sensor is on!");
                else
                    Serial.println("Motion Sensor is off");
            }
            catch (...) //catch any error
            {
                Serial.println("An error occured!");
                Serial.println("Motion Sensor NOT detected ");
            }
        }

       static void loop()
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
    private:
        // private very secret scary data here :0
    };
};






