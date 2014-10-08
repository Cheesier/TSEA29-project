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
  ui->pushButton_scan->setEnabled(false);
  ui->pushButton_scan->setText("scan..");
}

void Gui::bt_connecting(){
  ui->pushButton_connect->setEnabled(false);
  ui->label_bt_status->setText("connecting..");
  ui->pushButton_scan->setEnabled(true);
  ui->pushButton_scan->setText("cancel");
}

void Gui::bt_connected(){
  ui->pushButton_connect->setEnabled(true);
  ui->pushButton_connect->setText("disconnect");
  ui->label_bt_status->setText("connected");
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
