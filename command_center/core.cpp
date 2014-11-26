#include "core.h"
#include <string>

#include "serial.h"

#define TROLL_INPUT_MSG " *** invalid input value *** "

Core_ptr core;

Core::Core() {
  printf("creating core..\n");
#ifdef LINUX
  printf("running on linux\n");
#endif
}

Core::~Core() {
  //Something wierd, need to call destructor manually
  printf("destroying core..\n");
  w.reset();
}

void Core::init(){
  printf("initializing core..\n");
  w.reset(new Gui);
  w->show();
  bt.reset(new BTInterface);
  serial.reset(new Serial);

  serial->init_serial();
  serial->open_serial(SERIAL_PORT, BAUD_RATE);

  data.reset(new Data);
  pb_play_all();
}

void Core::log(const QString &data){
#define BUFFER_SIZE 20

  char time_str[BUFFER_SIZE] = "";
  time_t timestamp = time(0);
  //strftime(time_str,sizeof(time_str),"%T", localtime(&timestamp));
  QString out = QString("[%1] %2").arg(time_str,data);
  w->console_log(out);
  printf("%s\n", qPrintable(out));
}

void Core::troll_input(){
  log(TROLL_INPUT_MSG);
}

// ---------- playback -----------
#define REWIND_MSG " ------------ rewind --------------"
#define RESET_MSG "------------- reset --------------"

bool Core::pb_is_live(){
  r_lock l(pb_mtx);
  return pb_status == PB_LIVE;
}

void Core::pb_play_all(){
  w_lock l(pb_mtx);
  pb_status = PB_LIVE;
  pb_gui_update();
  while(pb_play_one());
}

bool Core::pb_play_next(){
  w_lock l(pb_mtx);
  return pb_play_one();
}

void Core::pb_rewind(){
  w_lock l(pb_mtx);
  pb_status = PB_PAUSED;
  log(REWIND_MSG);
  data->rewind();
  pb_gui_update();
}

void Core::pb_goto(const unsigned &idx){
  w_lock l(pb_mtx);
  pb_status = PB_PAUSED;
  if(idx<data->get_current_idx()){
      log(REWIND_MSG);
      data->rewind();
    }
  while(data->get_current_idx()<idx)
    pb_play_one();
  pb_gui_update();
}

void Core::pb_reset(){
  w_lock(pb_mtx);
  data->reset();
  log(RESET_MSG);
  pb_gui_update();
}

void Core::pb_pause(){
  w_lock l(pb_mtx);
  pb_status = PB_PAUSED;
  pb_gui_update();
}

//must be called by a synch method
bool Core::pb_play_one(){
  Msg_ptr msg;
  if(!data->get_next_msg(msg)) return false;
  process_msg(msg);
  pb_gui_update();
  return true;
}

//call from synch method
void Core::pb_gui_update(){
  w->pb_update(data->get_total_msgs(), data->get_current_idx(), pb_status);
}

//----------- data ------------

void Core::data_save(const string &file_name){
  r_lock l(pb_mtx);
  data->save(file_name);
}

void Core::data_open(const string &file_name){
  w_lock l(pb_mtx);
  pb_status = PB_PAUSED;
  data->open(file_name);
  pb_gui_update();
}

// --------- comm --------------

void Core::process_new_msg(const Msg_ptr &msg){
  thread t([this,msg](){
      data->append_msg(msg);
      if(!pb_is_live()) {
          pb_gui_update();
          return;
        }
      pb_play_all();
    });
  t.detach();
}

//not sychronized, hopefully won't be neccessary
void Core::process_msg(const Msg_ptr &msg){
  thread t([this, msg](){
      log(QString("processing message [type %1]").arg(msg->get_type() & 0x3F));

      if ((msg->get_type()/64) != (ADDR_KONTROLLCENTER/64)) {     //see if message is not meant for kontroll center
        log(QString("the message was meant for: %1..").arg(msg->get_type()/64)); // who was it meant for?
        return;
      }
      else {    // it was meant for kontroll center
          switch(msg->get_type() - ADDR_KONTROLLCENTER){  //remove ADDR
            case Message::T_ECHO:
              handle_echo(msg);
              break;
            case Message::T_DISTANCE_DATA:
              handle_distance_data(msg);
              break;
            case Message::T_TAPE_DATA:
              handle_tape_data(msg);
              break;
            case Message::T_ERROR:
              handle_error(msg);
              break;
            default:
              handle_unknown(msg);
              break;
          }
      }
    });
  t.detach();
}

