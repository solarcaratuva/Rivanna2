#include <mbed.h>
#include <rtos.h>
#include "pindef.h"
#include "Printing.h"
#include "PowerAuxCANInterface.h"
#include "PowerAuxBPSCANInterface.h"

#define TESTING     // only defined if using test functions
// #define DEBUGGING   // only define if debugging

#define MAIN_LOOP_PERIOD 1s
#define CAN_PERIOD 1s

PowerAuxCANInterface vehicle_can_interface(MAIN_CAN_RX, MAIN_CAN_TX, MAIN_CAN_STBY);
PowerAuxBPSCANInterface bps_can_interface(BMS_CAN1_RX, BMS_CAN1_TX, BMS_CAN1_STBY);

DigitalOut breakLights(BRAKE_LIGHT_EN);
DigitalOut headlights(DRL_EN);
DigitalOut horn(HORN_EN);
// DigitalOut ignition(IGNITION);

bool hazardsOn, leftSignal, rightSignal;
DigitalOut leftTurnSignal(LEFT_TURN_EN);
DigitalOut rightTurnSignal(RIGHT_TURN_EN);


int main() {
    // device.set_baud(38400);

#ifdef TESTING
    PRINT("start main() \r\n");
#endif //TESTING

    while(1) {
        #ifdef TESTING
            PRINT("main thread loop \r\n");
        #endif //TESTING

        PowerAuxExampleStruct a(5, 6, 7, 8);
        vehicle_can_interface.send(&a);

        if (hazardsOn) {
            if (leftTurnSignal && rightTurnSignal) {
                leftTurnSignal = false;
                rightTurnSignal = false;
            } else {
                leftTurnSignal = true;
                rightTurnSignal = true;
            }
        } else {
            leftTurnSignal = false;
            rightTurnSignal = false;
        }

        if (leftSignal) {
            if (leftTurnSignal) {
                leftTurnSignal = false;
            } else {
                leftTurnSignal = true;
            }
        } else {
            leftTurnSignal = false;
        }

        if (rightSignal) {
            if (rightTurnSignal) {
                rightTurnSignal = false;
            } else {
                rightTurnSignal = true;
            }
        } else {
            rightTurnSignal = false;
        }

        ThisThread::sleep_for(MAIN_LOOP_PERIOD);
    }
}

void PowerAuxCANInterface::handle(ECUPowerAuxCommands *can_struct)
{
    /*
    For brake_lights, headlights, horn, ignition, and battery_contact, the appropriate pin 
    should be set based on each field. For example, the HORN_EN pin should be set based on \
    the horn field of the ECUPowerAuxCommands struct.
    */

   breakLights = can_struct->brake_lights;
   headlights = can_struct->headlights;
   horn = can_struct->horn;

   leftSignal = can_struct->left_turn_signal;
   rightSignal = can_struct->right_turn_signal;
   hazardsOn = can_struct->hazards;

//    igntion = can_struct->ignition;
//    battery__contact = can_struct->battery_contact;

}

void PowerAuxBPSCANInterface::handle(PackInformation *can_struct)
{
    PRINT("Received PackInformation struct: pack_voltage=%u\n", can_struct->pack_voltage);
}

void PowerAuxBPSCANInterface::handle(CellVoltage *can_struct)
{
    PRINT("Received CellVoltage struct: low_cell_voltage=%u\n", can_struct->low_cell_voltage);
}

void PowerAuxBPSCANInterface::handle(CellTemperature *can_struct)
{
    PRINT("Received CellTemperature struct: low_temperature=%u\n", can_struct->low_temperature);
}
