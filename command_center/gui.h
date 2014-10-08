#ifndef GUI_H
#define GUI_H

#define QLABEL_STYLE_DISCONNECTED "QLabel{color:red;}"
#define QLABEL_STYLE_CONNECTING "QLabel{color:orange;}"
#define QLABEL_STYLE_CONNECTED "QLabel{color:green;}"

#include <memory>

#include <QMainWindow>

#include "glob.h"
#include "core.h"

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
  void on_pushButton_forward_pressed();
  void on_pushButton_backward_pressed();
  void on_pushButton_left_pressed();
  void on_pushButton_right_pressed();
  void on_pushButton_connect_clicked();

  void on_pushButton_scan_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_send_clicked();

private:
  //data
  Ui::Gui *ui;
};

#endif // GUI_H
