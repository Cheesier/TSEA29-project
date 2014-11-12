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
  enum msg_t{T_ECHO, T_P, T_D, T_GO_FORWARD_RIGHT = 0x05, T_GO_FORWARD_LEFT = 0x05, T_GO_FORWARD = 0x07, T_GO_BACKWARD = 0x08, T_TURN_LEFT = 0x09 , T_TURN_RIGHT = 0x0A,T_CLOSE_CLAW = 0x0B, T_OPEN_CLAW = 0x0C, T_STOP = 0x0D, T_ERROR = 0x3F};

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
  void go_forward(int speed);
  void go_backward(int speed);
  void turn_right(int speed);
  void turn_left(int speed);
  void go_forward_right(int speed);
  void go_forward_left(int speeds);
  void stop();
  void open_claw();
  void close_claw();

  void set_p(const double& val);
  void set_d(const double& val);


private:

  Type_t type;
  string data;
  hr_clock::time_point created_at;

  string raw_data;
};

#endif // MESSAGE_H
