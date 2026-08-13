/********************************************************************************
** Form generated from reading UI file 'msgisinamadulu.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGISINAMADULU_H
#define UI_MSGISINAMADULU_H

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

class Ui_msgisinamadulu
{
public:
    QWidget *centralwidget;
    QPushButton *btnYes;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *msgisinamadulu)
    {
        if (msgisinamadulu->objectName().isEmpty())
            msgisinamadulu->setObjectName(QStringLiteral("msgisinamadulu"));
        msgisinamadulu->resize(512, 374);
        msgisinamadulu->setStyleSheet(QStringLiteral("background-color: transparent;"));
        centralwidget = new QWidget(msgisinamadulu);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btnYes = new QPushButton(centralwidget);
        btnYes->setObjectName(QStringLiteral("btnYes"));
        btnYes->setGeometry(QRect(150, 70, 191, 181));
        btnYes->setStyleSheet(QLatin1String("background:none;\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/yes.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnYes->setIcon(icon);
        btnYes->setIconSize(QSize(175, 175));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 20, 351, 50));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 511, 331));
        label_2->setStyleSheet(QLatin1String("background-color:rgba(128,128,128,0.85);\n"
"border-radius: 30px;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(200, 250, 91, 41));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label_4->setAlignment(Qt::AlignCenter);
        msgisinamadulu->setCentralWidget(centralwidget);
        label_2->raise();
        btnYes->raise();
        label->raise();
        label_4->raise();
        menubar = new QMenuBar(msgisinamadulu);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 512, 21));
        msgisinamadulu->setMenuBar(menubar);
        statusbar = new QStatusBar(msgisinamadulu);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        msgisinamadulu->setStatusBar(statusbar);

        retranslateUi(msgisinamadulu);

        QMetaObject::connectSlotsByName(msgisinamadulu);
    } // setupUi

    void retranslateUi(QMainWindow *msgisinamadulu)
    {
        msgisinamadulu->setWindowTitle(QApplication::translate("msgisinamadulu", "MainWindow", nullptr));
        btnYes->setText(QString());
        label->setText(QApplication::translate("msgisinamadulu", "ISI NAMA DULU", nullptr));
        label_2->setText(QString());
        label_4->setText(QApplication::translate("msgisinamadulu", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class msgisinamadulu: public Ui_msgisinamadulu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGISINAMADULU_H
