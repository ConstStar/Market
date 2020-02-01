/********************************************************************************
** Form generated from reading UI file 'WEmailList.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEMAILLIST_H
#define UI_WEMAILLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WEmailList
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *label_9;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *edit_email;
    QLabel *label_5;
    QLineEdit *edit_passwd;
    QLabel *label_2;
    QLineEdit *edit_smtp;
    QLabel *label_3;
    QLineEdit *edit_port;
    QCheckBox *check_ssl;
    QLabel *label_6;
    QLineEdit *edit_dayMax;
    QPushButton *button_add;
    QGridLayout *gridLayout;
    QPushButton *button_fromFile;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QPushButton *button_outFile;

    void setupUi(QWidget *WEmailList)
    {
        if (WEmailList->objectName().isEmpty())
            WEmailList->setObjectName(QString::fromUtf8("WEmailList"));
        WEmailList->resize(894, 482);
        verticalLayout = new QVBoxLayout(WEmailList);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(WEmailList);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_7 = new QLabel(WEmailList);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        label_9 = new QLabel(WEmailList);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);


        verticalLayout->addLayout(horizontalLayout_3);

        tableView = new QTableView(WEmailList);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(WEmailList);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        edit_email = new QLineEdit(WEmailList);
        edit_email->setObjectName(QString::fromUtf8("edit_email"));

        horizontalLayout->addWidget(edit_email);

        label_5 = new QLabel(WEmailList);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        edit_passwd = new QLineEdit(WEmailList);
        edit_passwd->setObjectName(QString::fromUtf8("edit_passwd"));

        horizontalLayout->addWidget(edit_passwd);

        label_2 = new QLabel(WEmailList);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        edit_smtp = new QLineEdit(WEmailList);
        edit_smtp->setObjectName(QString::fromUtf8("edit_smtp"));
        edit_smtp->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(edit_smtp);

        label_3 = new QLabel(WEmailList);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        edit_port = new QLineEdit(WEmailList);
        edit_port->setObjectName(QString::fromUtf8("edit_port"));
        edit_port->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(edit_port);

        check_ssl = new QCheckBox(WEmailList);
        check_ssl->setObjectName(QString::fromUtf8("check_ssl"));

        horizontalLayout->addWidget(check_ssl);

        label_6 = new QLabel(WEmailList);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        edit_dayMax = new QLineEdit(WEmailList);
        edit_dayMax->setObjectName(QString::fromUtf8("edit_dayMax"));
        edit_dayMax->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(edit_dayMax);

        button_add = new QPushButton(WEmailList);
        button_add->setObjectName(QString::fromUtf8("button_add"));

        horizontalLayout->addWidget(button_add);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        button_fromFile = new QPushButton(WEmailList);
        button_fromFile->setObjectName(QString::fromUtf8("button_fromFile"));
        button_fromFile->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(button_fromFile, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_8 = new QLabel(WEmailList);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(label_8);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 2, 1);

        button_outFile = new QPushButton(WEmailList);
        button_outFile->setObjectName(QString::fromUtf8("button_outFile"));
        button_outFile->setEnabled(true);
        button_outFile->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(button_outFile, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(WEmailList);

        QMetaObject::connectSlotsByName(WEmailList);
    } // setupUi

    void retranslateUi(QWidget *WEmailList)
    {
        WEmailList->setWindowTitle(QCoreApplication::translate("WEmailList", "SMTP\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("WEmailList", "\351\202\256\347\256\261\345\210\227\350\241\250(\345\217\214\345\207\273\347\274\226\350\276\221)", nullptr));
        label_7->setText(QCoreApplication::translate("WEmailList", "\345\274\200\345\220\257\345\244\232\344\270\252\351\202\256\347\256\261\346\227\266\345\260\206\350\275\256\346\265\201\344\275\277\347\224\250", nullptr));
        label_9->setText(QCoreApplication::translate("WEmailList", "<html><head/><body><p><span style=\" color:#0000ff;\">\345\275\223\346\227\245\351\231\220(\345\215\225\344\270\252\350\264\246\345\217\267\345\217\221\351\200\201\346\227\245\351\231\220\345\210\266\346\254\241\346\225\260)\344\270\2720\346\227\266\345\210\231\344\270\215\345\201\232\351\231\220\345\210\266</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("WEmailList", "\351\202\256\347\256\261:", nullptr));
        label_5->setText(QCoreApplication::translate("WEmailList", "\345\257\206\347\240\201:", nullptr));
        label_2->setText(QCoreApplication::translate("WEmailList", "SMTP\345\234\260\345\235\200:", nullptr));
        label_3->setText(QCoreApplication::translate("WEmailList", "\347\253\257\345\217\243:", nullptr));
        check_ssl->setText(QCoreApplication::translate("WEmailList", "SSL", nullptr));
        label_6->setText(QCoreApplication::translate("WEmailList", "\346\227\245\351\231\220:", nullptr));
        button_add->setText(QCoreApplication::translate("WEmailList", "\346\267\273\345\212\240", nullptr));
        button_fromFile->setText(QCoreApplication::translate("WEmailList", "\344\273\216\346\226\207\344\273\266\344\270\255\345\257\274\345\205\245", nullptr));
        label_8->setText(QCoreApplication::translate("WEmailList", "\344\273\216\346\226\207\344\273\266\344\270\255\345\257\274\345\205\245\347\232\204\346\240\274\345\274\217: \351\202\256\347\256\261----\345\257\206\347\240\201----SMTP----\347\253\257\345\217\243----\346\230\257\345\220\246SSL(true/false)----\346\227\245\351\231\220(\345\217\257\345\277\275\347\225\245)\n"
"\345\246\202:xxxx@qq.com----xxxxx----smtp.qq.com----25----false----20\n"
"\346\210\226\350\200\205:xxxx@qq.com----xxxxx----smtp.qq.com----25----false", nullptr));
        button_outFile->setText(QCoreApplication::translate("WEmailList", "\345\205\250\351\203\250\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WEmailList: public Ui_WEmailList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEMAILLIST_H
