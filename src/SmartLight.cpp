#include <Arduino.h> //platformio needs this headerfile (for setup and loop pre functions)

namespace SmartLight
{
    class SmartLight
    {

    public:

        //class public variables to declare type
        // booleon values which will be determined by functions which will return bool/float
        bool LEDLight;
        double LightLevel;
        bool Light;
        bool LightSensorStateOn;
        bool StartSmartLight;
        // pins constant soo they cannot be changed
        const int LedPin;
        const int PhotoResistorPin;


        SmartLight() // constructor -> __init__ in python to assign values to class + pin and default bool assign
           : PhotoResistorPin(A2),
             LedPin(D7)
        {
            // starter values each time class is called (for safety)
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
       write "Sensor is detecting light!"
    ELSE
       RETURN  Light = False
       write "No light detected"
    ENDIF
END LightSensor
*/
        {
            LightLevel = analogRead(PhotoResistorPin); //get light level from pin reading
            if (LightLevel > 150)
            {
                // let light = true if reading above 150
                Serial.println("Sensor is detecting light!");
                return Light = true;
            }
            //otherwise return false if light < 150
                Serial.println("No light detected");
                return Light = false;
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
         RETURN  StartSmartLight = True
         write "Smart Light is now active!"
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


            if (LightSensorStateOn)
                // check if sensor is on and then continue with loop (for debugging purposes)
            {
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
          write " LED light on!"
          LEDLight = On
       ELSE
           write "LED light off"
           LEDLight = off
       ENDIF
    ENDIF
END Loop
*/
        {
            if (StartSmartLight)
            {
                // get light from returned booleon from LightSensor function
                Light = LightSensor();

                if (Light == false)
                { //if return false (no light detection turn led on)
                    Serial.println("LED ON");
                    digitalWrite(LedPin, HIGH);
                } else
                { //otherwise
                    Serial.println("LED OFF");
                    digitalWrite(LedPin, LOW);
                }
            }
            delay(1500);
        }
    };
};

SmartLight::SmartLight SmartLightSystem; //create a new instance named SmartLightSystem from class SmartLight to use the namespace
//outside of namespace for same method
//for compiling method
void setup() {SmartLightSystem.setup();}; //get class method setup (execute once until reset)
void loop() {SmartLightSystem.loop();}; //get class method loop (repeat each millisecond)