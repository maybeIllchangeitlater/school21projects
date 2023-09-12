/********************************************************************************
** Form generated from reading UI file 'depositcalc.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSITCALC_H
#define UI_DEPOSITCALC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DepositCalc
{
public:
    QLabel *replenishment;
    QLabel *withdrawal;
    QLineEdit *replenishment_in;
    QLineEdit *withdrawal_in;
    QLabel *pereodicity;
    QLineEdit *pereodicity_in;
    QLineEdit *capitalization_in;
    QLabel *capitalization;
    QLineEdit *deposit_term_in;
    QLabel *interest_rate;
    QLineEdit *interest_in;
    QLabel *pereodicity_2;
    QLabel *capitalization_2;
    QLineEdit *tax_in;
    QLabel *tax_rate;
    QLineEdit *deposit_in;
    QPushButton *rep_add;
    QPushButton *with_add;
    QLineEdit *aquired_interest;
    QLabel *replenishment_2;
    QLineEdit *tax_amount;
    QLabel *capitalization_3;
    QLineEdit *deposit_amount;
    QLabel *withdrawal_2;
    QPushButton *close;
    QPushButton *calc;
    QLabel *withdrawal_counter;
    QLabel *replenishment_counter;

    void setupUi(QWidget *DepositCalc)
    {
        if (DepositCalc->objectName().isEmpty())
            DepositCalc->setObjectName(QString::fromUtf8("DepositCalc"));
        DepositCalc->resize(800, 600);
        replenishment = new QLabel(DepositCalc);
        replenishment->setObjectName(QString::fromUtf8("replenishment"));
        replenishment->setGeometry(QRect(10, 280, 171, 41));
        QFont font;
        font.setPointSize(20);
        replenishment->setFont(font);
        withdrawal = new QLabel(DepositCalc);
        withdrawal->setObjectName(QString::fromUtf8("withdrawal"));
        withdrawal->setGeometry(QRect(10, 310, 171, 41));
        withdrawal->setFont(font);
        replenishment_in = new QLineEdit(DepositCalc);
        replenishment_in->setObjectName(QString::fromUtf8("replenishment_in"));
        replenishment_in->setGeometry(QRect(180, 290, 151, 21));
        withdrawal_in = new QLineEdit(DepositCalc);
        withdrawal_in->setObjectName(QString::fromUtf8("withdrawal_in"));
        withdrawal_in->setGeometry(QRect(180, 320, 151, 21));
        pereodicity = new QLabel(DepositCalc);
        pereodicity->setObjectName(QString::fromUtf8("pereodicity"));
        pereodicity->setGeometry(QRect(10, 220, 171, 41));
        pereodicity->setFont(font);
        pereodicity_in = new QLineEdit(DepositCalc);
        pereodicity_in->setObjectName(QString::fromUtf8("pereodicity_in"));
        pereodicity_in->setGeometry(QRect(180, 230, 151, 21));
        capitalization_in = new QLineEdit(DepositCalc);
        capitalization_in->setObjectName(QString::fromUtf8("capitalization_in"));
        capitalization_in->setGeometry(QRect(180, 260, 151, 21));
        capitalization = new QLabel(DepositCalc);
        capitalization->setObjectName(QString::fromUtf8("capitalization"));
        capitalization->setGeometry(QRect(10, 250, 171, 41));
        capitalization->setFont(font);
        deposit_term_in = new QLineEdit(DepositCalc);
        deposit_term_in->setObjectName(QString::fromUtf8("deposit_term_in"));
        deposit_term_in->setGeometry(QRect(180, 140, 151, 21));
        interest_rate = new QLabel(DepositCalc);
        interest_rate->setObjectName(QString::fromUtf8("interest_rate"));
        interest_rate->setGeometry(QRect(10, 160, 171, 41));
        interest_rate->setFont(font);
        interest_in = new QLineEdit(DepositCalc);
        interest_in->setObjectName(QString::fromUtf8("interest_in"));
        interest_in->setGeometry(QRect(180, 170, 151, 21));
        pereodicity_2 = new QLabel(DepositCalc);
        pereodicity_2->setObjectName(QString::fromUtf8("pereodicity_2"));
        pereodicity_2->setGeometry(QRect(10, 100, 171, 41));
        pereodicity_2->setFont(font);
        capitalization_2 = new QLabel(DepositCalc);
        capitalization_2->setObjectName(QString::fromUtf8("capitalization_2"));
        capitalization_2->setGeometry(QRect(10, 130, 171, 41));
        capitalization_2->setFont(font);
        tax_in = new QLineEdit(DepositCalc);
        tax_in->setObjectName(QString::fromUtf8("tax_in"));
        tax_in->setGeometry(QRect(180, 200, 151, 21));
        tax_rate = new QLabel(DepositCalc);
        tax_rate->setObjectName(QString::fromUtf8("tax_rate"));
        tax_rate->setGeometry(QRect(10, 190, 171, 41));
        tax_rate->setFont(font);
        deposit_in = new QLineEdit(DepositCalc);
        deposit_in->setObjectName(QString::fromUtf8("deposit_in"));
        deposit_in->setGeometry(QRect(180, 110, 151, 21));
        rep_add = new QPushButton(DepositCalc);
        rep_add->setObjectName(QString::fromUtf8("rep_add"));
        rep_add->setGeometry(QRect(340, 290, 100, 21));
        with_add = new QPushButton(DepositCalc);
        with_add->setObjectName(QString::fromUtf8("with_add"));
        with_add->setGeometry(QRect(340, 320, 100, 21));
        aquired_interest = new QLineEdit(DepositCalc);
        aquired_interest->setObjectName(QString::fromUtf8("aquired_interest"));
        aquired_interest->setGeometry(QRect(180, 460, 151, 21));
        replenishment_2 = new QLabel(DepositCalc);
        replenishment_2->setObjectName(QString::fromUtf8("replenishment_2"));
        replenishment_2->setGeometry(QRect(40, 480, 171, 41));
        replenishment_2->setFont(font);
        tax_amount = new QLineEdit(DepositCalc);
        tax_amount->setObjectName(QString::fromUtf8("tax_amount"));
        tax_amount->setGeometry(QRect(180, 490, 151, 21));
        capitalization_3 = new QLabel(DepositCalc);
        capitalization_3->setObjectName(QString::fromUtf8("capitalization_3"));
        capitalization_3->setGeometry(QRect(40, 450, 171, 41));
        capitalization_3->setFont(font);
        deposit_amount = new QLineEdit(DepositCalc);
        deposit_amount->setObjectName(QString::fromUtf8("deposit_amount"));
        deposit_amount->setGeometry(QRect(180, 520, 151, 21));
        withdrawal_2 = new QLabel(DepositCalc);
        withdrawal_2->setObjectName(QString::fromUtf8("withdrawal_2"));
        withdrawal_2->setGeometry(QRect(40, 510, 171, 41));
        withdrawal_2->setFont(font);
        close = new QPushButton(DepositCalc);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(619, 20, 141, 21));
        calc = new QPushButton(DepositCalc);
        calc->setObjectName(QString::fromUtf8("calc"));
        calc->setGeometry(QRect(580, 480, 171, 61));
        calc->setFont(font);
        withdrawal_counter = new QLabel(DepositCalc);
        withdrawal_counter->setObjectName(QString::fromUtf8("withdrawal_counter"));
        withdrawal_counter->setGeometry(QRect(110, 310, 171, 41));
        withdrawal_counter->setFont(font);
        replenishment_counter = new QLabel(DepositCalc);
        replenishment_counter->setObjectName(QString::fromUtf8("replenishment_counter"));
        replenishment_counter->setGeometry(QRect(140, 280, 171, 41));
        replenishment_counter->setFont(font);

        retranslateUi(DepositCalc);

        QMetaObject::connectSlotsByName(DepositCalc);
    } // setupUi

    void retranslateUi(QWidget *DepositCalc)
    {
        DepositCalc->setWindowTitle(QCoreApplication::translate("DepositCalc", "Form", nullptr));
        replenishment->setText(QCoreApplication::translate("DepositCalc", "replenishment", nullptr));
        withdrawal->setText(QCoreApplication::translate("DepositCalc", "withdrawal", nullptr));
        pereodicity->setText(QCoreApplication::translate("DepositCalc", "pereodicity", nullptr));
        capitalization->setText(QCoreApplication::translate("DepositCalc", "capitalization", nullptr));
        interest_rate->setText(QCoreApplication::translate("DepositCalc", "interest rate", nullptr));
        pereodicity_2->setText(QCoreApplication::translate("DepositCalc", "deposit amount", nullptr));
        capitalization_2->setText(QCoreApplication::translate("DepositCalc", "deposit term", nullptr));
        tax_rate->setText(QCoreApplication::translate("DepositCalc", "tax rate", nullptr));
        rep_add->setText(QCoreApplication::translate("DepositCalc", "ADD", nullptr));
        with_add->setText(QCoreApplication::translate("DepositCalc", "ADD", nullptr));
        replenishment_2->setText(QCoreApplication::translate("DepositCalc", "tax amount", nullptr));
        capitalization_3->setText(QCoreApplication::translate("DepositCalc", "aquired interest", nullptr));
        withdrawal_2->setText(QCoreApplication::translate("DepositCalc", "deposit amount", nullptr));
        close->setText(QCoreApplication::translate("DepositCalc", "Close", nullptr));
        calc->setText(QCoreApplication::translate("DepositCalc", "CALCULATE", nullptr));
        withdrawal_counter->setText(QCoreApplication::translate("DepositCalc", "1", nullptr));
        replenishment_counter->setText(QCoreApplication::translate("DepositCalc", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DepositCalc: public Ui_DepositCalc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSITCALC_H
