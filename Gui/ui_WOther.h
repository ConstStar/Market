/********************************************************************************
** Form generated from reading UI file 'WOther.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WOTHER_H
#define UI_WOTHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WOther
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QCheckBox *check_useHtml;
    QCheckBox *check_addGroupInto;
    QCheckBox *check_addFriend;
    QCheckBox *check_quitGroupSend;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *button_save;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *WOther)
    {
        if (WOther->objectName().isEmpty())
            WOther->setObjectName(QString::fromUtf8("WOther"));
        WOther->resize(355, 118);
        verticalLayout = new QVBoxLayout(WOther);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        check_useHtml = new QCheckBox(WOther);
        check_useHtml->setObjectName(QString::fromUtf8("check_useHtml"));

        gridLayout->addWidget(check_useHtml, 1, 1, 1, 1);

        check_addGroupInto = new QCheckBox(WOther);
        check_addGroupInto->setObjectName(QString::fromUtf8("check_addGroupInto"));

        gridLayout->addWidget(check_addGroupInto, 0, 0, 1, 1);

        check_addFriend = new QCheckBox(WOther);
        check_addFriend->setObjectName(QString::fromUtf8("check_addFriend"));

        gridLayout->addWidget(check_addFriend, 1, 0, 1, 1);

        check_quitGroupSend = new QCheckBox(WOther);
        check_quitGroupSend->setObjectName(QString::fromUtf8("check_quitGroupSend"));

        gridLayout->addWidget(check_quitGroupSend, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        button_save = new QPushButton(WOther);
        button_save->setObjectName(QString::fromUtf8("button_save"));
        button_save->setMinimumSize(QSize(120, 40));

        horizontalLayout_3->addWidget(button_save);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(WOther);

        QMetaObject::connectSlotsByName(WOther);
    } // setupUi

    void retranslateUi(QWidget *WOther)
    {
        WOther->setWindowTitle(QCoreApplication::translate("WOther", "\345\205\266\344\273\226\350\256\276\347\275\256", nullptr));
        check_useHtml->setText(QCoreApplication::translate("WOther", "\344\275\277\347\224\250HTML\351\202\256\344\273\266", nullptr));
        check_addGroupInto->setText(QCoreApplication::translate("WOther", "\350\207\252\345\212\250\345\220\214\346\204\217\345\205\245\347\276\244\351\202\200\350\257\267", nullptr));
        check_addFriend->setText(QCoreApplication::translate("WOther", "\350\207\252\345\212\250\345\220\214\346\204\217\345\245\275\345\217\213\350\257\267\346\261\202", nullptr));
        check_quitGroupSend->setText(QCoreApplication::translate("WOther", "\346\210\220\345\221\230\351\200\200\347\276\244\344\271\237\344\274\232\345\217\221\351\200\201\351\202\256\344\273\266", nullptr));
        button_save->setText(QCoreApplication::translate("WOther", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WOther: public Ui_WOther {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOTHER_H
