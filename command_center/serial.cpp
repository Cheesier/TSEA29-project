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
  serial = unique_ptr<QSerialPort>(new QSerialPort());
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

  QObject::connect(serial.get(),&QSerialPort::readyRead,[this](){serial_read();});
  printf("connected to serial port\n");
}

void Serial::send(const Msg_ptr& msg){
  unique_lock<mutex> lck(write_mtx);
  write_mgs.emplace_back(msg);
  lck.unlock();
  do_write();
}

void Serial::do_write(){
  unique_lock<mutex> lck(write_mtx);
  if(write_mgs.empty() || is_writing) return;
  is_writing = true;
  Msg_ptr msg = write_mgs.front();
  write_mgs.pop_front();
  lck.unlock();
  //std::thread t([this,msg](){
    serial->write(msg->get_raw_data(), msg->get_raw_data_size());
    unique_lock<mutex> lck2(write_mtx);
    is_writing = false;
    lck2.unlock();
    do_write();
  //});
  //t.detach();
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
      core->process_new_msg(Msg_ptr(new Message(type,string())));
      state = getType;
    }
    break;
  case getData:
    data->insert(dataIndex, byte);
    dataIndex++;
    if (dataIndex == size) {
      core->process_new_msg(Msg_ptr(new Message(type,string(data->data(),size))));
      state = getType;
    }
    break;
  }
}

void Serial::close_serial(void) {
  serial->close();
}
