/********************************************************************************
** Form generated from reading UI file 'ParameterSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERSETTING_H
#define UI_PARAMETERSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_DialogSetting
{
public:
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox_ComNames;
    QPushButton *pushButton;
    QLabel *label_Status;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_9;
    QPushButton *pushButton_SendOK;
    QPushButton *pushButton_SendNG;
    QLabel *label_6;
    QSpinBox *spinBox_Heartbeat;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_SaveConfig;
    QComboBox *comboBox_SystemType;
    QLabel *label_8;
    QGroupBox *groupBox_Frist;
    QGridLayout *gridLayout;
    QLabel *label_First;
    QComboBox *comboBox_First;
    QPushButton *pushButton_OpenFirst;
    QRadioButton *radioButton_FreeFirst;
    QRadioButton *radioButton_ExternalFirst;
    QRadioButton *radioButton_SoftFirst;
    QPushButton *pushButton_TriggerFirst;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QLabel *label_FirstTime;
    QLabel *label_FirstResult;
    QCheckBox *checkBox_RenderFirst;
    MyLabel *label_FirstImage;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QLabel *label_2;
    QLineEdit *lineEdit_MachineCode;
    QPushButton *pushButton_Copy;
    QLabel *label_3;
    QLineEdit *lineEdit_RegisterCode;
    QPushButton *pushButton_Register;
    QLabel *label_RegisterInfo;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton_LoadFirstImage;
    QLineEdit *lineEdit_NGPath;
    QPushButton *pushButton_LoadNGPath;
    QLineEdit *lineEdit_OKPath;
    QPushButton *pushButton_LoadOKPath;
    QCheckBox *checkBox_SaveNG;
    QCheckBox *checkBox_SaveOK;
    QPushButton *pushButton_LoadSecondImage;
    QGroupBox *groupBox_Second;
    QGridLayout *gridLayout_2;
    QLabel *label_Second;
    QComboBox *comboBox_Second;
    QPushButton *pushButton_OpenSecond;
    QRadioButton *radioButton_FreeSecond;
    QRadioButton *radioButton_ExternalSecond;
    QRadioButton *radioButton_SoftSecond;
    QPushButton *pushButton_TriggerSecond;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_6;
    QLabel *label_SecondTime;
    QCheckBox *checkBox_RenderSecond;
    QLabel *label_SecondResult;
    MyLabel *label_SecondImage;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_12;
    QLabel *label_27;
    QLabel *label_29;
    QLabel *label_30;
    QSpinBox *spinBox_Area_quejijao;
    QSpinBox *spinBox_Wh_quejijao;
    QLabel *label_32;
    QSpinBox *spinBox_Area_maosi;
    QSpinBox *spinBox_Wh_maosi;
    QLabel *label_31;
    QSpinBox *spinBox_Area_yiwu;
    QSpinBox *spinBox_Wh_yiwu;
    QLabel *label_28;
    QSpinBox *spinBox_Area_zangwu_2;
    QSpinBox *spinBox_Wh_zangwu_2;
    QLabel *label_34;
    QSpinBox *spinBox_Area_yashang;
    QSpinBox *spinBox_Wh_yashang;
    QLabel *label_36;
    QSpinBox *spinBox_Area_shuikouchang;
    QSpinBox *spinBox_Wh_shuikouchang;
    QLabel *label_33;
    QSpinBox *spinBox_Area_qipao;
    QSpinBox *spinBox_Wh_qipao;
    QLabel *label_35;
    QSpinBox *spinBox_Area_yajiaoshang_2;
    QSpinBox *spinBox_Wh_yajiaoshang_2;
    QLabel *label_37;
    QSpinBox *spinBox_Area_duanjiezi;
    QSpinBox *spinBox_Wh_duanjiezi;
    QGroupBox *spinBox_Degree;
    QGridLayout *gridLayout_14;
    QLabel *label_19;
    QSpinBox *spinBox_AddDegreeThreshold;
    QLabel *label_21;
    QSpinBox *spinBox_SubDegreeThreshold;
    QLabel *label_20;
    QSpinBox *spinBox_Distance;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_13;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_18;
    QSpinBox *spinBox_Area_canjiao;
    QSpinBox *spinBox_Wh_canjiao;
    QLabel *label_14;
    QSpinBox *spinBox_Area_huashang;
    QSpinBox *spinBox_Wh_huashang;
    QLabel *label_17;
    QSpinBox *spinBox_Area_yajiaoshang;
    QSpinBox *spinBox_Wh_yajiaoshang;
    QLabel *label_13;
    QSpinBox *spinBox_Area_zangwu;
    QSpinBox *spinBox_Wh_zangwu;

    void setupUi(QDialog *DialogSetting)
    {
        if (DialogSetting->objectName().isEmpty())
            DialogSetting->setObjectName(QString::fromUtf8("DialogSetting"));
        DialogSetting->resize(1540, 862);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CMainWindow/Resources/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogSetting->setWindowIcon(icon);
        DialogSetting->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(0, 85, 0);"));
        gridLayout_11 = new QGridLayout(DialogSetting);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        groupBox_3 = new QGroupBox(DialogSetting);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(581, 16777215));
        gridLayout_10 = new QGridLayout(groupBox_3);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        comboBox_ComNames = new QComboBox(groupBox_3);
        comboBox_ComNames->setObjectName(QString::fromUtf8("comboBox_ComNames"));

        gridLayout_3->addWidget(comboBox_ComNames, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(pushButton, 0, 1, 1, 1);

        label_Status = new QLabel(groupBox_3);
        label_Status->setObjectName(QString::fromUtf8("label_Status"));
        label_Status->setMinimumSize(QSize(35, 35));
        label_Status->setMaximumSize(QSize(35, 35));
        label_Status->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        gridLayout_3->addWidget(label_Status, 0, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_3, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(168, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        pushButton_SendOK = new QPushButton(groupBox_3);
        pushButton_SendOK->setObjectName(QString::fromUtf8("pushButton_SendOK"));

        gridLayout_9->addWidget(pushButton_SendOK, 0, 0, 1, 1);

        pushButton_SendNG = new QPushButton(groupBox_3);
        pushButton_SendNG->setObjectName(QString::fromUtf8("pushButton_SendNG"));
        pushButton_SendNG->setMinimumSize(QSize(80, 0));
        pushButton_SendNG->setMaximumSize(QSize(80, 16777215));

        gridLayout_9->addWidget(pushButton_SendNG, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(50, 0));
        label_6->setMaximumSize(QSize(50, 16777215));

        gridLayout_9->addWidget(label_6, 0, 2, 1, 1);

        spinBox_Heartbeat = new QSpinBox(groupBox_3);
        spinBox_Heartbeat->setObjectName(QString::fromUtf8("spinBox_Heartbeat"));
        spinBox_Heartbeat->setMinimumSize(QSize(80, 0));
        spinBox_Heartbeat->setMaximumSize(QSize(80, 16777215));
        spinBox_Heartbeat->setMinimum(1);

        gridLayout_9->addWidget(spinBox_Heartbeat, 0, 3, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 1, 1, 1, 1);


        gridLayout_11->addWidget(groupBox_3, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(DialogSetting);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(581, 16777215));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton_SaveConfig = new QPushButton(groupBox_4);
        pushButton_SaveConfig->setObjectName(QString::fromUtf8("pushButton_SaveConfig"));
        pushButton_SaveConfig->setMaximumSize(QSize(90, 16777215));

        gridLayout_4->addWidget(pushButton_SaveConfig, 0, 3, 1, 1);

        comboBox_SystemType = new QComboBox(groupBox_4);
        comboBox_SystemType->setObjectName(QString::fromUtf8("comboBox_SystemType"));

        gridLayout_4->addWidget(comboBox_SystemType, 0, 1, 1, 2);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(90, 16777215));

        gridLayout_4->addWidget(label_8, 0, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_4, 3, 0, 1, 1);

        groupBox_Frist = new QGroupBox(DialogSetting);
        groupBox_Frist->setObjectName(QString::fromUtf8("groupBox_Frist"));
        groupBox_Frist->setMaximumSize(QSize(581, 16777215));
        gridLayout = new QGridLayout(groupBox_Frist);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_First = new QLabel(groupBox_Frist);
        label_First->setObjectName(QString::fromUtf8("label_First"));
        label_First->setMaximumSize(QSize(101, 16777215));

        gridLayout->addWidget(label_First, 0, 0, 1, 1);

        comboBox_First = new QComboBox(groupBox_Frist);
        comboBox_First->setObjectName(QString::fromUtf8("comboBox_First"));

        gridLayout->addWidget(comboBox_First, 0, 1, 1, 3);

        pushButton_OpenFirst = new QPushButton(groupBox_Frist);
        pushButton_OpenFirst->setObjectName(QString::fromUtf8("pushButton_OpenFirst"));
        pushButton_OpenFirst->setMaximumSize(QSize(111, 16777215));

        gridLayout->addWidget(pushButton_OpenFirst, 0, 4, 1, 1);

        radioButton_FreeFirst = new QRadioButton(groupBox_Frist);
        radioButton_FreeFirst->setObjectName(QString::fromUtf8("radioButton_FreeFirst"));

        gridLayout->addWidget(radioButton_FreeFirst, 1, 1, 1, 1);

        radioButton_ExternalFirst = new QRadioButton(groupBox_Frist);
        radioButton_ExternalFirst->setObjectName(QString::fromUtf8("radioButton_ExternalFirst"));

        gridLayout->addWidget(radioButton_ExternalFirst, 1, 2, 1, 1);

        radioButton_SoftFirst = new QRadioButton(groupBox_Frist);
        radioButton_SoftFirst->setObjectName(QString::fromUtf8("radioButton_SoftFirst"));

        gridLayout->addWidget(radioButton_SoftFirst, 1, 3, 1, 1);

        pushButton_TriggerFirst = new QPushButton(groupBox_Frist);
        pushButton_TriggerFirst->setObjectName(QString::fromUtf8("pushButton_TriggerFirst"));
        pushButton_TriggerFirst->setMaximumSize(QSize(111, 16777215));

        gridLayout->addWidget(pushButton_TriggerFirst, 1, 4, 1, 1);


        gridLayout_11->addWidget(groupBox_Frist, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(DialogSetting);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_FirstTime = new QLabel(groupBox_5);
        label_FirstTime->setObjectName(QString::fromUtf8("label_FirstTime"));
        label_FirstTime->setMinimumSize(QSize(241, 0));
        label_FirstTime->setMaximumSize(QSize(241, 51));
        label_FirstTime->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);"));

        gridLayout_5->addWidget(label_FirstTime, 0, 0, 1, 1);

        label_FirstResult = new QLabel(groupBox_5);
        label_FirstResult->setObjectName(QString::fromUtf8("label_FirstResult"));
        label_FirstResult->setMinimumSize(QSize(151, 0));
        label_FirstResult->setMaximumSize(QSize(151, 51));
        label_FirstResult->setStyleSheet(QString::fromUtf8("image: url(:/CMainWindow/Resources/OK.svg);"));

        gridLayout_5->addWidget(label_FirstResult, 0, 2, 1, 1);

        checkBox_RenderFirst = new QCheckBox(groupBox_5);
        checkBox_RenderFirst->setObjectName(QString::fromUtf8("checkBox_RenderFirst"));
        checkBox_RenderFirst->setMaximumSize(QSize(16777215, 51));
        checkBox_RenderFirst->setChecked(true);

        gridLayout_5->addWidget(checkBox_RenderFirst, 0, 1, 1, 1);

        label_FirstImage = new MyLabel(groupBox_5);
        label_FirstImage->setObjectName(QString::fromUtf8("label_FirstImage"));
        label_FirstImage->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout_5->addWidget(label_FirstImage, 1, 0, 1, 3);


        gridLayout_11->addWidget(groupBox_5, 0, 1, 4, 1);

        groupBox_7 = new QGroupBox(DialogSetting);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_2 = new QLabel(groupBox_7);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(80, 16777215));

        gridLayout_8->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_MachineCode = new QLineEdit(groupBox_7);
        lineEdit_MachineCode->setObjectName(QString::fromUtf8("lineEdit_MachineCode"));
        lineEdit_MachineCode->setReadOnly(true);

        gridLayout_8->addWidget(lineEdit_MachineCode, 0, 1, 1, 1);

        pushButton_Copy = new QPushButton(groupBox_7);
        pushButton_Copy->setObjectName(QString::fromUtf8("pushButton_Copy"));

        gridLayout_8->addWidget(pushButton_Copy, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox_7);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setMaximumSize(QSize(80, 16777215));

        gridLayout_8->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_RegisterCode = new QLineEdit(groupBox_7);
        lineEdit_RegisterCode->setObjectName(QString::fromUtf8("lineEdit_RegisterCode"));

        gridLayout_8->addWidget(lineEdit_RegisterCode, 1, 1, 1, 1);

        pushButton_Register = new QPushButton(groupBox_7);
        pushButton_Register->setObjectName(QString::fromUtf8("pushButton_Register"));

        gridLayout_8->addWidget(pushButton_Register, 1, 2, 1, 1);

        label_RegisterInfo = new QLabel(groupBox_7);
        label_RegisterInfo->setObjectName(QString::fromUtf8("label_RegisterInfo"));
        label_RegisterInfo->setLayoutDirection(Qt::LeftToRight);
        label_RegisterInfo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        label_RegisterInfo->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_RegisterInfo, 2, 0, 1, 3);


        gridLayout_11->addWidget(groupBox_7, 5, 0, 1, 1);

        groupBox = new QGroupBox(DialogSetting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_7 = new QGridLayout(groupBox);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pushButton_LoadFirstImage = new QPushButton(groupBox);
        pushButton_LoadFirstImage->setObjectName(QString::fromUtf8("pushButton_LoadFirstImage"));

        gridLayout_7->addWidget(pushButton_LoadFirstImage, 0, 0, 1, 1);

        lineEdit_NGPath = new QLineEdit(groupBox);
        lineEdit_NGPath->setObjectName(QString::fromUtf8("lineEdit_NGPath"));
        lineEdit_NGPath->setReadOnly(true);

        gridLayout_7->addWidget(lineEdit_NGPath, 2, 0, 1, 3);

        pushButton_LoadNGPath = new QPushButton(groupBox);
        pushButton_LoadNGPath->setObjectName(QString::fromUtf8("pushButton_LoadNGPath"));
        pushButton_LoadNGPath->setMaximumSize(QSize(120, 16777215));

        gridLayout_7->addWidget(pushButton_LoadNGPath, 2, 3, 1, 1);

        lineEdit_OKPath = new QLineEdit(groupBox);
        lineEdit_OKPath->setObjectName(QString::fromUtf8("lineEdit_OKPath"));
        lineEdit_OKPath->setReadOnly(true);

        gridLayout_7->addWidget(lineEdit_OKPath, 3, 0, 1, 3);

        pushButton_LoadOKPath = new QPushButton(groupBox);
        pushButton_LoadOKPath->setObjectName(QString::fromUtf8("pushButton_LoadOKPath"));

        gridLayout_7->addWidget(pushButton_LoadOKPath, 3, 3, 1, 1);

        checkBox_SaveNG = new QCheckBox(groupBox);
        checkBox_SaveNG->setObjectName(QString::fromUtf8("checkBox_SaveNG"));

        gridLayout_7->addWidget(checkBox_SaveNG, 1, 0, 1, 1);

        checkBox_SaveOK = new QCheckBox(groupBox);
        checkBox_SaveOK->setObjectName(QString::fromUtf8("checkBox_SaveOK"));

        gridLayout_7->addWidget(checkBox_SaveOK, 1, 2, 1, 1);

        pushButton_LoadSecondImage = new QPushButton(groupBox);
        pushButton_LoadSecondImage->setObjectName(QString::fromUtf8("pushButton_LoadSecondImage"));

        gridLayout_7->addWidget(pushButton_LoadSecondImage, 0, 2, 1, 1);


        gridLayout_11->addWidget(groupBox, 4, 0, 1, 1);

        groupBox_Second = new QGroupBox(DialogSetting);
        groupBox_Second->setObjectName(QString::fromUtf8("groupBox_Second"));
        groupBox_Second->setMaximumSize(QSize(581, 16777215));
        gridLayout_2 = new QGridLayout(groupBox_Second);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_Second = new QLabel(groupBox_Second);
        label_Second->setObjectName(QString::fromUtf8("label_Second"));
        label_Second->setMaximumSize(QSize(101, 16777215));

        gridLayout_2->addWidget(label_Second, 0, 0, 1, 1);

        comboBox_Second = new QComboBox(groupBox_Second);
        comboBox_Second->setObjectName(QString::fromUtf8("comboBox_Second"));

        gridLayout_2->addWidget(comboBox_Second, 0, 1, 1, 3);

        pushButton_OpenSecond = new QPushButton(groupBox_Second);
        pushButton_OpenSecond->setObjectName(QString::fromUtf8("pushButton_OpenSecond"));
        pushButton_OpenSecond->setMaximumSize(QSize(111, 16777215));

        gridLayout_2->addWidget(pushButton_OpenSecond, 0, 4, 1, 1);

        radioButton_FreeSecond = new QRadioButton(groupBox_Second);
        radioButton_FreeSecond->setObjectName(QString::fromUtf8("radioButton_FreeSecond"));

        gridLayout_2->addWidget(radioButton_FreeSecond, 1, 1, 1, 1);

        radioButton_ExternalSecond = new QRadioButton(groupBox_Second);
        radioButton_ExternalSecond->setObjectName(QString::fromUtf8("radioButton_ExternalSecond"));

        gridLayout_2->addWidget(radioButton_ExternalSecond, 1, 2, 1, 1);

        radioButton_SoftSecond = new QRadioButton(groupBox_Second);
        radioButton_SoftSecond->setObjectName(QString::fromUtf8("radioButton_SoftSecond"));

        gridLayout_2->addWidget(radioButton_SoftSecond, 1, 3, 1, 1);

        pushButton_TriggerSecond = new QPushButton(groupBox_Second);
        pushButton_TriggerSecond->setObjectName(QString::fromUtf8("pushButton_TriggerSecond"));
        pushButton_TriggerSecond->setMaximumSize(QSize(111, 16777215));

        gridLayout_2->addWidget(pushButton_TriggerSecond, 1, 4, 1, 1);


        gridLayout_11->addWidget(groupBox_Second, 1, 0, 1, 1);

        groupBox_6 = new QGroupBox(DialogSetting);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_6 = new QGridLayout(groupBox_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_SecondTime = new QLabel(groupBox_6);
        label_SecondTime->setObjectName(QString::fromUtf8("label_SecondTime"));
        label_SecondTime->setMinimumSize(QSize(241, 0));
        label_SecondTime->setMaximumSize(QSize(241, 51));
        label_SecondTime->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);"));

        gridLayout_6->addWidget(label_SecondTime, 0, 0, 1, 1);

        checkBox_RenderSecond = new QCheckBox(groupBox_6);
        checkBox_RenderSecond->setObjectName(QString::fromUtf8("checkBox_RenderSecond"));
        checkBox_RenderSecond->setMaximumSize(QSize(16777215, 51));
        checkBox_RenderSecond->setChecked(true);

        gridLayout_6->addWidget(checkBox_RenderSecond, 0, 1, 1, 1);

        label_SecondResult = new QLabel(groupBox_6);
        label_SecondResult->setObjectName(QString::fromUtf8("label_SecondResult"));
        label_SecondResult->setMinimumSize(QSize(151, 0));
        label_SecondResult->setMaximumSize(QSize(151, 51));
        label_SecondResult->setStyleSheet(QString::fromUtf8("image: url(:/CMainWindow/Resources/OK.svg);"));

        gridLayout_6->addWidget(label_SecondResult, 0, 2, 1, 1);

        label_SecondImage = new MyLabel(groupBox_6);
        label_SecondImage->setObjectName(QString::fromUtf8("label_SecondImage"));
        label_SecondImage->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout_6->addWidget(label_SecondImage, 1, 0, 1, 3);


        gridLayout_11->addWidget(groupBox_6, 0, 2, 4, 1);

        groupBox_8 = new QGroupBox(DialogSetting);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_12 = new QGridLayout(groupBox_8);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_27 = new QLabel(groupBox_8);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_12->addWidget(label_27, 0, 1, 1, 1);

        label_29 = new QLabel(groupBox_8);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_12->addWidget(label_29, 0, 2, 1, 1);

        label_30 = new QLabel(groupBox_8);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_12->addWidget(label_30, 1, 0, 1, 1);

        spinBox_Area_quejijao = new QSpinBox(groupBox_8);
        spinBox_Area_quejijao->setObjectName(QString::fromUtf8("spinBox_Area_quejijao"));
        spinBox_Area_quejijao->setMinimum(0);
        spinBox_Area_quejijao->setMaximum(10000);
        spinBox_Area_quejijao->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_quejijao, 1, 1, 1, 1);

        spinBox_Wh_quejijao = new QSpinBox(groupBox_8);
        spinBox_Wh_quejijao->setObjectName(QString::fromUtf8("spinBox_Wh_quejijao"));
        spinBox_Wh_quejijao->setMinimum(0);
        spinBox_Wh_quejijao->setMaximum(10000);
        spinBox_Wh_quejijao->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_quejijao, 1, 2, 1, 1);

        label_32 = new QLabel(groupBox_8);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_12->addWidget(label_32, 2, 0, 1, 1);

        spinBox_Area_maosi = new QSpinBox(groupBox_8);
        spinBox_Area_maosi->setObjectName(QString::fromUtf8("spinBox_Area_maosi"));
        spinBox_Area_maosi->setMinimum(0);
        spinBox_Area_maosi->setMaximum(10000);
        spinBox_Area_maosi->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_maosi, 2, 1, 1, 1);

        spinBox_Wh_maosi = new QSpinBox(groupBox_8);
        spinBox_Wh_maosi->setObjectName(QString::fromUtf8("spinBox_Wh_maosi"));
        spinBox_Wh_maosi->setMinimum(0);
        spinBox_Wh_maosi->setMaximum(10000);
        spinBox_Wh_maosi->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_maosi, 2, 2, 1, 1);

        label_31 = new QLabel(groupBox_8);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_12->addWidget(label_31, 3, 0, 1, 1);

        spinBox_Area_yiwu = new QSpinBox(groupBox_8);
        spinBox_Area_yiwu->setObjectName(QString::fromUtf8("spinBox_Area_yiwu"));
        spinBox_Area_yiwu->setMinimum(0);
        spinBox_Area_yiwu->setMaximum(10000);
        spinBox_Area_yiwu->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_yiwu, 3, 1, 1, 1);

        spinBox_Wh_yiwu = new QSpinBox(groupBox_8);
        spinBox_Wh_yiwu->setObjectName(QString::fromUtf8("spinBox_Wh_yiwu"));
        spinBox_Wh_yiwu->setMinimum(0);
        spinBox_Wh_yiwu->setMaximum(10000);
        spinBox_Wh_yiwu->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_yiwu, 3, 2, 1, 1);

        label_28 = new QLabel(groupBox_8);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_12->addWidget(label_28, 4, 0, 1, 1);

        spinBox_Area_zangwu_2 = new QSpinBox(groupBox_8);
        spinBox_Area_zangwu_2->setObjectName(QString::fromUtf8("spinBox_Area_zangwu_2"));
        spinBox_Area_zangwu_2->setMinimum(0);
        spinBox_Area_zangwu_2->setMaximum(10000);
        spinBox_Area_zangwu_2->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_zangwu_2, 4, 1, 1, 1);

        spinBox_Wh_zangwu_2 = new QSpinBox(groupBox_8);
        spinBox_Wh_zangwu_2->setObjectName(QString::fromUtf8("spinBox_Wh_zangwu_2"));
        spinBox_Wh_zangwu_2->setMinimum(0);
        spinBox_Wh_zangwu_2->setMaximum(10000);
        spinBox_Wh_zangwu_2->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_zangwu_2, 4, 2, 1, 1);

        label_34 = new QLabel(groupBox_8);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_12->addWidget(label_34, 5, 0, 1, 1);

        spinBox_Area_yashang = new QSpinBox(groupBox_8);
        spinBox_Area_yashang->setObjectName(QString::fromUtf8("spinBox_Area_yashang"));
        spinBox_Area_yashang->setMinimum(0);
        spinBox_Area_yashang->setMaximum(10000);
        spinBox_Area_yashang->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_yashang, 5, 1, 1, 1);

        spinBox_Wh_yashang = new QSpinBox(groupBox_8);
        spinBox_Wh_yashang->setObjectName(QString::fromUtf8("spinBox_Wh_yashang"));
        spinBox_Wh_yashang->setMinimum(0);
        spinBox_Wh_yashang->setMaximum(10000);
        spinBox_Wh_yashang->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_yashang, 5, 2, 1, 1);

        label_36 = new QLabel(groupBox_8);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_12->addWidget(label_36, 6, 0, 1, 1);

        spinBox_Area_shuikouchang = new QSpinBox(groupBox_8);
        spinBox_Area_shuikouchang->setObjectName(QString::fromUtf8("spinBox_Area_shuikouchang"));
        spinBox_Area_shuikouchang->setMinimum(0);
        spinBox_Area_shuikouchang->setMaximum(10000);
        spinBox_Area_shuikouchang->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_shuikouchang, 6, 1, 1, 1);

        spinBox_Wh_shuikouchang = new QSpinBox(groupBox_8);
        spinBox_Wh_shuikouchang->setObjectName(QString::fromUtf8("spinBox_Wh_shuikouchang"));
        spinBox_Wh_shuikouchang->setMinimum(0);
        spinBox_Wh_shuikouchang->setMaximum(10000);
        spinBox_Wh_shuikouchang->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_shuikouchang, 6, 2, 1, 1);

        label_33 = new QLabel(groupBox_8);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_12->addWidget(label_33, 7, 0, 1, 1);

        spinBox_Area_qipao = new QSpinBox(groupBox_8);
        spinBox_Area_qipao->setObjectName(QString::fromUtf8("spinBox_Area_qipao"));
        spinBox_Area_qipao->setMinimum(0);
        spinBox_Area_qipao->setMaximum(10000);
        spinBox_Area_qipao->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_qipao, 7, 1, 1, 1);

        spinBox_Wh_qipao = new QSpinBox(groupBox_8);
        spinBox_Wh_qipao->setObjectName(QString::fromUtf8("spinBox_Wh_qipao"));
        spinBox_Wh_qipao->setMinimum(0);
        spinBox_Wh_qipao->setMaximum(10000);
        spinBox_Wh_qipao->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_qipao, 7, 2, 1, 1);

        label_35 = new QLabel(groupBox_8);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_12->addWidget(label_35, 8, 0, 1, 1);

        spinBox_Area_yajiaoshang_2 = new QSpinBox(groupBox_8);
        spinBox_Area_yajiaoshang_2->setObjectName(QString::fromUtf8("spinBox_Area_yajiaoshang_2"));
        spinBox_Area_yajiaoshang_2->setMinimum(0);
        spinBox_Area_yajiaoshang_2->setMaximum(10000);
        spinBox_Area_yajiaoshang_2->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_yajiaoshang_2, 8, 1, 1, 1);

        spinBox_Wh_yajiaoshang_2 = new QSpinBox(groupBox_8);
        spinBox_Wh_yajiaoshang_2->setObjectName(QString::fromUtf8("spinBox_Wh_yajiaoshang_2"));
        spinBox_Wh_yajiaoshang_2->setMinimum(0);
        spinBox_Wh_yajiaoshang_2->setMaximum(10000);
        spinBox_Wh_yajiaoshang_2->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_yajiaoshang_2, 8, 2, 1, 1);

        label_37 = new QLabel(groupBox_8);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_12->addWidget(label_37, 9, 0, 1, 1);

        spinBox_Area_duanjiezi = new QSpinBox(groupBox_8);
        spinBox_Area_duanjiezi->setObjectName(QString::fromUtf8("spinBox_Area_duanjiezi"));
        spinBox_Area_duanjiezi->setMinimum(0);
        spinBox_Area_duanjiezi->setMaximum(10000);
        spinBox_Area_duanjiezi->setValue(0);

        gridLayout_12->addWidget(spinBox_Area_duanjiezi, 9, 1, 1, 1);

        spinBox_Wh_duanjiezi = new QSpinBox(groupBox_8);
        spinBox_Wh_duanjiezi->setObjectName(QString::fromUtf8("spinBox_Wh_duanjiezi"));
        spinBox_Wh_duanjiezi->setMinimum(0);
        spinBox_Wh_duanjiezi->setMaximum(10000);
        spinBox_Wh_duanjiezi->setValue(0);

        gridLayout_12->addWidget(spinBox_Wh_duanjiezi, 9, 2, 1, 1);


        gridLayout_11->addWidget(groupBox_8, 4, 2, 2, 1);

        spinBox_Degree = new QGroupBox(DialogSetting);
        spinBox_Degree->setObjectName(QString::fromUtf8("spinBox_Degree"));
        gridLayout_14 = new QGridLayout(spinBox_Degree);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        label_19 = new QLabel(spinBox_Degree);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_14->addWidget(label_19, 0, 0, 1, 1);

        spinBox_AddDegreeThreshold = new QSpinBox(spinBox_Degree);
        spinBox_AddDegreeThreshold->setObjectName(QString::fromUtf8("spinBox_AddDegreeThreshold"));
        spinBox_AddDegreeThreshold->setMinimum(-180);
        spinBox_AddDegreeThreshold->setMaximum(180);
        spinBox_AddDegreeThreshold->setValue(0);

        gridLayout_14->addWidget(spinBox_AddDegreeThreshold, 0, 1, 1, 1);

        label_21 = new QLabel(spinBox_Degree);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_14->addWidget(label_21, 1, 0, 1, 1);

        spinBox_SubDegreeThreshold = new QSpinBox(spinBox_Degree);
        spinBox_SubDegreeThreshold->setObjectName(QString::fromUtf8("spinBox_SubDegreeThreshold"));
        spinBox_SubDegreeThreshold->setMinimum(-180);
        spinBox_SubDegreeThreshold->setMaximum(180);
        spinBox_SubDegreeThreshold->setValue(0);

        gridLayout_14->addWidget(spinBox_SubDegreeThreshold, 1, 1, 1, 1);

        label_20 = new QLabel(spinBox_Degree);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_14->addWidget(label_20, 2, 0, 1, 1);

        spinBox_Distance = new QSpinBox(spinBox_Degree);
        spinBox_Distance->setObjectName(QString::fromUtf8("spinBox_Distance"));
        spinBox_Distance->setMinimum(2);
        spinBox_Distance->setValue(10);

        gridLayout_14->addWidget(spinBox_Distance, 2, 1, 1, 1);


        gridLayout_11->addWidget(spinBox_Degree, 5, 1, 1, 1);

        groupBox_2 = new QGroupBox(DialogSetting);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_13 = new QGridLayout(groupBox_2);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_13->addWidget(label_15, 0, 1, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_13->addWidget(label_16, 0, 2, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_13->addWidget(label_18, 1, 0, 1, 1);

        spinBox_Area_canjiao = new QSpinBox(groupBox_2);
        spinBox_Area_canjiao->setObjectName(QString::fromUtf8("spinBox_Area_canjiao"));
        spinBox_Area_canjiao->setMinimum(0);
        spinBox_Area_canjiao->setMaximum(10000);
        spinBox_Area_canjiao->setValue(0);

        gridLayout_13->addWidget(spinBox_Area_canjiao, 1, 1, 1, 1);

        spinBox_Wh_canjiao = new QSpinBox(groupBox_2);
        spinBox_Wh_canjiao->setObjectName(QString::fromUtf8("spinBox_Wh_canjiao"));
        spinBox_Wh_canjiao->setMinimum(0);
        spinBox_Wh_canjiao->setMaximum(10000);
        spinBox_Wh_canjiao->setValue(0);

        gridLayout_13->addWidget(spinBox_Wh_canjiao, 1, 2, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_13->addWidget(label_14, 2, 0, 1, 1);

        spinBox_Area_huashang = new QSpinBox(groupBox_2);
        spinBox_Area_huashang->setObjectName(QString::fromUtf8("spinBox_Area_huashang"));
        spinBox_Area_huashang->setMinimum(0);
        spinBox_Area_huashang->setMaximum(10000);
        spinBox_Area_huashang->setValue(0);

        gridLayout_13->addWidget(spinBox_Area_huashang, 2, 1, 1, 1);

        spinBox_Wh_huashang = new QSpinBox(groupBox_2);
        spinBox_Wh_huashang->setObjectName(QString::fromUtf8("spinBox_Wh_huashang"));
        spinBox_Wh_huashang->setMinimum(0);
        spinBox_Wh_huashang->setMaximum(10000);
        spinBox_Wh_huashang->setValue(0);

        gridLayout_13->addWidget(spinBox_Wh_huashang, 2, 2, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_13->addWidget(label_17, 3, 0, 1, 1);

        spinBox_Area_yajiaoshang = new QSpinBox(groupBox_2);
        spinBox_Area_yajiaoshang->setObjectName(QString::fromUtf8("spinBox_Area_yajiaoshang"));
        spinBox_Area_yajiaoshang->setMinimum(0);
        spinBox_Area_yajiaoshang->setMaximum(10000);
        spinBox_Area_yajiaoshang->setValue(0);

        gridLayout_13->addWidget(spinBox_Area_yajiaoshang, 3, 1, 1, 1);

        spinBox_Wh_yajiaoshang = new QSpinBox(groupBox_2);
        spinBox_Wh_yajiaoshang->setObjectName(QString::fromUtf8("spinBox_Wh_yajiaoshang"));
        spinBox_Wh_yajiaoshang->setMinimum(0);
        spinBox_Wh_yajiaoshang->setMaximum(10000);
        spinBox_Wh_yajiaoshang->setValue(0);

        gridLayout_13->addWidget(spinBox_Wh_yajiaoshang, 3, 2, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_13->addWidget(label_13, 4, 0, 1, 1);

        spinBox_Area_zangwu = new QSpinBox(groupBox_2);
        spinBox_Area_zangwu->setObjectName(QString::fromUtf8("spinBox_Area_zangwu"));
        spinBox_Area_zangwu->setMinimum(0);
        spinBox_Area_zangwu->setMaximum(10000);
        spinBox_Area_zangwu->setValue(0);

        gridLayout_13->addWidget(spinBox_Area_zangwu, 4, 1, 1, 1);

        spinBox_Wh_zangwu = new QSpinBox(groupBox_2);
        spinBox_Wh_zangwu->setObjectName(QString::fromUtf8("spinBox_Wh_zangwu"));
        spinBox_Wh_zangwu->setMinimum(0);
        spinBox_Wh_zangwu->setMaximum(10000);
        spinBox_Wh_zangwu->setValue(0);

        gridLayout_13->addWidget(spinBox_Wh_zangwu, 4, 2, 1, 1);


        gridLayout_11->addWidget(groupBox_2, 4, 1, 1, 1);


        retranslateUi(DialogSetting);
        QObject::connect(pushButton_OpenFirst, SIGNAL(clicked()), DialogSetting, SLOT(OpenFirstCamera()));
        QObject::connect(pushButton_TriggerFirst, SIGNAL(clicked()), DialogSetting, SLOT(FirstSoftTriggerOnce()));
        QObject::connect(pushButton_OpenSecond, SIGNAL(clicked()), DialogSetting, SLOT(OpenSecondCamera()));
        QObject::connect(pushButton_TriggerSecond, SIGNAL(clicked()), DialogSetting, SLOT(SecondSoftTirggerOnce()));
        QObject::connect(pushButton_SendOK, SIGNAL(clicked()), DialogSetting, SLOT(SendOKToPLC()));
        QObject::connect(pushButton_SendNG, SIGNAL(clicked()), DialogSetting, SLOT(SendNGToPLC()));
        QObject::connect(pushButton_SaveConfig, SIGNAL(clicked()), DialogSetting, SLOT(SaveConfig()));
        QObject::connect(comboBox_SystemType, SIGNAL(activated(int)), DialogSetting, SLOT(SetSystemType(int)));
        QObject::connect(checkBox_RenderFirst, SIGNAL(clicked(bool)), DialogSetting, SLOT(ShowFristRender(bool)));
        QObject::connect(checkBox_RenderSecond, SIGNAL(clicked(bool)), DialogSetting, SLOT(ShowSecondRender(bool)));
        QObject::connect(pushButton_LoadFirstImage, SIGNAL(clicked()), DialogSetting, SLOT(LoadFirstImage()));
        QObject::connect(pushButton_LoadSecondImage, SIGNAL(clicked()), DialogSetting, SLOT(LoadSecondImage()));
        QObject::connect(checkBox_SaveNG, SIGNAL(clicked(bool)), DialogSetting, SLOT(SetSaveNGChecked(bool)));
        QObject::connect(checkBox_SaveOK, SIGNAL(clicked(bool)), DialogSetting, SLOT(SetSaveOKChecked(bool)));
        QObject::connect(pushButton_LoadNGPath, SIGNAL(clicked()), DialogSetting, SLOT(LoadNGPath()));
        QObject::connect(pushButton_LoadOKPath, SIGNAL(clicked()), DialogSetting, SLOT(LoadOKPath()));
        QObject::connect(pushButton, SIGNAL(clicked()), DialogSetting, SLOT(OpenSerial()));
        QObject::connect(pushButton_Copy, SIGNAL(clicked()), DialogSetting, SLOT(CopyRegisterCode()));
        QObject::connect(pushButton_Register, SIGNAL(clicked()), DialogSetting, SLOT(SoftwareRegister()));
        QObject::connect(spinBox_Area_maosi, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_yiwu, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_zangwu_2, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_yashang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_shuikouchang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_qipao, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_yajiaoshang_2, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_duanjiezi, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_maosi, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_yiwu, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_zangwu_2, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_yashang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_shuikouchang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_qipao, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_yajiaoshang_2, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_duanjiezi, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_quejijao, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Wh_quejijao, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetSecondThreshold()));
        QObject::connect(spinBox_Area_zangwu, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Wh_zangwu, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Area_canjiao, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Wh_canjiao, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Area_huashang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Wh_huashang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Area_yajiaoshang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_Wh_yajiaoshang, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetFirstThreshold()));
        QObject::connect(spinBox_AddDegreeThreshold, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetDegreeThreshold()));
        QObject::connect(spinBox_SubDegreeThreshold, SIGNAL(valueChanged(int)), DialogSetting, SLOT(SetDegreeThreshold()));

        QMetaObject::connectSlotsByName(DialogSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogSetting)
    {
        DialogSetting->setWindowTitle(QCoreApplication::translate("DialogSetting", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("DialogSetting", "\351\200\232\350\256\257", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogSetting", "\346\211\223\345\274\200", nullptr));
        label_Status->setText(QString());
        pushButton_SendOK->setText(QCoreApplication::translate("DialogSetting", "\345\217\221\351\200\201OK", nullptr));
        pushButton_SendNG->setText(QCoreApplication::translate("DialogSetting", "\345\217\221\351\200\201NG", nullptr));
        label_6->setText(QCoreApplication::translate("DialogSetting", "\345\277\203\350\267\263", nullptr));
        spinBox_Heartbeat->setSuffix(QCoreApplication::translate("DialogSetting", "\347\247\222", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("DialogSetting", "\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        pushButton_SaveConfig->setText(QCoreApplication::translate("DialogSetting", "\344\277\235\345\255\230\345\217\202\346\225\260", nullptr));
        label_8->setText(QCoreApplication::translate("DialogSetting", "\350\277\220\350\241\214\346\250\241\345\274\217", nullptr));
        groupBox_Frist->setTitle(QCoreApplication::translate("DialogSetting", "\344\270\200\345\267\245\344\275\215-\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
        label_First->setText(QCoreApplication::translate("DialogSetting", "\347\233\270\346\234\272\345\220\215\347\247\260", nullptr));
        pushButton_OpenFirst->setText(QCoreApplication::translate("DialogSetting", "\346\211\223\345\274\200\347\233\270\346\234\272", nullptr));
        radioButton_FreeFirst->setText(QCoreApplication::translate("DialogSetting", "\350\207\252\347\224\261\351\207\207\351\233\206", nullptr));
        radioButton_ExternalFirst->setText(QCoreApplication::translate("DialogSetting", "\347\241\254\350\247\246\345\217\221", nullptr));
        radioButton_SoftFirst->setText(QCoreApplication::translate("DialogSetting", "\350\275\257\350\247\246\345\217\221", nullptr));
        pushButton_TriggerFirst->setText(QCoreApplication::translate("DialogSetting", "\350\247\246\345\217\221\344\270\200\346\254\241", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("DialogSetting", "\344\270\200\345\267\245\344\275\215", nullptr));
        label_FirstTime->setText(QCoreApplication::translate("DialogSetting", "\350\200\227\346\227\266\357\274\232", nullptr));
        label_FirstResult->setText(QString());
        checkBox_RenderFirst->setText(QCoreApplication::translate("DialogSetting", "\346\270\262\346\237\223\345\233\276", nullptr));
        label_FirstImage->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("DialogSetting", "\350\275\257\344\273\266\346\263\250\345\206\214", nullptr));
        label_2->setText(QCoreApplication::translate("DialogSetting", "\346\234\272\345\231\250\347\240\201\357\274\232", nullptr));
        pushButton_Copy->setText(QCoreApplication::translate("DialogSetting", "\345\244\215\345\210\266\346\234\272\345\231\250\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("DialogSetting", "\346\263\250\345\206\214\347\240\201\357\274\232", nullptr));
        pushButton_Register->setText(QCoreApplication::translate("DialogSetting", "\346\263\250\345\206\214", nullptr));
        label_RegisterInfo->setText(QCoreApplication::translate("DialogSetting", "\346\234\252\346\263\250\345\206\214", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DialogSetting", "\346\225\260\346\215\256\345\255\230\346\241\243", nullptr));
        pushButton_LoadFirstImage->setText(QCoreApplication::translate("DialogSetting", "\345\212\240\350\275\275\344\270\200\345\267\245\344\275\215\345\233\276\345\203\217", nullptr));
        lineEdit_NGPath->setPlaceholderText(QCoreApplication::translate("DialogSetting", "NG\345\233\276\345\203\217\350\267\257\345\276\204", nullptr));
        pushButton_LoadNGPath->setText(QCoreApplication::translate("DialogSetting", "\346\211\223\345\274\200\350\267\257\345\276\204", nullptr));
        lineEdit_OKPath->setPlaceholderText(QCoreApplication::translate("DialogSetting", "OK\345\233\276\345\203\217\350\267\257\345\276\204", nullptr));
        pushButton_LoadOKPath->setText(QCoreApplication::translate("DialogSetting", "\346\211\223\345\274\200\350\267\257\345\276\204", nullptr));
        checkBox_SaveNG->setText(QCoreApplication::translate("DialogSetting", "\344\277\235\345\255\230NG", nullptr));
        checkBox_SaveOK->setText(QCoreApplication::translate("DialogSetting", "\344\277\235\345\255\230OK", nullptr));
        pushButton_LoadSecondImage->setText(QCoreApplication::translate("DialogSetting", "\345\212\240\350\275\275\344\272\214\345\267\245\344\275\215\345\233\276\345\203\217", nullptr));
        groupBox_Second->setTitle(QCoreApplication::translate("DialogSetting", "\344\272\214\345\267\245\344\275\215-\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
        label_Second->setText(QCoreApplication::translate("DialogSetting", "\347\233\270\346\234\272\345\220\215\347\247\260", nullptr));
        pushButton_OpenSecond->setText(QCoreApplication::translate("DialogSetting", "\346\211\223\345\274\200\347\233\270\346\234\272", nullptr));
        radioButton_FreeSecond->setText(QCoreApplication::translate("DialogSetting", "\350\207\252\347\224\261\351\207\207\351\233\206", nullptr));
        radioButton_ExternalSecond->setText(QCoreApplication::translate("DialogSetting", "\347\241\254\350\247\246\345\217\221", nullptr));
        radioButton_SoftSecond->setText(QCoreApplication::translate("DialogSetting", "\350\275\257\350\247\246\345\217\221", nullptr));
        pushButton_TriggerSecond->setText(QCoreApplication::translate("DialogSetting", "\350\247\246\345\217\221\344\270\200\346\254\241", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("DialogSetting", "\344\272\214\345\267\245\344\275\215", nullptr));
        label_SecondTime->setText(QCoreApplication::translate("DialogSetting", "\350\200\227\346\227\266\357\274\232", nullptr));
        checkBox_RenderSecond->setText(QCoreApplication::translate("DialogSetting", "\346\270\262\346\237\223\345\233\276", nullptr));
        label_SecondResult->setText(QString());
        label_SecondImage->setText(QString());
        groupBox_8->setTitle(QCoreApplication::translate("DialogSetting", "\344\272\214\345\267\245\344\275\215\347\274\272\351\231\267\351\230\210\345\200\274\350\256\276\347\275\256", nullptr));
        label_27->setText(QCoreApplication::translate("DialogSetting", "\351\235\242\347\247\257\351\230\210\345\200\274", nullptr));
        label_29->setText(QCoreApplication::translate("DialogSetting", "\351\225\277\345\272\246\351\230\210\345\200\274", nullptr));
        label_30->setText(QCoreApplication::translate("DialogSetting", "\347\274\272\350\203\266", nullptr));
        spinBox_Area_quejijao->setSuffix(QString());
        spinBox_Area_quejijao->setPrefix(QString());
        spinBox_Wh_quejijao->setSuffix(QString());
        spinBox_Wh_quejijao->setPrefix(QString());
        label_32->setText(QCoreApplication::translate("DialogSetting", "\346\257\233\344\270\235", nullptr));
        spinBox_Area_maosi->setSuffix(QString());
        spinBox_Area_maosi->setPrefix(QString());
        spinBox_Wh_maosi->setSuffix(QString());
        spinBox_Wh_maosi->setPrefix(QString());
        label_31->setText(QCoreApplication::translate("DialogSetting", "\345\274\202\347\211\251", nullptr));
        spinBox_Area_yiwu->setSuffix(QString());
        spinBox_Area_yiwu->setPrefix(QString());
        spinBox_Wh_yiwu->setSuffix(QString());
        spinBox_Wh_yiwu->setPrefix(QString());
        label_28->setText(QCoreApplication::translate("DialogSetting", "\350\204\217\346\261\241", nullptr));
        spinBox_Area_zangwu_2->setSuffix(QString());
        spinBox_Area_zangwu_2->setPrefix(QString());
        spinBox_Wh_zangwu_2->setSuffix(QString());
        spinBox_Wh_zangwu_2->setPrefix(QString());
        label_34->setText(QCoreApplication::translate("DialogSetting", "\345\216\213\344\274\244", nullptr));
        spinBox_Area_yashang->setSuffix(QString());
        spinBox_Area_yashang->setPrefix(QString());
        spinBox_Wh_yashang->setSuffix(QString());
        spinBox_Wh_yashang->setPrefix(QString());
        label_36->setText(QCoreApplication::translate("DialogSetting", "\346\260\264\345\217\243\351\225\277", nullptr));
        spinBox_Area_shuikouchang->setSuffix(QString());
        spinBox_Area_shuikouchang->setPrefix(QString());
        spinBox_Wh_shuikouchang->setSuffix(QString());
        spinBox_Wh_shuikouchang->setPrefix(QString());
        label_33->setText(QCoreApplication::translate("DialogSetting", "\346\260\224\346\263\241", nullptr));
        spinBox_Area_qipao->setSuffix(QString());
        spinBox_Area_qipao->setPrefix(QString());
        spinBox_Wh_qipao->setSuffix(QString());
        spinBox_Wh_qipao->setPrefix(QString());
        label_35->setText(QCoreApplication::translate("DialogSetting", "\350\203\266\345\216\213\344\274\244", nullptr));
        spinBox_Area_yajiaoshang_2->setSuffix(QString());
        spinBox_Area_yajiaoshang_2->setPrefix(QString());
        spinBox_Wh_yajiaoshang_2->setSuffix(QString());
        spinBox_Wh_yajiaoshang_2->setPrefix(QString());
        label_37->setText(QCoreApplication::translate("DialogSetting", "\346\226\255\344\273\213\345\255\220", nullptr));
        spinBox_Area_duanjiezi->setSuffix(QString());
        spinBox_Area_duanjiezi->setPrefix(QString());
        spinBox_Wh_duanjiezi->setSuffix(QString());
        spinBox_Wh_duanjiezi->setPrefix(QString());
        spinBox_Degree->setTitle(QCoreApplication::translate("DialogSetting", "\344\272\214\345\267\245\344\275\215\350\247\222\345\272\246/\345\201\217\344\275\215\351\230\210\345\200\274\350\256\276\347\275\256", nullptr));
        label_19->setText(QCoreApplication::translate("DialogSetting", "\350\247\222\345\272\246\346\255\243\351\230\210\345\200\274", nullptr));
        spinBox_AddDegreeThreshold->setSuffix(QString());
        spinBox_AddDegreeThreshold->setPrefix(QString());
        label_21->setText(QCoreApplication::translate("DialogSetting", "\350\247\222\345\272\246\350\264\237\351\230\210\345\200\274", nullptr));
        spinBox_SubDegreeThreshold->setSuffix(QString());
        spinBox_SubDegreeThreshold->setPrefix(QString());
        label_20->setText(QCoreApplication::translate("DialogSetting", "\345\201\217\344\275\215\351\230\210\345\200\274", nullptr));
        spinBox_Distance->setSuffix(QString());
        spinBox_Distance->setPrefix(QString());
        groupBox_2->setTitle(QCoreApplication::translate("DialogSetting", "\344\270\200\345\267\245\344\275\215\347\274\272\351\231\267\351\230\210\345\200\274\350\256\276\347\275\256", nullptr));
        label_15->setText(QCoreApplication::translate("DialogSetting", "\351\235\242\347\247\257\351\230\210\345\200\274", nullptr));
        label_16->setText(QCoreApplication::translate("DialogSetting", "\351\225\277\345\272\246\351\230\210\345\200\274", nullptr));
        label_18->setText(QCoreApplication::translate("DialogSetting", "\346\256\213\350\203\266", nullptr));
        spinBox_Area_canjiao->setSuffix(QString());
        spinBox_Area_canjiao->setPrefix(QString());
        spinBox_Wh_canjiao->setSuffix(QString());
        spinBox_Wh_canjiao->setPrefix(QString());
        label_14->setText(QCoreApplication::translate("DialogSetting", "\345\210\222\344\274\244", nullptr));
        spinBox_Area_huashang->setSuffix(QString());
        spinBox_Area_huashang->setPrefix(QString());
        spinBox_Wh_huashang->setSuffix(QString());
        spinBox_Wh_huashang->setPrefix(QString());
        label_17->setText(QCoreApplication::translate("DialogSetting", "\350\203\266\345\216\213\344\274\244", nullptr));
        spinBox_Area_yajiaoshang->setSuffix(QString());
        spinBox_Area_yajiaoshang->setPrefix(QString());
        spinBox_Wh_yajiaoshang->setSuffix(QString());
        spinBox_Wh_yajiaoshang->setPrefix(QString());
        label_13->setText(QCoreApplication::translate("DialogSetting", "\350\204\217\346\261\241", nullptr));
        spinBox_Area_zangwu->setSuffix(QString());
        spinBox_Area_zangwu->setPrefix(QString());
        spinBox_Wh_zangwu->setSuffix(QString());
        spinBox_Wh_zangwu->setPrefix(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogSetting: public Ui_DialogSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERSETTING_H
