/********************************************************************************
** Form generated from reading UI file 'WSystem.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSYSTEM_H
#define UI_WSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WSystem
{
public:
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_14;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *edit_verifyEmail;
    QLineEdit *edit_verifyPasswd;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *check_keyVerify;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLineEdit *edit_keyVerify;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *button_getKey;
    QPushButton *button_getCredits;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *edit_smtpSleep;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QLineEdit *edit_keyWordMsgSize;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *edit_oneQQDayMax;
    QLineEdit *edit_oneQQSleep;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *edit_oneGroupTime;
    QLabel *label_3;
    QLineEdit *edit_oneGroupEmail;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_;
    QLabel *label;
    QLabel *label_12;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *edit_key;
    QLineEdit *edit_ComputerId;
    QLineEdit *edit_exceedDateTime;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *button_save;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *WSystem)
    {
        if (WSystem->objectName().isEmpty())
            WSystem->setObjectName(QString::fromUtf8("WSystem"));
        WSystem->resize(722, 384);
        verticalLayout_12 = new QVBoxLayout(WSystem);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        groupBox = new QGroupBox(WSystem);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_11 = new QVBoxLayout(groupBox);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 20));

        verticalLayout_4->addWidget(label_5);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 20));

        verticalLayout_4->addWidget(label_6);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        edit_verifyEmail = new QLineEdit(groupBox);
        edit_verifyEmail->setObjectName(QString::fromUtf8("edit_verifyEmail"));
        edit_verifyEmail->setMinimumSize(QSize(170, 0));

        verticalLayout_3->addWidget(edit_verifyEmail);

        edit_verifyPasswd = new QLineEdit(groupBox);
        edit_verifyPasswd->setObjectName(QString::fromUtf8("edit_verifyPasswd"));

        verticalLayout_3->addWidget(edit_verifyPasswd);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_11->addLayout(horizontalLayout_2);


        horizontalLayout_14->addWidget(groupBox);

        groupBox_5 = new QGroupBox(WSystem);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_8 = new QVBoxLayout(groupBox_5);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        check_keyVerify = new QCheckBox(groupBox_5);
        check_keyVerify->setObjectName(QString::fromUtf8("check_keyVerify"));

        verticalLayout_8->addWidget(check_keyVerify);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_11->addWidget(label_13);

        edit_keyVerify = new QLineEdit(groupBox_5);
        edit_keyVerify->setObjectName(QString::fromUtf8("edit_keyVerify"));

        horizontalLayout_11->addWidget(edit_keyVerify);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        button_getKey = new QPushButton(groupBox_5);
        button_getKey->setObjectName(QString::fromUtf8("button_getKey"));

        horizontalLayout_13->addWidget(button_getKey);

        button_getCredits = new QPushButton(groupBox_5);
        button_getCredits->setObjectName(QString::fromUtf8("button_getCredits"));

        horizontalLayout_13->addWidget(button_getCredits);


        verticalLayout_8->addLayout(horizontalLayout_13);


        horizontalLayout_14->addWidget(groupBox_5);


        verticalLayout_12->addLayout(horizontalLayout_14);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        groupBox_2 = new QGroupBox(WSystem);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_12 = new QHBoxLayout(groupBox_2);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        edit_smtpSleep = new QLineEdit(groupBox_2);
        edit_smtpSleep->setObjectName(QString::fromUtf8("edit_smtpSleep"));

        horizontalLayout_3->addWidget(edit_smtpSleep);


        verticalLayout_9->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_6->addWidget(label_11);

        edit_keyWordMsgSize = new QLineEdit(groupBox_2);
        edit_keyWordMsgSize->setObjectName(QString::fromUtf8("edit_keyWordMsgSize"));

        horizontalLayout_6->addWidget(edit_keyWordMsgSize);


        verticalLayout_9->addLayout(horizontalLayout_6);


        horizontalLayout_12->addLayout(verticalLayout_9);


        horizontalLayout_7->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(WSystem);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_9 = new QHBoxLayout(groupBox_3);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 20));

        verticalLayout_5->addWidget(label_8);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 20));

        verticalLayout_5->addWidget(label_9);


        horizontalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        edit_oneQQDayMax = new QLineEdit(groupBox_3);
        edit_oneQQDayMax->setObjectName(QString::fromUtf8("edit_oneQQDayMax"));

        verticalLayout_6->addWidget(edit_oneQQDayMax);

        edit_oneQQSleep = new QLineEdit(groupBox_3);
        edit_oneQQSleep->setObjectName(QString::fromUtf8("edit_oneQQSleep"));

        verticalLayout_6->addWidget(edit_oneQQSleep);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        edit_oneGroupTime = new QLineEdit(groupBox_3);
        edit_oneGroupTime->setObjectName(QString::fromUtf8("edit_oneGroupTime"));
        edit_oneGroupTime->setMinimumSize(QSize(50, 0));
        edit_oneGroupTime->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(edit_oneGroupTime);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        edit_oneGroupEmail = new QLineEdit(groupBox_3);
        edit_oneGroupEmail->setObjectName(QString::fromUtf8("edit_oneGroupEmail"));
        edit_oneGroupEmail->setMinimumSize(QSize(50, 0));
        edit_oneGroupEmail->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(edit_oneGroupEmail);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_5);


        horizontalLayout_9->addLayout(verticalLayout_7);

        line = new QFrame(groupBox_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_9->addWidget(line);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_9->addWidget(label_10);


        horizontalLayout_7->addWidget(groupBox_3);


        verticalLayout_12->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox_4 = new QGroupBox(WSystem);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(400, 0));
        horizontalLayout_10 = new QHBoxLayout(groupBox_4);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_ = new QLabel(groupBox_4);
        label_->setObjectName(QString::fromUtf8("label_"));
        label_->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(label_);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(label);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(label_12);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        edit_key = new QLineEdit(groupBox_4);
        edit_key->setObjectName(QString::fromUtf8("edit_key"));
        edit_key->setEnabled(true);
        edit_key->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(edit_key);

        edit_ComputerId = new QLineEdit(groupBox_4);
        edit_ComputerId->setObjectName(QString::fromUtf8("edit_ComputerId"));
        edit_ComputerId->setEnabled(true);
        edit_ComputerId->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(edit_ComputerId);

        edit_exceedDateTime = new QLineEdit(groupBox_4);
        edit_exceedDateTime->setObjectName(QString::fromUtf8("edit_exceedDateTime"));
        edit_exceedDateTime->setEnabled(true);
        edit_exceedDateTime->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(edit_exceedDateTime);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_10->addLayout(horizontalLayout);


        horizontalLayout_8->addWidget(groupBox_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        button_save = new QPushButton(WSystem);
        button_save->setObjectName(QString::fromUtf8("button_save"));
        button_save->setMinimumSize(QSize(150, 60));
        button_save->setMaximumSize(QSize(150, 60));

        horizontalLayout_8->addWidget(button_save);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_12->addLayout(horizontalLayout_8);


        retranslateUi(WSystem);

        QMetaObject::connectSlotsByName(WSystem);
    } // setupUi

    void retranslateUi(QWidget *WSystem)
    {
        WSystem->setWindowTitle(QCoreApplication::translate("WSystem", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WSystem", "\346\231\256\351\200\232\351\252\214\350\257\201\351\202\256\347\256\261\345\217\257\347\224\250\346\200\247", nullptr));
        label_5->setText(QCoreApplication::translate("WSystem", "QQ\351\202\256\347\256\261\350\264\246\345\217\267:", nullptr));
        label_6->setText(QCoreApplication::translate("WSystem", "\351\202\256\347\256\261\346\216\210\346\235\203\347\240\201:", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("WSystem", "\347\254\254\344\270\211\346\226\271\351\252\214\350\257\201\351\202\256\347\256\261\345\217\257\347\224\250\346\200\247", nullptr));
        check_keyVerify->setText(QCoreApplication::translate("WSystem", "\344\275\277\347\224\250\347\254\254\344\270\211\346\226\271\351\252\214\350\257\201\346\226\271\345\274\217", nullptr));
        label_13->setText(QCoreApplication::translate("WSystem", "key:", nullptr));
        button_getKey->setText(QCoreApplication::translate("WSystem", "\350\216\267\345\217\226key", nullptr));
        button_getCredits->setText(QCoreApplication::translate("WSystem", "\346\237\245\350\257\242\345\211\251\344\275\231", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WSystem", "\351\243\216\346\216\247\350\256\276\347\275\256\344\270\200", nullptr));
        label_7->setText(QCoreApplication::translate("WSystem", "\346\257\217\351\202\256\347\256\261\345\217\221\351\200\201\351\232\224\351\227\264(\347\247\222):", nullptr));
        label_11->setText(QCoreApplication::translate("WSystem", "\347\276\244\346\266\210\346\201\257\345\255\227\346\225\260\351\231\220\345\210\266:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WSystem", "\351\243\216\346\216\247\350\256\276\347\275\256\344\272\214", nullptr));
        label_8->setText(QCoreApplication::translate("WSystem", "\346\257\217\344\270\252QQ\344\270\200\345\244\251\346\234\200\345\244\232\346\216\245\346\224\266\351\202\256\344\273\266:", nullptr));
        label_9->setText(QCoreApplication::translate("WSystem", "\345\220\214\344\270\200QQ\344\270\244\345\260\201\351\202\256\344\273\266\351\232\224\351\227\264\347\247\222\346\225\260:", nullptr));
        label_2->setText(QCoreApplication::translate("WSystem", "\345\215\225\344\270\252\347\276\244\345\234\250", nullptr));
        label_3->setText(QCoreApplication::translate("WSystem", "\347\247\222\345\206\205\345\217\221\351\200\201\351\202\256\344\273\266\344\270\215\350\203\275\350\266\205\350\277\207", nullptr));
        label_4->setText(QCoreApplication::translate("WSystem", "\345\260\201", nullptr));
        label_10->setText(QCoreApplication::translate("WSystem", "\345\241\2530\345\210\231\344\270\215\351\231\220\345\210\266", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WSystem", "\347\212\266\346\200\201", nullptr));
        label_->setText(QCoreApplication::translate("WSystem", "\345\275\223\345\211\215\346\263\250\345\206\214\347\240\201:", nullptr));
        label->setText(QCoreApplication::translate("WSystem", "\346\234\272\345\231\250\347\240\201:", nullptr));
        label_12->setText(QCoreApplication::translate("WSystem", "\345\210\260\346\234\237\346\227\266\351\227\264:", nullptr));
        button_save->setText(QCoreApplication::translate("WSystem", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WSystem: public Ui_WSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSYSTEM_H
