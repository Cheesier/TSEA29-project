#ifndef GUI_H
#define GUI_H

#define QLABEL_STYLE_DISCONNECTED "QLabel{color:red;}"
#define QLABEL_STYLE_CONNECTING "QLabel{color:orange;}"
#define QLABEL_STYLE_CONNECTED "QLabel{color:green;}"

#include <memory>

#include <QMainWindow>
#include <QFileDialog>
#include <QShortcut>

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

  void onSensorInput(QByteArray sensorData);
  void onTapeInput(QByteArray tapeData);

  // --------- SIGNALS ------------
signals:
  void console_log(const QString& data);

  //playback
  void pb_update(const unsigned& total_msgs, const unsigned& current_msg, const unsigned& status);

  //bluetooth
  void bt_reset();
  void bt_connecting();
  void bt_connected();



  // ---------- SLOTS -------------
private slots:
  void console_log_(const QString& data);

  void pb_update_(const unsigned& total_msgs, const unsigned& current_msg, const unsigned& status);

  void bt_reset_();
  void bt_connecting_();
  void bt_connected_();

  //-- user input -- --------------
  void on_pushButton_forward_pressed();
  void on_pushButton_backward_pressed();
  void on_pushButton_left_pressed();
  void on_pushButton_right_pressed();

  void on_pushButton_stop_clicked();
  void on_pushButton_claw_switch_clicked();

  void on_pushButton_connect_clicked();

  void on_pushButton_scan_clicked();

  void on_pushButton_clear_clicked();
  void on_pushButton_send_clicked();

  void on_pushButton_pb_play_clicked();
  void on_pushButton_pb_next_clicked();
  void on_pushButton_pb_live_clicked();
  void on_pushButton_pb_rewind_clicked();
  void on_horizontalSlider_pb_sliderReleased();

  void on_actionReset_triggered();

  void on_actionSave_triggered();

  void on_actionOpen_triggered();

  void on_pushButton_set_pd_clicked();
  void on_pushButton_pdf_clicked();

  void on_pushButton_forward_left_pressed();

  void on_pushButton_forward_right_pressed();

  void on_horizontalSlider_speed_valueChanged();
  void on_pushButton_set_speed_clicked();
  void on_horizontalSlider_degrees_valueChanged();
  void on_pushButton_rotate_mode_clicked();

  void on_pushButton_direction_clicked();
  void on_pushButton_drive_mode_clicked();


private:

  Ui::Gui *ui;
};

#endif // GUI_H
