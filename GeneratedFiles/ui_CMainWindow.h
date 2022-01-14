/********************************************************************************
** Form generated from reading UI file 'CMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_CMainWindowClass
{
public:
    QAction *action_Start;
    QAction *action_Stop;
    QAction *action_Setting;
    QAction *action_Reset;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_First;
    QGridLayout *gridLayout;
    QLabel *label_FirstTime;
    QLabel *label_FirstIndex;
    QLabel *label_FirstResult;
    MyLabel *label_FirstImage;
    QGroupBox *groupBox_Second;
    QGridLayout *gridLayout_2;
    QLabel *label_SecondTime;
    QLabel *label_SecondIndex;
    QLabel *label_SecondResult;
    MyLabel *label_SecondImage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindowClass)
    {
        if (CMainWindowClass->objectName().isEmpty())
            CMainWindowClass->setObjectName(QString::fromUtf8("CMainWindowClass"));
        CMainWindowClass->resize(1340, 834);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CMainWindow/Resources/app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CMainWindowClass->setWindowIcon(icon);
        CMainWindowClass->setStyleSheet(QString::fromUtf8(""));
        action_Start = new QAction(CMainWindowClass);
        action_Start->setObjectName(QString::fromUtf8("action_Start"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/CMainWindow/Resources/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Start->setIcon(icon1);
        action_Stop = new QAction(CMainWindowClass);
        action_Stop->setObjectName(QString::fromUtf8("action_Stop"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/CMainWindow/Resources/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Stop->setIcon(icon2);
        action_Setting = new QAction(CMainWindowClass);
        action_Setting->setObjectName(QString::fromUtf8("action_Setting"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/CMainWindow/Resources/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Setting->setIcon(icon3);
        action_Reset = new QAction(CMainWindowClass);
        action_Reset->setObjectName(QString::fromUtf8("action_Reset"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/CMainWindow/Resources/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Reset->setIcon(icon4);
        centralWidget = new QWidget(CMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_First = new QGroupBox(centralWidget);
        groupBox_First->setObjectName(QString::fromUtf8("groupBox_First"));
        groupBox_First->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout = new QGridLayout(groupBox_First);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_FirstTime = new QLabel(groupBox_First);
        label_FirstTime->setObjectName(QString::fromUtf8("label_FirstTime"));
        label_FirstTime->setMaximumSize(QSize(16777215, 51));
        label_FirstTime->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);"));

        gridLayout->addWidget(label_FirstTime, 0, 0, 1, 1);

        label_FirstIndex = new QLabel(groupBox_First);
        label_FirstIndex->setObjectName(QString::fromUtf8("label_FirstIndex"));
        label_FirstIndex->setMaximumSize(QSize(16777215, 51));
        label_FirstIndex->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);"));

        gridLayout->addWidget(label_FirstIndex, 0, 1, 1, 1);

        label_FirstResult = new QLabel(groupBox_First);
        label_FirstResult->setObjectName(QString::fromUtf8("label_FirstResult"));
        label_FirstResult->setMaximumSize(QSize(150, 51));
        label_FirstResult->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);\n"
"image: url(:/CMainWindow/Resources/OK.svg);"));

        gridLayout->addWidget(label_FirstResult, 0, 2, 1, 1);

        label_FirstImage = new MyLabel(groupBox_First);
        label_FirstImage->setObjectName(QString::fromUtf8("label_FirstImage"));
        label_FirstImage->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout->addWidget(label_FirstImage, 1, 0, 1, 3);


        gridLayout_3->addWidget(groupBox_First, 0, 0, 1, 1);

        groupBox_Second = new QGroupBox(centralWidget);
        groupBox_Second->setObjectName(QString::fromUtf8("groupBox_Second"));
        groupBox_Second->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout_2 = new QGridLayout(groupBox_Second);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_SecondTime = new QLabel(groupBox_Second);
        label_SecondTime->setObjectName(QString::fromUtf8("label_SecondTime"));
        label_SecondTime->setMaximumSize(QSize(16777215, 51));
        label_SecondTime->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);"));

        gridLayout_2->addWidget(label_SecondTime, 0, 0, 1, 1);

        label_SecondIndex = new QLabel(groupBox_Second);
        label_SecondIndex->setObjectName(QString::fromUtf8("label_SecondIndex"));
        label_SecondIndex->setMaximumSize(QSize(16777215, 51));
        label_SecondIndex->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);"));

        gridLayout_2->addWidget(label_SecondIndex, 0, 1, 1, 1);

        label_SecondResult = new QLabel(groupBox_Second);
        label_SecondResult->setObjectName(QString::fromUtf8("label_SecondResult"));
        label_SecondResult->setMaximumSize(QSize(150, 51));
        label_SecondResult->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(85, 0, 255);\n"
"image: url(:/CMainWindow/Resources/NG.svg);"));

        gridLayout_2->addWidget(label_SecondResult, 0, 2, 1, 1);

        label_SecondImage = new MyLabel(groupBox_Second);
        label_SecondImage->setObjectName(QString::fromUtf8("label_SecondImage"));
        label_SecondImage->setStyleSheet(QString::fromUtf8("background-image: url(:/CMainWindow/Resources/background.png);"));

        gridLayout_2->addWidget(label_SecondImage, 1, 0, 1, 3);


        gridLayout_3->addWidget(groupBox_Second, 0, 1, 1, 1);

        CMainWindowClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(CMainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(50, 50));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        CMainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CMainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CMainWindowClass->setStatusBar(statusBar);

        mainToolBar->addAction(action_Start);
        mainToolBar->addAction(action_Stop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Setting);
        mainToolBar->addAction(action_Reset);

        retranslateUi(CMainWindowClass);

        QMetaObject::connectSlotsByName(CMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindowClass)
    {
        CMainWindowClass->setWindowTitle(QCoreApplication::translate("CMainWindowClass", "\344\273\213\345\255\220\347\274\272\351\231\267\346\243\200\346\265\213\350\275\257\344\273\266_V1.0.0", nullptr));
        action_Start->setText(QCoreApplication::translate("CMainWindowClass", "\345\274\200\345\247\213\350\277\220\350\241\214", nullptr));
        action_Stop->setText(QCoreApplication::translate("CMainWindowClass", "\345\201\234\346\255\242\350\277\220\350\241\214", nullptr));
        action_Setting->setText(QCoreApplication::translate("CMainWindowClass", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        action_Reset->setText(QCoreApplication::translate("CMainWindowClass", "\347\273\237\350\256\241\351\207\215\347\275\256", nullptr));
        groupBox_First->setTitle(QCoreApplication::translate("CMainWindowClass", "\344\270\200\345\267\245\344\275\215", nullptr));
        label_FirstTime->setText(QCoreApplication::translate("CMainWindowClass", "\350\200\227\346\227\266\357\274\232", nullptr));
        label_FirstIndex->setText(QCoreApplication::translate("CMainWindowClass", "\345\272\217\345\217\267\357\274\232", nullptr));
        label_FirstResult->setText(QString());
        label_FirstImage->setText(QString());
        groupBox_Second->setTitle(QCoreApplication::translate("CMainWindowClass", "\344\272\214\345\267\245\344\275\215", nullptr));
        label_SecondTime->setText(QCoreApplication::translate("CMainWindowClass", "\350\200\227\346\227\266\357\274\232", nullptr));
        label_SecondIndex->setText(QCoreApplication::translate("CMainWindowClass", "\345\272\217\345\217\267\357\274\232", nullptr));
        label_SecondResult->setText(QString());
        label_SecondImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CMainWindowClass: public Ui_CMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
