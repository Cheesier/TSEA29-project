#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Gui){

  printf("local bluetooth device [%s] is %sfound\n", qPrintable(bt_dev.address().toString()), bt_dev.isValid()? "" : "not ");

  ui->setupUi(this);
  if(bt_is_avaible()) bt_handle_avaible();
}

Gui::~Gui(){
  delete ui;
}

bool Gui::bt_is_avaible(){
  return bt_dev.isValid();
}

void Gui::bt_handle_avaible(){
  bt_service_discovery.reset(new QBluetoothServiceDiscoveryAgent());
  QBluetoothUuid uuid(QString(REMOTE_SERVICE_UUID));
  bt_service_discovery->setUuidFilter(uuid);

  connect(bt_service_discovery.get(),&QBluetoothServiceDiscoveryAgent::serviceDiscovered,this,&Gui::bt_new_service);

  ui->label_bt_status->setText("not connected");
  enable_bt_buttons();
}

void Gui::bt_new_service(const QBluetoothServiceInfo & service){
  printf("discovered client %s [%s]\n", qPrintable(service.device().name()), qPrintable(service.device().address().toString()));
  bt_connect(service);
}

//connect via connect button
void Gui::bt_connect(const string &device){
  printf("connecting..\n");
  ui->pushButton_connect->setText("connecting..");

  bt_socket.reset(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol));
  bt_socket->connectToService(QBluetoothAddress( QString(device.c_str())),QBluetoothUuid(QString(REMOTE_SERVICE_UUID)));
  bt_handle_connect();
}

//connect via scan
void Gui::bt_connect(const QBluetoothServiceInfo &service){
  printf("connecting..\n");
  bt_socket.reset(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol));
  bt_socket->connectToService(service);
  bt_handle_connect();
}

void Gui::bt_handle_connect(){
  ui->pushButton_connect->setEnabled(false);
  ui->pushButton_scan->setEnabled(false);

  connect(bt_socket.get(), &QBluetoothSocket::connected, [&](){
    ui->label_bt_status->setText("connected");
    ui->pushButton_connect->setText("disconnect");
    ui->pushButton_connect->setEnabled(true);
    core->bt_connected();
  });

  connect(bt_socket.get(), &QBluetoothSocket::disconnected, [&](){
    core->bt_disconnected();
  });

  connect(bt_socket.get(),&QBluetoothSocket::readyRead,[&](){
    bt_read();
  });

  //connect(bt_socket.get(),&QBluetoothSocket::error,[&](const QBluetoothSocket::SocketError& e){
    //  printf("bluetooth socket error\n");
    // bt_is_connected=false;
   //  enable_bt_buttons();
   //  ui->label_bt_status->setText("failed to connect to remote device");
 // });

  bt_is_writing=false;
}

void Gui::bt_read(){
  unique_lock<mutex> lck(bt_read_mtx, defer_lock_t());
  if(!lck.try_lock()) return;
  if(!bt_socket->bytesAvailable()) return;
  printf("reading new message from bluetooth..\n");
  Message::Type_t type = 0;
  Message::Size_t size = 0;
  bt_socket->read((char *)&type,sizeof(type));
  bt_socket->read((char *)&size,sizeof(size));
#ifdef TEXTMODE
  type-='0';
  size-='0';
#endif
  string payload(size, 0);
  Message::Size_t bytes_read = bt_socket->read(&payload[0],size);
  lck.unlock();
  std::thread t([this](){
    bt_read();
  });
  t.detach();
  // printf("type : %d\nsize : %d\npayload : %s\n----\n",
  //        int(type), int(size), payload.c_str());
  if(bytes_read<size){
    printf("** could not get all data\n");
    return;
  }
  core->process_msg(Msg_ptr(new Message(type,payload)));
}

void Gui::bt_send(const Msg_ptr &msg){
  unique_lock<mutex> lck(bt_write_mtx);
  write_mgs.emplace_back(msg);
  lck.unlock();
  bt_write();
}

void Gui::bt_write(){
  unique_lock<mutex> lck(bt_write_mtx);
  if(write_mgs.empty() || bt_is_writing) return;
  bt_is_writing = true;
  Msg_ptr msg = write_mgs.front();
  write_mgs.pop_front();
  lck.unlock();

  std::thread t([this,msg](){
    //write here
    bt_socket->write(msg->get_raw_data(),msg->get_raw_data_size());
    unique_lock<mutex> lck(bt_write_mtx);
    bt_is_writing = false;
    lck.unlock();
    bt_write();
  });
  t.detach();
}

void Gui::bt_close_socket(){
  bt_socket->close();
}

void Gui::bt_reset_socket(){
  enable_bt_buttons();
  bt_socket.reset();
  bt_is_writing= false;
}

// ------------- gui --------------


void Gui::enable_bt_buttons(){
  ui->pushButton_connect->setEnabled(true);
  ui->pushButton_connect->setText("connect");
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
  if(!core->get_bt_is_connected()) {
    bt_connect(REMOTE_DEVICE_ADDRESS);
  } else {
      bt_close_socket();
      ui->label_bt_status->setText("not connected");
  }
}