void Core::handle_echo(const Msg_ptr &msg){
  msg->print();
}

void Core::handle_distance_data(const Msg_ptr &msg){
    w->onSensorInput(msg->get_data());
}

void Core::handle_tape_data(const Msg_ptr &msg){
    w->onTapeInput(msg->get_data());
}

//handles error messages 0x3F
void Core::handle_error(const Msg_ptr & msg){
    string message = "Error message recived: " + msg->get_data();
    log(QString::fromStdString(message));
    msg->print();
}

void Core::handle_unknown(const Msg_ptr &msg){
  log(QString("** unknown message [type %1] recived").arg(msg->get_type()));
  msg->print();
}

// ---------- bluetooth related --------

void Core::bt_avaible(){
  log("found local bluetooth device");
  w->bt_reset();
  //w->bt_reset();
}

void Core::bt_connect(){
  bt->connect_to_device(REMOTE_DEVICE_ADDRESS);
  w->bt_connecting();
}

void Core::bt_disconnect(){
  bt->disconnect();
  w->bt_reset();
}

void Core::bt_connected(){
  log("bluetooth link is established");
  w->bt_connected();
}

void Core::bt_disconnected(){
  log("** bluetooth link is closed");
  w->bt_reset();
}

bool Core::bt_is_connected(){
  return bt->is_connected();
}


// ------------- bluetooth commands -----------


void Core::send(const Msg_ptr &msg){
#ifdef BT_ACTIVE
  if(!bt->is_connected()) {
      log("failed to send message: bluetooth is not connected");
      return;
    }
  bt->send(msg);
#endif

#ifdef SERIAL_ACTIVE
  serial->serial_write(msg);
#endif
  log(QString("sending new msg [type %1]..").arg(msg->get_type()));
}

void Core::custom_msg(const unsigned &type, const string &payload){
  Msg_ptr msg(new Message(type,payload));
  msg->encode();
  send(msg);
}

void Core::echo(){
  Msg_ptr msg(new Message);
  msg->echo();
  send(msg);
}

void Core::go_forward(){
  Msg_ptr msg(new Message);
  msg->go_forward();
  send(msg);
}

void Core::go_backward(){
  Msg_ptr msg(new Message);
  msg->go_backward();
  send(msg);
}

void Core::turn_right(){
  Msg_ptr msg(new Message);
  msg->turn_right();
  send(msg);
}

void Core::turn_left(){
  Msg_ptr msg(new Message);
  msg->turn_left();
  send(msg);
}

void Core::go_forward_right(){
  Msg_ptr msg(new Message);
  msg->go_forward_right();
  send(msg);
}

void Core::go_forward_left(){
  Msg_ptr msg(new Message);
  msg->go_forward_left();
  send(msg);
}

void Core::set_speed(int speed){
  Msg_ptr msg(new Message);
  msg->set_speed(speed);
  send(msg);
}

void Core::set_degrees(int degrees){
  Msg_ptr msg(new Message);
  msg->set_degrees(degrees);
  send(msg);
}

void Core::stop(){
  Msg_ptr msg(new Message);
  msg->stop();
  send(msg);
}

void Core::open_claw(){
  Msg_ptr msg(new Message);
  msg->open_claw();
  send(msg);
}

void Core::close_claw(){
  Msg_ptr msg(new Message);
  msg->close_claw();
  send(msg);
}

void Core::change_direction(int direction){
  Msg_ptr msg(new Message);
  msg->change_direction(direction);
  send(msg);
}

void Core::change_drive_mode(int dm){
  Msg_ptr msg(new Message);
  msg->change_drive_mode(dm);
  send(msg);
}

void Core::set_pd(int p, int d){
  if(p <0 || p>255 || d <0 || d>255){
    troll_input();
    return;
  }
  Msg_ptr msg(new Message);
  msg->set_pd(p,d);
  send(msg);
}

void Core::go_forward_pd(){
  Msg_ptr msg(new Message);
  msg->go_forward_pd();
  send(msg);
}
