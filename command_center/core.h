/*
 * Core är huvudklassen i progrmmet som sköter logiken och kommunimationen mellan de olika klasser
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <memory>
#include <deque>
#include <thread>
#include <mutex>
#include <ctime>

#ifdef LINUX
#include <boost/thread.hpp>
#endif

#include <QString>

#include "glob.h"
#include "gui.h"
#include "message.h"
#include "btinterface.h"
#include "data.h"

//always use smart pointers for class instances
class Core;
typedef unique_ptr<Core> Core_ptr;

class Gui;
typedef unique_ptr<Gui> Gui_ptr;

class BTInterface;
typedef unique_ptr<BTInterface> BTInterface_ptr;

class Data;
typedef unique_ptr<Data> Data_ptr;

class Serial;
typedef unique_ptr<Serial> Serial_ptr;

extern Core_ptr core;

class Core {
public:
  Core();
  ~Core();

  enum {PB_PAUSED, PB_PLAYING, PB_LIVE};

  // intiera subklasser och annat
  void init();
  // skriver ut information till standard output och till logkonsollen
  void log(const QString& data);

  //playback
  void pb_play_all();
  void pb_rewind();
  void pb_play();
  void pb_pause();
  void pb_goto(const unsigned& idx);
  void pb_reset();
  bool pb_play_next();
  bool pb_is_live();

  //öppna och stäng datafiler
  void data_save(const string& file_name);
  void data_open(const string& file_name);

  void process_new_msg(const Msg_ptr& msg);

  //blåtandsrelaterat
  void bt_avaible();
  void bt_connect();
  void bt_disconnect();
  void bt_connected();
  void bt_disconnected();

  bool bt_is_connected();

  // blåtandskommandon
  void custom_msg(const unsigned& type_, const string& payload);
  void echo();
  void go_forward();
  void go_backward();
  void turn_right();
  void turn_left();
  void go_forward_right();
  void go_forward_left();
  void set_speed(int speed);
  void set_degrees(int degrees);
  void stop();
  void open_claw();
  void close_claw();

  void change_direction(int direction);
  void change_drive_mode(int dm);

  void set_pd(int p, int d);
  void go_forward_pd();

  void calibrate_black();
  void calibrate_white();

private:
  //skriver ut när användarinput är orimlig
  void troll_input();

  //playback "gå" ett meddelande fram
  bool pb_play_one();
  //uppdatera guit (playback)
  void pb_gui_update();

  //behandla meddelande (reaktor-mönstret)
  void process_msg(const Msg_ptr& msg);

  //handle msgs
  void handle_echo(const Msg_ptr& msg);
  void handle_distance_data(const Msg_ptr &msg);
  void handle_tape_data(const Msg_ptr &msg);
  void handle_error(const Msg_ptr & msg);
  void handle_unknown(const Msg_ptr& msg);

  //skicka meddeltande
  void send(const Msg_ptr& msg);

  //data
  Gui_ptr w;
  BTInterface_ptr bt;
  Serial_ptr serial;
  Data_ptr data;

  unsigned pb_status = PB_PAUSED;

  //mutexes
#ifdef LINUX
   typedef boost::shared_mutex rw_mutex;
   typedef boost::shared_lock<boost::shared_mutex> r_lock;
   typedef boost::unique_lock<boost::shared_mutex> w_lock;
#else
   typedef std::mutex rw_mutex;
   typedef std::unique_lock<std::mutex> r_lock;
   typedef std::unique_lock<std::mutex> w_lock;
#endif
   rw_mutex pb_mtx;

};

#endif // CORE_H
