/********************************************************************************
** Form generated from reading UI file 'WEmailTest.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEMAILTEST_H
#define UI_WEMAILTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
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

class Ui_WEmailTest
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_state;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QComboBox *combo_word;
    QLineEdit *edit_putEmail;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *edit_verifyEmail;
    QPushButton *button_verify;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_5;
    QPushButton *button_test;

    void setupUi(QWidget *WEmailTest)
    {
        if (WEmailTest->objectName().isEmpty())
            WEmailTest->setObjectName(QString::fromUtf8("WEmailTest"));
        WEmailTest->resize(809, 597);
        verticalLayout_5 = new QVBoxLayout(WEmailTest);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(WEmailTest);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_state = new QLabel(WEmailTest);
        label_state->setObjectName(QString::fromUtf8("label_state"));

        horizontalLayout->addWidget(label_state);


        verticalLayout_5->addLayout(horizontalLayout);

        tableView = new QTableView(WEmailTest);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMinimumSize(QSize(600, 300));

        verticalLayout_5->addWidget(tableView);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(WEmailTest);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(WEmailTest);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        combo_word = new QComboBox(WEmailTest);
        combo_word->setObjectName(QString::fromUtf8("combo_word"));

        verticalLayout_2->addWidget(combo_word);

        edit_putEmail = new QLineEdit(WEmailTest);
        edit_putEmail->setObjectName(QString::fromUtf8("edit_putEmail"));

        verticalLayout_2->addWidget(edit_putEmail);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        line = new QFrame(WEmailTest);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(WEmailTest);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(240, 16777215));

        horizontalLayout_5->addWidget(label_4);

        edit_verifyEmail = new QLineEdit(WEmailTest);
        edit_verifyEmail->setObjectName(QString::fromUtf8("edit_verifyEmail"));
        edit_verifyEmail->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(edit_verifyEmail);

        button_verify = new QPushButton(WEmailTest);
        button_verify->setObjectName(QString::fromUtf8("button_verify"));
        button_verify->setMinimumSize(QSize(100, 0));
        button_verify->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_5->addWidget(button_verify);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        label_5 = new QLabel(WEmailTest);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_4);

        button_test = new QPushButton(WEmailTest);
        button_test->setObjectName(QString::fromUtf8("button_test"));
        button_test->setMinimumSize(QSize(200, 80));
        button_test->setMaximumSize(QSize(200, 80));

        horizontalLayout_7->addWidget(button_test);


        verticalLayout_5->addLayout(horizontalLayout_7);


        retranslateUi(WEmailTest);

        QMetaObject::connectSlotsByName(WEmailTest);
    } // setupUi

    void retranslateUi(QWidget *WEmailTest)
    {
        WEmailTest->setWindowTitle(QCoreApplication::translate("WEmailTest", "\351\202\256\347\256\261\346\265\213\350\257\225", nullptr));
        label->setText(QCoreApplication::translate("WEmailTest", "\345\217\221\351\200\201\351\202\256\347\256\261\346\265\213\350\257\225(\350\257\267\345\205\210\345\213\276\351\200\211\351\234\200\350\246\201\346\265\213\350\257\225\347\232\204\351\202\256\347\256\261)", nullptr));
        label_state->setText(QCoreApplication::translate("WEmailTest", "(\345\217\214\345\207\273\345\244\215\345\210\266)", nullptr));
        label_2->setText(QCoreApplication::translate("WEmailTest", "\351\200\211\346\213\251\345\217\221\344\273\266\345\206\205\345\256\271:", nullptr));
        label_3->setText(QCoreApplication::translate("WEmailTest", "\346\216\245\346\224\266\351\202\256\347\256\261:", nullptr));
        label_4->setText(QCoreApplication::translate("WEmailTest", "\350\276\223\345\205\245\344\270\200\344\270\252QQ\345\217\267\347\240\201\351\252\214\350\257\201\346\230\257\345\220\246\345\274\200\351\200\232\351\202\256\347\256\261:", nullptr));
        button_verify->setText(QCoreApplication::translate("WEmailTest", "\351\252\214\350\257\201", nullptr));
        label_5->setText(QCoreApplication::translate("WEmailTest", "\346\265\213\350\257\225\347\232\204\345\217\230\351\207\217\345\260\206\344\270\272\351\273\230\350\256\244\345\200\274", nullptr));
        button_test->setText(QCoreApplication::translate("WEmailTest", "\345\274\200\345\247\213\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WEmailTest: public Ui_WEmailTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEMAILTEST_H
