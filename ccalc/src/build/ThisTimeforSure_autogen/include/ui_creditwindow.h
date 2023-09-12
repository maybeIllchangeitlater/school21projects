/********************************************************************************
** Form generated from reading UI file 'creditwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITWINDOW_H
#define UI_CREDITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include "creditwindow.h"

QT_BEGIN_NAMESPACE

class Ui_CreditWindow
{
public:
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QPushButton *exit;
    QLabel *label;
    QLineEdit *total_credit;
    QLineEdit *percentage;
    QLabel *label_2;
    QLineEdit *term;
    QLabel *label_3;
    QLineEdit *type;
    QLabel *label_4;
    QPushButton *Cal;
    QLineEdit *Total_payment;
    QLineEdit *Overpay;
    QLabel *label_6;
    QLineEdit *Monthly;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(CreditWindow *CreditWindow)
    {
        if (CreditWindow->objectName().isEmpty())
            CreditWindow->setObjectName(QString::fromUtf8("CreditWindow"));
        CreditWindow->resize(800, 600);
        menubar = new QMenuBar(CreditWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        statusbar = new QStatusBar(CreditWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 27));
        exit = new QPushButton(CreditWindow);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(680, 10, 100, 32));
        label = new QLabel(CreditWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 50, 251, 51));
        QFont font;
        font.setPointSize(25);
        label->setFont(font);
        total_credit = new QLineEdit(CreditWindow);
        total_credit->setObjectName(QString::fromUtf8("total_credit"));
        total_credit->setGeometry(QRect(290, 60, 211, 31));
        percentage = new QLineEdit(CreditWindow);
        percentage->setObjectName(QString::fromUtf8("percentage"));
        percentage->setGeometry(QRect(290, 90, 211, 31));
        label_2 = new QLabel(CreditWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 80, 251, 51));
        label_2->setFont(font);
        term = new QLineEdit(CreditWindow);
        term->setObjectName(QString::fromUtf8("term"));
        term->setGeometry(QRect(290, 120, 211, 31));
        label_3 = new QLabel(CreditWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 110, 251, 51));
        label_3->setFont(font);
        type = new QLineEdit(CreditWindow);
        type->setObjectName(QString::fromUtf8("type"));
        type->setGeometry(QRect(290, 150, 211, 31));
        QFont font1;
        font1.setPointSize(16);
        type->setFont(font1);
        label_4 = new QLabel(CreditWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 140, 251, 51));
        label_4->setFont(font);
        Cal = new QPushButton(CreditWindow);
        Cal->setObjectName(QString::fromUtf8("Cal"));
        Cal->setGeometry(QRect(580, 540, 211, 51));
        QFont font2;
        font2.setPointSize(20);
        Cal->setFont(font2);
        Total_payment = new QLineEdit(CreditWindow);
        Total_payment->setObjectName(QString::fromUtf8("Total_payment"));
        Total_payment->setGeometry(QRect(290, 270, 211, 31));
        Overpay = new QLineEdit(CreditWindow);
        Overpay->setObjectName(QString::fromUtf8("Overpay"));
        Overpay->setGeometry(QRect(290, 240, 211, 31));
        label_6 = new QLabel(CreditWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 260, 251, 51));
        label_6->setFont(font);
        Monthly = new QLineEdit(CreditWindow);
        Monthly->setObjectName(QString::fromUtf8("Monthly"));
        Monthly->setGeometry(QRect(290, 210, 211, 31));
        label_7 = new QLabel(CreditWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 230, 251, 51));
        label_7->setFont(font);
        label_8 = new QLabel(CreditWindow);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(60, 200, 251, 51));
        label_8->setFont(font);
        label_9 = new QLabel(CreditWindow);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(530, 140, 271, 41));
        label_9->setFont(font1);

        retranslateUi(CreditWindow);

        QMetaObject::connectSlotsByName(CreditWindow);
    } // setupUi

    void retranslateUi(CreditWindow *CreditWindow)
    {
        CreditWindow->setWindowTitle(QCoreApplication::translate("CreditWindow", "MainWindow", nullptr));
        exit->setText(QCoreApplication::translate("CreditWindow", "Close", nullptr));
        label->setText(QCoreApplication::translate("CreditWindow", "Total Credit Amount", nullptr));
        label_2->setText(QCoreApplication::translate("CreditWindow", "Interest Rate", nullptr));
        label_3->setText(QCoreApplication::translate("CreditWindow", "Term", nullptr));
        type->setText(QCoreApplication::translate("CreditWindow", "1", nullptr));
        label_4->setText(QCoreApplication::translate("CreditWindow", "Type", nullptr));
        Cal->setText(QCoreApplication::translate("CreditWindow", "CALCULATE", nullptr));
        label_6->setText(QCoreApplication::translate("CreditWindow", "Total Payment", nullptr));
        label_7->setText(QCoreApplication::translate("CreditWindow", "Overpayment", nullptr));
        label_8->setText(QCoreApplication::translate("CreditWindow", "Monthly Payment", nullptr));
        label_9->setText(QCoreApplication::translate("CreditWindow", "1 - Annual, 2 - differentiated", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreditWindow: public Ui_CreditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITWINDOW_H
