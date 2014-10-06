#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>

#include <QMainWindow>
#include <QtBluetooth>

#include "glob.h"
#include "core.h"
#include "message.h"

namespace Ui {
class Gui;
}

class Gui : public QMainWindow {
  Q_OBJECT

public:
  explicit Gui(QWidget *parent = 0);
  ~Gui();

  void bt_close_socket();
  void bt_reset_socket();
  void bt_connect(const string& device);
  void bt_send(const Msg_ptr& msg);

private slots:
  void bt_new_service(const QBluetoothServiceInfo&);

  void bt_read();

  void on_pushButton_forward_pressed();
  void on_pushButton_backward_pressed();
  void on_pushButton_left_pressed();
  void on_pushButton_right_pressed();
  void on_pushButton_connect_clicked();

private:
  void enable_bt_buttons();

  void bt_connect(const QBluetoothServiceInfo& service);
  void bt_handle_connect();
  void bt_handle_avaible();
  void bt_write();
  bool bt_is_avaible();

  //data
  Ui::Gui *ui;

  //bluetooth data
  QBluetoothLocalDevice bt_dev;
  shared_ptr<QBluetoothServiceDiscoveryAgent> bt_service_discovery;
  shared_ptr<QBluetoothSocket> bt_socket;

  deque<Msg_ptr> write_mgs;
  bool bt_is_writing = false;
  mutex bt_read_mtx, bt_write_mtx;
};

#endif // GUI_H
