/********************************************************************************
** Form generated from reading UI file 'msgtargetercapai.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGTARGETERCAPAI_H
#define UI_MSGTARGETERCAPAI_H

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

class Ui_msgtargetercapai
{
public:
    QWidget *centralwidget;
    QPushButton *btnYes;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *btnResume;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *msgtargetercapai)
    {
        if (msgtargetercapai->objectName().isEmpty())
            msgtargetercapai->setObjectName(QStringLiteral("msgtargetercapai"));
        msgtargetercapai->resize(512, 374);
        msgtargetercapai->setStyleSheet(QStringLiteral("background-color: transparent;"));
        centralwidget = new QWidget(msgtargetercapai);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btnYes = new QPushButton(centralwidget);
        btnYes->setObjectName(QStringLiteral("btnYes"));
        btnYes->setGeometry(QRect(290, 70, 191, 181));
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
        label_2->setStyleSheet(QLatin1String("background-color:rgba(128,128,128,0.85);\n"
"border-radius: 30px;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(290, 260, 181, 41));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label_4->setAlignment(Qt::AlignCenter);
        btnResume = new QPushButton(centralwidget);
        btnResume->setObjectName(QStringLiteral("btnResume"));
        btnResume->setGeometry(QRect(0, 40, 241, 241));
        btnResume->setStyleSheet(QStringLiteral("border:none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/resume1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnResume->setIcon(icon1);
        btnResume->setIconSize(QSize(175, 175));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 260, 181, 41));
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setStyleSheet(QLatin1String("font: 75 32pt \"Roboto Black\";\n"
"color:white;"));
        label_5->setAlignment(Qt::AlignCenter);
        msgtargetercapai->setCentralWidget(centralwidget);
        label_2->raise();
        btnYes->raise();
        label->raise();
        label_4->raise();
        btnResume->raise();
        label_5->raise();
        menubar = new QMenuBar(msgtargetercapai);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 512, 21));
        msgtargetercapai->setMenuBar(menubar);
        statusbar = new QStatusBar(msgtargetercapai);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        msgtargetercapai->setStatusBar(statusbar);

        retranslateUi(msgtargetercapai);

        QMetaObject::connectSlotsByName(msgtargetercapai);
    } // setupUi

    void retranslateUi(QMainWindow *msgtargetercapai)
    {
        msgtargetercapai->setWindowTitle(QApplication::translate("msgtargetercapai", "MainWindow", nullptr));
        btnYes->setText(QString());
        label->setText(QApplication::translate("msgtargetercapai", "TARGET TERCAPAI", nullptr));
        label_2->setText(QString());
        label_4->setText(QApplication::translate("msgtargetercapai", "SELESAI", nullptr));
        btnResume->setText(QString());
        label_5->setText(QApplication::translate("msgtargetercapai", "RESUME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class msgtargetercapai: public Ui_msgtargetercapai {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGTARGETERCAPAI_H
