#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::Gui){

  ui->setupUi(this);
  //  if(bt_is_avaible()) bt_handle_avaible();
}

Gui::~Gui(){
  printf("destroying gui..\n");
  delete ui;
}


// ------------- gui --------------

void Gui::bt_reset(){
  ui->pushButton_connect->setEnabled(true);
  ui->pushButton_connect->setText("connect");
  ui->label_bt_status->setText("not connected");
  ui->label_bt_status->setStyleSheet(QLABEL_STYLE_DISCONNECTED);
  ui->pushButton_scan->setEnabled(false);
  ui->pushButton_scan->setText("scan..");
}

void Gui::bt_connecting(){
  ui->pushButton_connect->setEnabled(false);
  ui->label_bt_status->setText("connecting..");
  ui->label_bt_status->setStyleSheet(QLABEL_STYLE_CONNECTING);
  ui->pushButton_scan->setEnabled(true);
  ui->pushButton_scan->setText("cancel");
}

void Gui::bt_connected(){
  ui->pushButton_connect->setEnabled(true);
  ui->pushButton_connect->setText("disconnect");
  ui->label_bt_status->setText("connected");
  ui->label_bt_status->setStyleSheet(QLABEL_STYLE_CONNECTED);
  ui->pushButton_scan->setEnabled(false);
  ui->pushButton_scan->setText("scan..");
}

//  -------------- slots
void Gui::on_pushButton_forward_pressed(){
  core->go_forward();
}

void Gui::on_pushButton_backward_pressed(){
  core->go_backward();
}

void Gui::on_pushButton_left_pressed(){
  core->turn_left();
}

void Gui::on_pushButton_right_pressed(){
  core->turn_right();
}

void Gui::on_pushButton_connect_clicked(){
  if(!core->bt_is_connected())
    core->bt_connect();
  else core->bt_disconnect();
}

void Gui::on_pushButton_scan_clicked(){
    core->bt_disconnect();
}

void Gui::on_pushButton_clear_clicked(){
  ui->lineEdit_type->clear();
  ui->lineEdit_payload->clear();
}

void Gui::on_pushButton_send_clicked(){
  const QString& type_ = ui->lineEdit_type->text();
  const QString& payload_ = ui->lineEdit_payload->text();
  const unsigned& type = type_.toInt();
  const string& payload = payload_.toStdString();
  core->custom_msg(type,payload);
}
