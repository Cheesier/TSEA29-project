    #ifndef MESSAGE_H
#define MESSAGE_H


#define ADDR_KOMMUNIKATIONSENHET 0x00
#define ADDR_STYRENHET           0x40
#define ADDR_SENSORENHET         0x80
#define ADDR_KONTROLLCENTER      0xC0


#include<string>
#include<memory>
#include<ctime>
#include<cstring>
#include<chrono>
#include<fstream>

#include "glob.h"

class Message;
typedef shared_ptr<Message> Msg_ptr;

typedef chrono::high_resolution_clock hr_clock;

class Message {
public:
  typedef unsigned char Size_t;
  typedef unsigned char Type_t;

  Message(){}
  Message(const Type_t& type_, const string& data_);
  enum msg_t{T_ECHO,
             //Send
             T_GO_FORWARD_PD    = 0x01,
             T_CHANGE_DIRECTION = 0x04,
             T_SET_PD           = 0x06,
             T_GO_FORWARD       = 0x07,
             T_GO_BACKWARD      = 0x08,
             T_TURN_LEFT        = 0x09,
             T_TURN_RIGHT       = 0x0A,
             T_CLOSE_CLAW       = 0x0B,
             T_OPEN_CLAW        = 0x0C,
             T_STOP             = 0x0D,
             T_SET_SPEED        = 0x0E,
             T_GO_FORWARD_LEFT  = 0x0F,
             T_GO_FORWARD_RIGHT = 0x10,
             T_SET_DEGREES      = 0x11,
             //Recive
             T_DISTANCE_DATA    = 0x20,
             T_TAPE_DATA        = 0x21,
             T_ERROR            = 0x3F};

  inline bool operator> (const Message& other) {return created_at > other.created_at;}
  inline bool operator< (const Message& other) {return created_at < other.created_at;}

  friend ostream& operator << (ostream& os, const Message& msg);
  friend istream& operator >> (istream& os, Message& msg);

  Type_t get_type() const;
  string get_data() const;
  hr_clock::time_point get_created_at()const;
  Size_t get_data_size() const;
  char * get_raw_data();
  size_t get_raw_data_size();

  void print();
  void encode();

  //constructors

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

  void set_pd(int p, int d);
  void go_forward_pd();


private:

  Type_t type;
  string data;
  hr_clock::time_point created_at;

  string raw_data;
};

#endif // MESSAGE_H
