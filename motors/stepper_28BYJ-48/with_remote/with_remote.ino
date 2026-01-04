//Adapted to work with IRremote V4.5
//2026.01.04

#include "Stepper.h"
#include "IRremote.h"

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int IR_RECEIVE_PIN = 12; // Signal Pin of IR receiver to Arduino Digital Pin 12

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
decode_results results;

uint32_t last_decodedRawData = 0;//variable uses to store the last decodedRawData

void setup()
{
  Serial.begin(115200);
  delay(5000);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.println("Everything set up....");
  Serial.println("Press VOL+ or VOL- to continue...");
}

void loop()
{ 
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    Serial.println("Receive irrecv: ");
    Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    // Check if it is a repeat IR code
    if (IrReceiver.decodedIRData.flags)
    {
      //set the current decodedRawData to the last decodedRawData
      IrReceiver.decodedIRData.decodedRawData = last_decodedRawData;
    }
    switch (IrReceiver.decodedIRData.decodedRawData)
    {

      case 0xB946FF00: // VOL+ button pressed
        Serial.println("VOL+ button pressed");
        small_stepper.setSpeed(500); //Max seems to be 500
        Steps2Take  =  -2048;  // Rotate CW
        small_stepper.step(Steps2Take);
        delay(2000);
        break;

      case 0xEA15FF00: // VOL- button pressed
        Serial.println("VOL- button pressed");
        small_stepper.setSpeed(500);
        Steps2Take  =  2048;  // Rotate CCW
        small_stepper.step(Steps2Take);
        delay(2000);
        break;

    }
    //store the last decodedRawData
    last_decodedRawData = IrReceiver.decodedIRData.decodedRawData;
    Serial.println("Press VOL+ or VOL- to continue...");
    IrReceiver.resume(); // receive the next value
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

}/* --end main loop -- */
