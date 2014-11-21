#ifndef SERIAL_H
#define SERIAL_H

#include <QSerialPort>
#include <string>
#include "message.h"

class Serial {
public:
    void init_serial(void);
    void open_serial(string port, int baud);
    void serial_write(const Msg_ptr& msg);
    void serial_read(void);
    void close_serial();
    void read_byte(unsigned char byte);
};

#endif // SERIAL_H
