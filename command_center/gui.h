#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>

#include <QMainWindow>

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

  void bt_reset();
  void bt_connecting();
  void bt_connected();

private slots:
/*  void bt_new_service(const QBluetoothServiceInfo&);

  void bt_read();
*/
  void on_pushButton_forward_pressed();
  void on_pushButton_backward_pressed();
  void on_pushButton_left_pressed();
  void on_pushButton_right_pressed();
  void on_pushButton_connect_clicked();

  void on_pushButton_scan_clicked();

private:
  //data
  Ui::Gui *ui;
};

#endif // GUI_H
