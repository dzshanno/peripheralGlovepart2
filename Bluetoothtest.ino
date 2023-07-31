/*

  Blue tooth sending test

  send a set of known values via bluetooth
*/

// include bluetooth library
#include <ArduinoBLE.h>

// set the UUID of the BLE service
BLEService FlexService("19B10000-E8F2-537E-4F6C-D104768A1214");

// Set the UUID of the BLE characteristics for the flex sensor values

BLEShortCharacteristic Flex1("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEShortCharacteristic Flex2("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEShortCharacteristic Flex3("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEShortCharacteristic Flex4("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEShortCharacteristic Flex5("19B10005-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
// run the setup actions

void setup()
{

    // begin BLE initialization
    if (!BLE.begin())
    {
        while (1)
            ;
    }

    // set advertised local name and service UUID:
    BLE.setLocalName("Glove");
    BLE.setAdvertisedService(FlexService);

    // add the characteristic to the service
    FlexService.addCharacteristic(Flex1);
    FlexService.addCharacteristic(Flex2);
    FlexService.addCharacteristic(Flex3);
    FlexService.addCharacteristic(Flex4);
    FlexService.addCharacteristic(Flex5);

    // add service
    BLE.addService(FlexService);

    // set the initial value for the characeristic:
    Flex1.writeValue(0);
    Flex2.writeValue(0);
    Flex3.writeValue(0);
    Flex4.writeValue(0);
    Flex5.writeValue(0);
    // start advertising
    BLE.advertise();
}

void loop()
{
    // listen for Bluetooth® Low Energy peripherals to connect:
    BLEDevice central = BLE.central();

    // if a central is connected to peripheral:
    if (central)
    {

        // while the central is still connected to peripheral:
        int step = 10;
        int a = 10;
        while (central.connected())
        {
            a = a + step;
            if (a >= 90)
            {
                step = -10;
            }
            if (a <= 20)
            {
                step = 10
            }
            sendfixedvalue(0, Flex1, "Flex1", a);
            sendfixedvalue(1, Flex2, "Flex1", a);
            sendfixedvalue(2, Flex3, "Flex1", a);
            sendfixedvalue(3, Flex4, "Flex1", a);
            sendfixedvalue(4, Flex5, "Flex1", a);
            delay(500);
        }

        // then loop back round and listen for a connection from a BLE central device
    }
}

// Other functions called by the setup and loop

void sendfixedvalue(int finger, BLEShortCharacteristic characteristic, String name, int value)
{
    // write the flex sensort value to the BLE characteristic
    characteristic.writeValue(value);
    delay(10);
}

int mapflex(int finger, int value)
{
    long flexPercent = map(value, straight[finger], fullbent[finger], 0, 100);
    return flexPercent;
}