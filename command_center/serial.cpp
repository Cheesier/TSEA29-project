#include "serial.h"
#include "core.h"

QSerialPort *serial;

unsigned char type;
unsigned char size;
unsigned char index;
string data;

enum CurrentStep {
    getType,
    getSize,
    getData
};

CurrentStep state;

void Serial::init_serial(void) {
    serial = new QSerialPort(Q_NULLPTR);
}

void Serial::open_serial(string port, int baud) {
    serial->setPortName(QString::fromStdString(port));
    serial->setBaudRate(baud);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::UnknownStopBits );
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    //QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    QObject::connect(serial,&QSerialPort::readyRead,[this](){serial_read();});
    //QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(serial_read()));

    printf("connected to serial port\n");
}

void Serial::serial_write(const Msg_ptr& msg) {
    QByteArray* data = new QByteArray();
    data->append((char)msg->get_type());
    data->append((char)msg->get_data_size());
    data->append((char*)msg->get_data().data(), msg->get_data_size());
    serial->write(*data);
}

void Serial::serial_read(void) {
    unsigned char buffer[255];
    qint64 amount;
    amount = serial->read((char*)&buffer, 255);

    for (int i = 0; i < amount; i++) {
        read_byte(buffer[i]);
    }

    /*string mojs = "";
    mojs += char(55);
    mojs += char(55);
    core->process_new_msg(Msg_ptr(new Message(0xE3,mojs)));*/
}

void Serial::read_byte(unsigned char byte) {
    //printf("got byte: %x", byte);
    switch(state) {
        case getType:
            type = byte;
            state = getSize;
            break;
        case getSize:
            size = byte;
            if (size != 0) {
                data = "";
                index = 0;
                state = getData;
            }
            else {
                printf("message: %x%x\n", type, size);
                core->process_new_msg(Msg_ptr(new Message(type,data)));
                state = getType;
            }
            break;
        case getData:
            data.append((char*)&byte);
            index++;
            if (index == size) {
                //printf("message: %x%x");
                //printf("message sent, data: %s", (char*)&data);
                core->process_new_msg(Msg_ptr(new Message(type,data)));
                state = getType;
            }
            break;
    }
}

void Serial::close_serial(void) {
    serial->close();
}
