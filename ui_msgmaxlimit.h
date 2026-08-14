/********************************************************************************
** Form generated from reading UI file 'msgmaxlimit.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGMAXLIMIT_H
#define UI_MSGMAXLIMIT_H

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

class Ui_msgmaxlimit
{
public:
    QWidget *centralwidget;
    QPushButton *btnYes;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *msgmaxlimit)
    {
        if (msgmaxlimit->objectName().isEmpty())
            msgmaxlimit->setObjectName(QStringLiteral("msgmaxlimit"));
        msgmaxlimit->resize(512, 374);
        msgmaxlimit->setStyleSheet(QStringLiteral("background-color: transparent;"));
        centralwidget = new QWidget(msgmaxlimit);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btnYes = new QPushButton(centralwidget);
        btnYes->setObjectName(QStringLiteral("btnYes"));
        btnYes->setGeometry(QRect(170, 70, 191, 181));
        btnYes->setStyleSheet(QLatin1String("background:none;\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/yes.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnYes->setIcon(icon);
        btnYes->setIconSize(QSize(175, 175));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 15, 491, 50));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 511, 331));
        label_2->setStyleSheet(QLatin1String("background-color: rgb(255, 84, 16);\n"
"border-radius: 30px;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 260, 181, 41));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label_4->setAlignment(Qt::AlignCenter);
        msgmaxlimit->setCentralWidget(centralwidget);
        label_2->raise();
        btnYes->raise();
        label->raise();
        label_4->raise();
        menubar = new QMenuBar(msgmaxlimit);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 512, 21));
        msgmaxlimit->setMenuBar(menubar);
        statusbar = new QStatusBar(msgmaxlimit);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        msgmaxlimit->setStatusBar(statusbar);

        retranslateUi(msgmaxlimit);

        QMetaObject::connectSlotsByName(msgmaxlimit);
    } // setupUi

    void retranslateUi(QMainWindow *msgmaxlimit)
    {
        msgmaxlimit->setWindowTitle(QApplication::translate("msgmaxlimit", "MainWindow", nullptr));
        btnYes->setText(QString());
        label->setText(QApplication::translate("msgmaxlimit", "WARNING LIMIT ATAS", nullptr));
        label_2->setText(QString());
        label_4->setText(QApplication::translate("msgmaxlimit", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class msgmaxlimit: public Ui_msgmaxlimit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGMAXLIMIT_H
