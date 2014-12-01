#include "serial.h"
#include "core.h"
#include <QCoreApplication>

QT_USE_NAMESPACE

unsigned char type;
unsigned char size;
unsigned char dataIndex;
QByteArray* data;

enum CurrentStep {
    getType,
    getSize,
    getData
};

CurrentStep state;

Serial::Serial() {
    serial = new QSerialPort(Q_NULLPTR);
    data = new QByteArray();
}

void Serial::open_serial(string port, int baud) {
    serial->setPortName(QString::fromStdString(port));
    serial->setBaudRate(baud);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::UnknownStopBits );
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    QObject::connect(serial,&QSerialPort::readyRead,[this](){serial_read();});
    printf("connected to serial port\n");
}

void Serial::serial_write(const Msg_ptr& msg) {
    QByteArray* data = new QByteArray();
    data->append((char)msg->get_type());
    data->append((char)msg->get_data_size());
    data->append(msg->get_data());
    serial->write(*data);
}

void Serial::serial_read(void) {
    unsigned char buffer[255];
    qint64 amount;
    amount = serial->read((char*)&buffer, 255);

    if (amount == -1)
        printf("Error reading past stream! \n");
    for (int i = 0; i < amount; i++) {
        read_byte(buffer[i]);
    }

    /*string mojs = "";
    mojs += char(55);
    mojs += char(55);
    core->process_new_msg(Msg_ptr(new Message(0xE3,mojs)));*/
}

void Serial::read_byte(unsigned char byte) {
    switch(state) {
        case getType:
            type = byte;
            state = getSize;
            break;
        case getSize:
            size = byte;
            if (size != 0) {
                data->clear();
                dataIndex = 0;
                state = getData;
            }
            else {
                core->process_new_msg(Msg_ptr(new Message(type,data)));
                state = getType;
            }
            break;
        case getData:
            data->insert(dataIndex, byte);
            dataIndex++;
            if (dataIndex == size) {
                core->process_new_msg(Msg_ptr(new Message(type,data)));
                state = getType;
            }
            break;
    }
}

void Serial::close_serial(void) {
    serial->close();
}
