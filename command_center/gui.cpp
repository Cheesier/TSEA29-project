#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
  QMainWindow(parent){
  //ui.reset(new Ui::Gui);
  ui = new Ui::Gui;
  ui->setupUi(this);
  connect(this, &Gui::console_log, this, &Gui::console_log_);
  connect(this, &Gui::pb_update, this, &Gui::pb_update_);
  connect(this, &Gui::bt_reset, this, &Gui::bt_reset_);
  connect(this, &Gui::bt_connecting, this, &Gui::bt_connecting_);
  connect(this, &Gui::bt_connected, this, &Gui::bt_connected_);
}

Gui::~Gui(){
  printf("destroying gui..\n");
  delete ui;
}


// ------------- gui --------------

void Gui::console_log_(const QString &data){
  ui->plainTextEdit_log->appendPlainText(data);
}

// ----------- playback ------------

#define PB_STRING_LIVE "[LIVE]"
#define PB_STRING_PAUSED "[PAUSED]"

void Gui::pb_update_(const unsigned &total_msgs, const unsigned &current_msg, const unsigned& status){
  ui->label_pb_total->setText(QString::number(total_msgs));
  ui->label_pb_current->setText(QString::number(current_msg));
  ui->horizontalSlider_pb->setMaximum(total_msgs);
  ui->horizontalSlider_pb->setValue(current_msg);
  QString status_string;
  switch(status){
      case Core::PB_PAUSED:
        status_string = PB_STRING_PAUSED;
        break;
      case Core::PB_LIVE:
        status_string = PB_STRING_LIVE;
        break;
  }
  ui->label_pb_status->setText(status_string);
}

// ------------- bt ----------------

void Gui::bt_reset_(){
  ui->pushButton_connect->setEnabled(true);
  ui->pushButton_connect->setText("Connect");
  ui->label_bt_status->setText("Not connected");
  ui->label_bt_status->setStyleSheet(QLABEL_STYLE_DISCONNECTED);
  ui->pushButton_scan->setEnabled(false);
  ui->pushButton_scan->setText("Scan..");
}

void Gui::bt_connecting_(){
  ui->pushButton_connect->setEnabled(false);
  ui->label_bt_status->setText("Connecting..");
  ui->label_bt_status->setStyleSheet(QLABEL_STYLE_CONNECTING);
  ui->pushButton_scan->setEnabled(true);
  ui->pushButton_scan->setText("Cancel");
}

void Gui::bt_connected_(){
  ui->pushButton_connect->setEnabled(true);
  ui->pushButton_connect->setText("Disconnect");
  ui->label_bt_status->setText("Connected");
  ui->label_bt_status->setStyleSheet(QLABEL_STYLE_CONNECTED);
  ui->pushButton_scan->setEnabled(false);
  ui->pushButton_scan->setText("Scan..");
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
  const unsigned& type = ui->lineEdit_type->text().toInt();
  const QString& payload_ = ui->lineEdit_payload->text();
  const string& payload = payload_.toStdString();
  core->custom_msg(type,payload);
}

void Gui::on_pushButton_pb_rewind_clicked(){
  core->pb_rewind();
}

void Gui::on_pushButton_pb_play_clicked() {
  //later play later, just pause for now
  core->pb_pause();
}

void Gui::on_pushButton_pb_next_clicked(){
  core->pb_play_next();
}

void Gui::on_pushButton_pb_live_clicked(){
  core->pb_play_all();
}

void Gui::on_horizontalSlider_pb_sliderReleased(){
  const unsigned& idx = ui->horizontalSlider_pb->value();
  core->pb_goto(idx);
}

void Gui::on_actionReset_triggered(){
  core->pb_reset();
}

void Gui::on_actionSave_triggered(){
  const QString& file_name = QFileDialog::getSaveFileName(this,"Save file","", "All files (*)");
  core->data_save(file_name.toStdString());
}

void Gui::on_actionOpen_triggered(){
  const QString& file_name = QFileDialog::getOpenFileName(this,"Open file", "","All files (*)");
  core->data_open(file_name.toStdString());
}

void Gui::on_lineEdit_p_value_returnPressed(){
  const double& val = ui->lineEdit_p_value->text().toDouble();
  ui->lineEdit_p_value->setText(QString::number(val));
  core->set_p(val);
}

void Gui::on_lineEdit_d_value_returnPressed(){
  const double& val = ui->lineEdit_d_value->text().toDouble();
  ui->lineEdit_d_value->setText(QString::number(val));
  core->set_d(val);
}

void Gui::on_pushButton_forward_left_pressed(){
  core->go_forward_left();
}

void Gui::on_pushButton_forward_right_pressed(){
  core->go_forward_right();
}
