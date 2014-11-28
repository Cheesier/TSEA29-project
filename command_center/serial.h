#ifndef SERIAL_H
#define SERIAL_H

#include <QSerialPort>
#include <string>
#include "message.h"
#include <mutex>


class Serial : public QObject {
public:
    Serial();
    void open_serial(string port, int baud);
    void serial_write(const Msg_ptr& msg);
    void close_serial();

private slots:
    void serial_read(void);
    void handleError(QSerialPort::SerialPortError serialPortError);
private:
    void read_byte(unsigned char byte);


    QSerialPort *serial;
    QByteArray readData;
    mutex read_lock;
};

#endif // SERIAL_H
