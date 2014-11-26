/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gui
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionReset;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_scan;
    QPushButton *pushButton_connect;
    QLabel *label_bt_status;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_send;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_type;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_payload;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QFrame *line;
    QFrame *line_2;
    QPlainTextEdit *plainTextEdit_log;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QFrame *line_4;
    QSlider *horizontalSlider_pb;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_pb_rewind;
    QPushButton *pushButton_pb_play;
    QPushButton *pushButton_pb_next;
    QPushButton *pushButton_pb_live;
    QLabel *label_pb_status;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_pb_current;
    QLabel *label_7;
    QLabel *label_pb_total;
    QFrame *line_5;
    QFrame *line_6;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_left_sensor;
    QLabel *label_12;
    QLabel *label_backward_sensor;
    QLabel *label_right_sensor;
    QLabel *label_forward_sensor;
    QLabel *label_11;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_tape_11;
    QLabel *label_tape_10;
    QLabel *label_tape_9;
    QLabel *label_tape_8;
    QLabel *label_tape_7;
    QLabel *label_tape_6;
    QLabel *label_tape_5;
    QLabel *label_tape_4;
    QLabel *label_tape_3;
    QLabel *label_tape_2;
    QLabel *label_tape_1;
    QFrame *line_3;
    QFrame *line_7;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_direction;
    QLabel *label_4;
    QLabel *label_direction;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_right;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_set_speed;
    QLabel *label_speed;
    QSlider *horizontalSlider_speed;
    QPushButton *pushButton_backward;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_left;
    QPushButton *pushButton_forward;
    QPushButton *pushButton_forward_right;
    QPushButton *pushButton_forward_left;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_rotate_mode;
    QLabel *label_degrees;
    QSlider *horizontalSlider_degrees;
    QPushButton *pushButton_claw_switch;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_set_pd;
    QPushButton *pushButton_pdf;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_p_value;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_d_value;
    QFrame *line_8;
    QFrame *line_9;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButton_drive_mode;
    QLabel *label_9;
    QLabel *label_drive_mode;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName(QStringLiteral("Gui"));
        Gui->setEnabled(true);
        Gui->resize(1312, 710);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Gui->sizePolicy().hasHeightForWidth());
        Gui->setSizePolicy(sizePolicy);
        Gui->setStyleSheet(QStringLiteral(""));
        actionOpen = new QAction(Gui);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(Gui);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionReset = new QAction(Gui);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        centralWidget = new QWidget(Gui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(22, 429, 362, 31));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_scan = new QPushButton(gridLayoutWidget_2);
        pushButton_scan->setObjectName(QStringLiteral("pushButton_scan"));
        pushButton_scan->setEnabled(false);

        gridLayout->addWidget(pushButton_scan, 0, 1, 1, 1);

        pushButton_connect = new QPushButton(gridLayoutWidget_2);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setEnabled(false);

        gridLayout->addWidget(pushButton_connect, 0, 0, 1, 1);

        label_bt_status = new QLabel(centralWidget);
        label_bt_status->setObjectName(QStringLiteral("label_bt_status"));
        label_bt_status->setEnabled(true);
        label_bt_status->setGeometry(QRect(22, 469, 361, 26));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        label_bt_status->setFont(font);
        label_bt_status->setLayoutDirection(Qt::LeftToRight);
        label_bt_status->setStyleSheet(QStringLiteral("color: #ff0000;"));
        label_bt_status->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 539, 91, 61));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(20, 599, 361, 31));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_clear = new QPushButton(gridLayoutWidget_3);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        gridLayout_3->addWidget(pushButton_clear, 0, 1, 1, 1);

        pushButton_send = new QPushButton(gridLayoutWidget_3);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));

        gridLayout_3->addWidget(pushButton_send, 0, 0, 1, 1);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(110, 539, 271, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_type = new QLineEdit(verticalLayoutWidget);
        lineEdit_type->setObjectName(QStringLiteral("lineEdit_type"));

        horizontalLayout_2->addWidget(lineEdit_type);

        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEdit_payload = new QLineEdit(verticalLayoutWidget);
        lineEdit_payload->setObjectName(QStringLiteral("lineEdit_payload"));
        lineEdit_payload->setEnabled(true);

        horizontalLayout_6->addWidget(lineEdit_payload);

        comboBox_2 = new QComboBox(verticalLayoutWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_6->addWidget(comboBox_2);


        verticalLayout->addLayout(horizontalLayout_6);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 519, 361, 17));
        label_3->setAlignment(Qt::AlignCenter);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 48, 361, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(22, 408, 361, 21));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        plainTextEdit_log = new QPlainTextEdit(centralWidget);
        plainTextEdit_log->setObjectName(QStringLiteral("plainTextEdit_log"));
        plainTextEdit_log->setGeometry(QRect(850, 10, 421, 411));
        QFont font1;
        font1.setPointSize(9);
        plainTextEdit_log->setFont(font1);
        plainTextEdit_log->setStyleSheet(QLatin1String("background-color: #000000;\n"
"color:#ffffff;"));
        plainTextEdit_log->setBackgroundVisible(false);
        verticalLayoutWidget_4 = new QWidget(centralWidget);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(420, 460, 851, 73));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        line_4 = new QFrame(verticalLayoutWidget_4);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_4);

        horizontalSlider_pb = new QSlider(verticalLayoutWidget_4);
        horizontalSlider_pb->setObjectName(QStringLiteral("horizontalSlider_pb"));
        horizontalSlider_pb->setMaximum(0);
        horizontalSlider_pb->setValue(0);
        horizontalSlider_pb->setSliderPosition(0);
        horizontalSlider_pb->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(horizontalSlider_pb);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_pb_rewind = new QPushButton(verticalLayoutWidget_4);
        pushButton_pb_rewind->setObjectName(QStringLiteral("pushButton_pb_rewind"));

        horizontalLayout->addWidget(pushButton_pb_rewind);

        pushButton_pb_play = new QPushButton(verticalLayoutWidget_4);
        pushButton_pb_play->setObjectName(QStringLiteral("pushButton_pb_play"));

        horizontalLayout->addWidget(pushButton_pb_play);

        pushButton_pb_next = new QPushButton(verticalLayoutWidget_4);
        pushButton_pb_next->setObjectName(QStringLiteral("pushButton_pb_next"));

        horizontalLayout->addWidget(pushButton_pb_next);

        pushButton_pb_live = new QPushButton(verticalLayoutWidget_4);
        pushButton_pb_live->setObjectName(QStringLiteral("pushButton_pb_live"));

        horizontalLayout->addWidget(pushButton_pb_live);

        label_pb_status = new QLabel(verticalLayoutWidget_4);
        label_pb_status->setObjectName(QStringLiteral("label_pb_status"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_pb_status->setFont(font2);
        label_pb_status->setStyleSheet(QStringLiteral("color:#ff0000;"));
        label_pb_status->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_pb_status);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_pb_current = new QLabel(verticalLayoutWidget_4);
        label_pb_current->setObjectName(QStringLiteral("label_pb_current"));
        label_pb_current->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_pb_current);

        label_7 = new QLabel(verticalLayoutWidget_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(10, 16777215));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_7);

        label_pb_total = new QLabel(verticalLayoutWidget_4);
        label_pb_total->setObjectName(QStringLiteral("label_pb_total"));
        label_pb_total->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_pb_total);


        horizontalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(390, 10, 20, 621));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(820, 10, 20, 411));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        gridLayoutWidget_4 = new QWidget(centralWidget);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(420, 60, 391, 361));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_left_sensor = new QLabel(gridLayoutWidget_4);
        label_left_sensor->setObjectName(QStringLiteral("label_left_sensor"));
        label_left_sensor->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_left_sensor, 1, 0, 1, 1);

        label_12 = new QLabel(gridLayoutWidget_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 1, 1, 1, 1);

        label_backward_sensor = new QLabel(gridLayoutWidget_4);
        label_backward_sensor->setObjectName(QStringLiteral("label_backward_sensor"));
        label_backward_sensor->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_backward_sensor, 2, 1, 1, 1);

        label_right_sensor = new QLabel(gridLayoutWidget_4);
        label_right_sensor->setObjectName(QStringLiteral("label_right_sensor"));
        label_right_sensor->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_right_sensor, 1, 2, 1, 1);

        label_forward_sensor = new QLabel(gridLayoutWidget_4);
        label_forward_sensor->setObjectName(QStringLiteral("label_forward_sensor"));
        label_forward_sensor->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_forward_sensor, 0, 1, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(420, 9, 391, 16));
        label_11->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(420, 30, 391, 30));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_tape_11 = new QLabel(horizontalLayoutWidget_2);
        label_tape_11->setObjectName(QStringLiteral("label_tape_11"));
        QFont font3;
        font3.setPointSize(14);
        label_tape_11->setFont(font3);
        label_tape_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_11);

        label_tape_10 = new QLabel(horizontalLayoutWidget_2);
        label_tape_10->setObjectName(QStringLiteral("label_tape_10"));
        label_tape_10->setFont(font3);
        label_tape_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_10);

        label_tape_9 = new QLabel(horizontalLayoutWidget_2);
        label_tape_9->setObjectName(QStringLiteral("label_tape_9"));
        label_tape_9->setFont(font3);
        label_tape_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_9);

        label_tape_8 = new QLabel(horizontalLayoutWidget_2);
        label_tape_8->setObjectName(QStringLiteral("label_tape_8"));
        label_tape_8->setFont(font3);
        label_tape_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_8);

        label_tape_7 = new QLabel(horizontalLayoutWidget_2);
        label_tape_7->setObjectName(QStringLiteral("label_tape_7"));
        label_tape_7->setFont(font3);
        label_tape_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_7);

        label_tape_6 = new QLabel(horizontalLayoutWidget_2);
        label_tape_6->setObjectName(QStringLiteral("label_tape_6"));
        label_tape_6->setFont(font3);
        label_tape_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_6);

        label_tape_5 = new QLabel(horizontalLayoutWidget_2);
        label_tape_5->setObjectName(QStringLiteral("label_tape_5"));
        label_tape_5->setFont(font3);
        label_tape_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_5);

        label_tape_4 = new QLabel(horizontalLayoutWidget_2);
        label_tape_4->setObjectName(QStringLiteral("label_tape_4"));
        label_tape_4->setFont(font3);
        label_tape_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_4);

        label_tape_3 = new QLabel(horizontalLayoutWidget_2);
        label_tape_3->setObjectName(QStringLiteral("label_tape_3"));
        label_tape_3->setFont(font3);
        label_tape_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_3);

        label_tape_2 = new QLabel(horizontalLayoutWidget_2);
        label_tape_2->setObjectName(QStringLiteral("label_tape_2"));
        label_tape_2->setFont(font3);
        label_tape_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_2);

        label_tape_1 = new QLabel(horizontalLayoutWidget_2);
        label_tape_1->setObjectName(QStringLiteral("label_tape_1"));
        label_tape_1->setFont(font3);
        label_tape_1->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_tape_1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(22, 359, 361, 21));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(420, 420, 851, 41));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(19, 68, 361, 41));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        pushButton_direction = new QPushButton(horizontalLayoutWidget);
        pushButton_direction->setObjectName(QStringLiteral("pushButton_direction"));

        horizontalLayout_9->addWidget(pushButton_direction);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        label_direction = new QLabel(horizontalLayoutWidget);
        label_direction->setObjectName(QStringLiteral("label_direction"));

        horizontalLayout_9->addWidget(label_direction);

        gridLayoutWidget_5 = new QWidget(centralWidget);
        gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(20, 109, 361, 170));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_right = new QPushButton(gridLayoutWidget_5);
        pushButton_right->setObjectName(QStringLiteral("pushButton_right"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_right->sizePolicy().hasHeightForWidth());
        pushButton_right->setSizePolicy(sizePolicy1);
        pushButton_right->setMinimumSize(QSize(120, 0));

        gridLayout_4->addWidget(pushButton_right, 1, 2, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton_set_speed = new QPushButton(gridLayoutWidget_5);
        pushButton_set_speed->setObjectName(QStringLiteral("pushButton_set_speed"));

        horizontalLayout_7->addWidget(pushButton_set_speed);

        label_speed = new QLabel(gridLayoutWidget_5);
        label_speed->setObjectName(QStringLiteral("label_speed"));
        sizePolicy1.setHeightForWidth(label_speed->sizePolicy().hasHeightForWidth());
        label_speed->setSizePolicy(sizePolicy1);
        label_speed->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_speed);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalSlider_speed = new QSlider(gridLayoutWidget_5);
        horizontalSlider_speed->setObjectName(QStringLiteral("horizontalSlider_speed"));
        sizePolicy1.setHeightForWidth(horizontalSlider_speed->sizePolicy().hasHeightForWidth());
        horizontalSlider_speed->setSizePolicy(sizePolicy1);
        horizontalSlider_speed->setMaximum(255);
        horizontalSlider_speed->setValue(255);
        horizontalSlider_speed->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(horizontalSlider_speed);


        gridLayout_4->addLayout(verticalLayout_6, 2, 2, 1, 1);

        pushButton_backward = new QPushButton(gridLayoutWidget_5);
        pushButton_backward->setObjectName(QStringLiteral("pushButton_backward"));
        sizePolicy1.setHeightForWidth(pushButton_backward->sizePolicy().hasHeightForWidth());
        pushButton_backward->setSizePolicy(sizePolicy1);
        pushButton_backward->setMinimumSize(QSize(0, 50));
        pushButton_backward->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(pushButton_backward, 2, 1, 1, 1);

        pushButton_stop = new QPushButton(gridLayoutWidget_5);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        sizePolicy1.setHeightForWidth(pushButton_stop->sizePolicy().hasHeightForWidth());
        pushButton_stop->setSizePolicy(sizePolicy1);
        pushButton_stop->setMinimumSize(QSize(120, 50));

        gridLayout_4->addWidget(pushButton_stop, 1, 1, 1, 1);

        pushButton_left = new QPushButton(gridLayoutWidget_5);
        pushButton_left->setObjectName(QStringLiteral("pushButton_left"));
        sizePolicy1.setHeightForWidth(pushButton_left->sizePolicy().hasHeightForWidth());
        pushButton_left->setSizePolicy(sizePolicy1);
        pushButton_left->setMinimumSize(QSize(120, 0));

        gridLayout_4->addWidget(pushButton_left, 1, 0, 1, 1);

        pushButton_forward = new QPushButton(gridLayoutWidget_5);
        pushButton_forward->setObjectName(QStringLiteral("pushButton_forward"));
        sizePolicy1.setHeightForWidth(pushButton_forward->sizePolicy().hasHeightForWidth());
        pushButton_forward->setSizePolicy(sizePolicy1);
        pushButton_forward->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_forward, 0, 1, 1, 1);

        pushButton_forward_right = new QPushButton(gridLayoutWidget_5);
        pushButton_forward_right->setObjectName(QStringLiteral("pushButton_forward_right"));
        sizePolicy1.setHeightForWidth(pushButton_forward_right->sizePolicy().hasHeightForWidth());
        pushButton_forward_right->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pushButton_forward_right, 0, 2, 1, 1);

        pushButton_forward_left = new QPushButton(gridLayoutWidget_5);
        pushButton_forward_left->setObjectName(QStringLiteral("pushButton_forward_left"));
        sizePolicy1.setHeightForWidth(pushButton_forward_left->sizePolicy().hasHeightForWidth());
        pushButton_forward_left->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pushButton_forward_left, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        pushButton_rotate_mode = new QPushButton(gridLayoutWidget_5);
        pushButton_rotate_mode->setObjectName(QStringLiteral("pushButton_rotate_mode"));

        horizontalLayout_11->addWidget(pushButton_rotate_mode);

        label_degrees = new QLabel(gridLayoutWidget_5);
        label_degrees->setObjectName(QStringLiteral("label_degrees"));
        label_degrees->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_degrees);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalSlider_degrees = new QSlider(gridLayoutWidget_5);
        horizontalSlider_degrees->setObjectName(QStringLiteral("horizontalSlider_degrees"));
        horizontalSlider_degrees->setMaximum(255);
        horizontalSlider_degrees->setValue(90);
        horizontalSlider_degrees->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(horizontalSlider_degrees);


        gridLayout_4->addLayout(verticalLayout_5, 2, 0, 1, 1);

        pushButton_claw_switch = new QPushButton(centralWidget);
        pushButton_claw_switch->setObjectName(QStringLiteral("pushButton_claw_switch"));
        pushButton_claw_switch->setGeometry(QRect(20, 379, 361, 27));
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 299, 361, 68));
        horizontalLayout_10 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        pushButton_set_pd = new QPushButton(horizontalLayoutWidget_3);
        pushButton_set_pd->setObjectName(QStringLiteral("pushButton_set_pd"));
        sizePolicy1.setHeightForWidth(pushButton_set_pd->sizePolicy().hasHeightForWidth());
        pushButton_set_pd->setSizePolicy(sizePolicy1);
        pushButton_set_pd->setMinimumSize(QSize(120, 0));

        horizontalLayout_10->addWidget(pushButton_set_pd);

        pushButton_pdf = new QPushButton(horizontalLayoutWidget_3);
        pushButton_pdf->setObjectName(QStringLiteral("pushButton_pdf"));
        sizePolicy1.setHeightForWidth(pushButton_pdf->sizePolicy().hasHeightForWidth());
        pushButton_pdf->setSizePolicy(sizePolicy1);
        pushButton_pdf->setMinimumSize(QSize(120, 0));

        horizontalLayout_10->addWidget(pushButton_pdf);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(horizontalLayoutWidget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_5);

        lineEdit_p_value = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p_value->setObjectName(QStringLiteral("lineEdit_p_value"));
        lineEdit_p_value->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_4->addWidget(lineEdit_p_value);


        gridLayout_5->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(horizontalLayoutWidget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_6);

        lineEdit_d_value = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_d_value->setObjectName(QStringLiteral("lineEdit_d_value"));
        lineEdit_d_value->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_5->addWidget(lineEdit_d_value);


        gridLayout_5->addLayout(horizontalLayout_5, 2, 0, 1, 1);


        horizontalLayout_10->addLayout(gridLayout_5);

        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(20, 279, 361, 21));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_9 = new QFrame(centralWidget);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setGeometry(QRect(20, 500, 361, 21));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_4 = new QWidget(centralWidget);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(19, 8, 361, 41));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        pushButton_drive_mode = new QPushButton(horizontalLayoutWidget_4);
        pushButton_drive_mode->setObjectName(QStringLiteral("pushButton_drive_mode"));

        horizontalLayout_12->addWidget(pushButton_drive_mode);

        label_9 = new QLabel(horizontalLayoutWidget_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_12->addWidget(label_9);

        label_drive_mode = new QLabel(horizontalLayoutWidget_4);
        label_drive_mode->setObjectName(QStringLiteral("label_drive_mode"));

        horizontalLayout_12->addWidget(label_drive_mode);

        Gui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Gui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1312, 26));
        QFont font4;
        font4.setBold(true);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(75);
        menuBar->setFont(font4);
        menuBar->setStyleSheet(QStringLiteral(""));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        Gui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Gui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Gui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Gui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Gui->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionReset);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);

        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QMainWindow *Gui)
    {
        Gui->setWindowTitle(QApplication::translate("Gui", "Control Center", 0));
        actionOpen->setText(QApplication::translate("Gui", "Open", 0));
        actionSave->setText(QApplication::translate("Gui", "Save", 0));
        actionReset->setText(QApplication::translate("Gui", "Reset", 0));
        pushButton_scan->setText(QApplication::translate("Gui", "Scan..", 0));
        pushButton_connect->setText(QApplication::translate("Gui", "Connect", 0));
        label_bt_status->setText(QApplication::translate("Gui", "No bluetooth device avaible", 0));
        label->setText(QApplication::translate("Gui", "Type", 0));
        label_2->setText(QApplication::translate("Gui", "Payload", 0));
        pushButton_clear->setText(QApplication::translate("Gui", "Clear", 0));
        pushButton_send->setText(QApplication::translate("Gui", "Send", 0));
        label_3->setText(QApplication::translate("Gui", "Custom Message", 0));
        pushButton_pb_rewind->setText(QApplication::translate("Gui", "Rewind", 0));
        pushButton_pb_play->setText(QApplication::translate("Gui", "Pause", 0));
        pushButton_pb_next->setText(QApplication::translate("Gui", "Next", 0));
        pushButton_pb_live->setText(QApplication::translate("Gui", "Live", 0));
        label_pb_status->setText(QApplication::translate("Gui", "[LIVE]", 0));
        label_pb_current->setText(QApplication::translate("Gui", "0", 0));
        label_7->setText(QApplication::translate("Gui", "/", 0));
        label_pb_total->setText(QApplication::translate("Gui", "0", 0));
        label_left_sensor->setText(QApplication::translate("Gui", "--", 0));
        label_12->setText(QApplication::translate("Gui", "--", 0));
        label_backward_sensor->setText(QApplication::translate("Gui", "--", 0));
        label_right_sensor->setText(QApplication::translate("Gui", "--", 0));
        label_forward_sensor->setText(QApplication::translate("Gui", "--", 0));
        label_11->setText(QApplication::translate("Gui", "Sensors", 0));
        label_tape_11->setText(QApplication::translate("Gui", "0", 0));
        label_tape_10->setText(QApplication::translate("Gui", "0", 0));
        label_tape_9->setText(QApplication::translate("Gui", "0", 0));
        label_tape_8->setText(QApplication::translate("Gui", "0", 0));
        label_tape_7->setText(QApplication::translate("Gui", "0", 0));
        label_tape_6->setText(QApplication::translate("Gui", "0", 0));
        label_tape_5->setText(QApplication::translate("Gui", "0", 0));
        label_tape_4->setText(QApplication::translate("Gui", "0", 0));
        label_tape_3->setText(QApplication::translate("Gui", "0", 0));
        label_tape_2->setText(QApplication::translate("Gui", "0", 0));
        label_tape_1->setText(QApplication::translate("Gui", "0", 0));
        pushButton_direction->setText(QApplication::translate("Gui", "Switch Direction", 0));
        label_4->setText(QApplication::translate("Gui", "Current Direction:", 0));
        label_direction->setText(QApplication::translate("Gui", "Regular", 0));
        pushButton_right->setText(QApplication::translate("Gui", "R", 0));
        pushButton_set_speed->setText(QApplication::translate("Gui", "Set speed", 0));
        label_speed->setText(QApplication::translate("Gui", "255", 0));
        pushButton_backward->setText(QApplication::translate("Gui", "B", 0));
        pushButton_stop->setText(QApplication::translate("Gui", "S", 0));
        pushButton_left->setText(QApplication::translate("Gui", "L", 0));
        pushButton_forward->setText(QApplication::translate("Gui", "F", 0));
        pushButton_forward_right->setText(QApplication::translate("Gui", "RF", 0));
        pushButton_forward_left->setText(QApplication::translate("Gui", "LF", 0));
        pushButton_rotate_mode->setText(QApplication::translate("Gui", "Auto rotate", 0));
        label_degrees->setText(QApplication::translate("Gui", "90", 0));
        pushButton_claw_switch->setText(QApplication::translate("Gui", "Open Claw", 0));
        pushButton_set_pd->setText(QApplication::translate("Gui", "SetPD", 0));
        pushButton_pdf->setText(QApplication::translate("Gui", "PD F", 0));
        label_5->setText(QApplication::translate("Gui", "p :", 0));
        lineEdit_p_value->setText(QApplication::translate("Gui", "0", 0));
        label_6->setText(QApplication::translate("Gui", "d : ", 0));
        lineEdit_d_value->setText(QApplication::translate("Gui", "0", 0));
        pushButton_drive_mode->setText(QApplication::translate("Gui", "Switch drive mode", 0));
        label_9->setText(QApplication::translate("Gui", "Current drive mode:", 0));
        label_drive_mode->setText(QApplication::translate("Gui", "Manual", 0));
        menuFile->setTitle(QApplication::translate("Gui", "Data", 0));
        menuHelp->setTitle(QApplication::translate("Gui", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H