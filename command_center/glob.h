#ifndef GLOB_H
#define GLOB_H


//used for testing -- converts char ('0' == 48 --> 0 ) values for msg size and type
//disable this when testing with the actual device
//#define TEXTMODE

//#define REMOTE_DEVICE_ADDRESS "BC:F5:AC:78:24:21" //Oscars
#define REMOTE_DEVICE_ADDRESS "2C:54:CF:76:02:E1" //Oskars
//#define REMOTE_DEVICE_ADDRESS "00:06:66:03:16:C0" //Robot
#define REMOTE_SERVICE_UUID "00001101-0000-1000-8000-00805f9b34fb"
//#define REMOTE_SERVICE_UUID "0003"

//#define BT_ACTIVE
#define SERIAL_ACTIVE

#define SERIAL_PORT "COM4"
#define BAUD_RATE 115200

#ifdef __linux__
#define LINUX
#endif

using namespace std;

#endif // GLOB_H
