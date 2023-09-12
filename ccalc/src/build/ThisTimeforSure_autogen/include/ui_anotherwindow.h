/********************************************************************************
** Form generated from reading UI file 'anotherwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANOTHERWINDOW_H
#define UI_ANOTHERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include "anotherwindow.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_AnotherWindow
{
public:
    QCustomPlot *AnotherWindow_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QPushButton *Close;
    QLineEdit *ErrorWindow;

    void setupUi(AnotherWindow *AnotherWindow)
    {
        if (AnotherWindow->objectName().isEmpty())
            AnotherWindow->setObjectName(QString::fromUtf8("AnotherWindow"));
        AnotherWindow->resize(800, 600);
        AnotherWindow_2 = new QCustomPlot(AnotherWindow);
        AnotherWindow_2->setObjectName(QString::fromUtf8("AnotherWindow_2"));
        AnotherWindow_2->setGeometry(QRect(0, 0, 801, 541));
        menubar = new QMenuBar(AnotherWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        statusbar = new QStatusBar(AnotherWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 27));
        Close = new QPushButton(AnotherWindow);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setGeometry(QRect(650, 550, 100, 32));
        ErrorWindow = new QLineEdit(AnotherWindow);
        ErrorWindow->setObjectName(QString::fromUtf8("ErrorWindow"));
        ErrorWindow->setGeometry(QRect(130, 560, 151, 31));

        retranslateUi(AnotherWindow);

        QMetaObject::connectSlotsByName(AnotherWindow);
    } // setupUi

    void retranslateUi(AnotherWindow *AnotherWindow)
    {
        AnotherWindow->setWindowTitle(QCoreApplication::translate("AnotherWindow", "MainWindow", nullptr));
        Close->setText(QCoreApplication::translate("AnotherWindow", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnotherWindow: public Ui_AnotherWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANOTHERWINDOW_H
