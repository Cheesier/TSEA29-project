/*
 * interface för seriell port
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <QSerialPort>
#include <string>
#include <mutex>
#include <deque>

#include "message.h"

class Serial : public QObject {
public:
  Serial();
  // öppna/stäng
  void open_serial(string port, int baud);
  void close_serial();


  void send(const Msg_ptr& msg);

private slots:
  void serial_read(void);
  void handleError(QSerialPort::SerialPortError serialPortError);
private:
  void read_byte(unsigned char byte);

  void do_write();

  bool is_writing = false;
  //meddelandekön
  deque<Msg_ptr> write_mgs;
  mutex write_mtx;


  unique_ptr<QSerialPort> serial;
  QByteArray readData;
};

#endif // SERIAL_H
