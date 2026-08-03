/********************************************************************************
** Form generated from reading UI file 'msglogout.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGLOGOUT_H
#define UI_MSGLOGOUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_msglogout
{
public:
    QWidget *centralwidget;
    QPushButton *btnYes;
    QPushButton *btnNo;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *msglogout)
    {
        if (msglogout->objectName().isEmpty())
            msglogout->setObjectName(QStringLiteral("msglogout"));
        msglogout->resize(512, 374);
        msglogout->setStyleSheet(QStringLiteral("background-color: transparent;"));
        centralwidget = new QWidget(msglogout);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btnYes = new QPushButton(centralwidget);
        btnYes->setObjectName(QStringLiteral("btnYes"));
        btnYes->setGeometry(QRect(280, 70, 191, 181));
        btnYes->setStyleSheet(QLatin1String("background:none;\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/yes.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnYes->setIcon(icon);
        btnYes->setIconSize(QSize(175, 175));
        btnNo = new QPushButton(centralwidget);
        btnNo->setObjectName(QStringLiteral("btnNo"));
        btnNo->setGeometry(QRect(13, 40, 241, 241));
        btnNo->setStyleSheet(QStringLiteral("border:none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/no.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNo->setIcon(icon1);
        btnNo->setIconSize(QSize(175, 175));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 15, 351, 50));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 511, 331));
        label_2->setStyleSheet(QLatin1String("background-color:rgba(128,128,128,0.85);\n"
"border-radius: 30px;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 258, 171, 40));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color: white;"));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(331, 258, 91, 41));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label_4->setAlignment(Qt::AlignCenter);
        msglogout->setCentralWidget(centralwidget);
        label_2->raise();
        btnYes->raise();
        label->raise();
        label_3->raise();
        label_4->raise();
        btnNo->raise();
        menubar = new QMenuBar(msglogout);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 512, 21));
        msglogout->setMenuBar(menubar);
        statusbar = new QStatusBar(msglogout);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        msglogout->setStatusBar(statusbar);

        retranslateUi(msglogout);

        QMetaObject::connectSlotsByName(msglogout);
    } // setupUi

    void retranslateUi(QMainWindow *msglogout)
    {
        msglogout->setWindowTitle(QApplication::translate("msglogout", "MainWindow", nullptr));
        btnYes->setText(QString());
        btnNo->setText(QString());
        label->setText(QApplication::translate("msglogout", "EXIT ?", nullptr));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("msglogout", "CANCEL", nullptr));
        label_4->setText(QApplication::translate("msglogout", "YES", nullptr));
    } // retranslateUi

};

namespace Ui {
    class msglogout: public Ui_msglogout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGLOGOUT_H
