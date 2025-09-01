#include <Arduino.h> //platformio lib

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
        int LedPin;
        const int PhotoResistorpin; //define the pin
        const int MotionSensorPin; //  define the pin
        int Motionstate; //define pin = 0


        SmartLight() //constructor __init__ in python
        //sensor pins
            : PhotoResistorpin(A1), MotionSensorPin(A1) {
            //predefine variables
            LedPin = A1;
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
            try {
                Serial.begin(9600);
                if (const int LightLevel = analogRead(PhotoResistorpin); LightLevel > 150){
                    // condition for light detection
                    Serial.print("Sensor is detecting light!");
                    return Light = true;
                }
                // if not above 150 return no light detected
                Serial.print("Sensor is not detecting light");
                return Light = false;
                // Wait for 1 second before the next loop iteration
            }
            catch (...) {
                // incase sensor fails to notify me to fix it!
                Serial.println("Light Sensor could not be detected");
                return LightSensorStateOn = false; //flag for deciding if smartlight should proceed
            }
            return Light = false;
        }

          bool MotionSensor()
          /*
BEGIN MotionSensor
  \\ process to perform motion check
  READ Motion from sensor

  IF Motion THEN
      RETURN  Motion = True
      write "Motion detected!"
  ELSE
      RETURN  Motion = False
      write "No motion detected"
  ENDIF
END MotionSensor
*/
        {
            try {
                Motionstate = digitalRead(MotionSensorPin);         // Read the state of the PIR sensor
                if (Motionstate == HIGH) {                 // If the PIR sensor detects movement (state = HIGH)
                    Serial.print("Motion is detecting motion!");
                    return Motion = true; //flag for deciding if light should be on/off
                }
                return Motion = false; //flag for deciding if light should be on/off
                Serial.println("Monitoring...");
            } catch (...) { //incase sensor fails to notify me to fix it!
                Serial.println("Motion Sensor could not be detected");
                return MotionSensorStateOn = false; //flag for deciding if smartlight should proceed
            }
            return Motion = false; //flag for deciding if light should be on/off
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
            pinMode(LedPin, OUTPUT); //led location (readjust if needed)
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
BEGIN loop
    IF StartSmartLight = True THEN \\ only start if all sensors work
       IF MOTION AND LIGHT = True THEN
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
            if (StartSmartLight == true) { //only start if sensors work
                if (Light == true && Motion == true ) { //check if both sensors are detecting
                    //turn light on if they are
                    Serial.println("LED light on!");
                    digitalWrite(LedPin, HIGH);
                }
                else { //turn light off if not
                    Serial.println("LED light off!");
                    digitalWrite(LedPin, LOW);
                }
            }
            delay(1500); // 1.5 second delay
        }
    };
};

SmartLight::SmartLight SmartLightSystem;
//outside of namespace for same method
//for compiling method
void setup(){SmartLightSystem.setup();};
void loop(){SmartLightSystem.loop();};






