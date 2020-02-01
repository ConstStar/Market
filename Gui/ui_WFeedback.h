/********************************************************************************
** Form generated from reading UI file 'WFeedback.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WFEEDBACK_H
#define UI_WFEEDBACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WFeedback
{
public:
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *edit_title;
    QLabel *label;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *combo_contact;
    QLineEdit *edit_contact;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *text_word;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QComboBox *combo_smtp;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_send;

    void setupUi(QWidget *WFeedback)
    {
        if (WFeedback->objectName().isEmpty())
            WFeedback->setObjectName(QString::fromUtf8("WFeedback"));
        WFeedback->resize(541, 394);
        verticalLayout_4 = new QVBoxLayout(WFeedback);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter = new QSplitter(WFeedback);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        edit_title = new QLineEdit(layoutWidget);
        edit_title->setObjectName(QString::fromUtf8("edit_title"));

        gridLayout->addWidget(edit_title, 1, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        combo_contact = new QComboBox(layoutWidget1);
        combo_contact->setObjectName(QString::fromUtf8("combo_contact"));
        combo_contact->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(combo_contact);

        edit_contact = new QLineEdit(layoutWidget1);
        edit_contact->setObjectName(QString::fromUtf8("edit_contact"));
        edit_contact->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(edit_contact);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        splitter->addWidget(layoutWidget1);

        verticalLayout_4->addWidget(splitter);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(WFeedback);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        text_word = new QTextEdit(WFeedback);
        text_word->setObjectName(QString::fromUtf8("text_word"));

        verticalLayout->addWidget(text_word);


        verticalLayout_4->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(WFeedback);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_6->addWidget(label_4);

        combo_smtp = new QComboBox(WFeedback);
        combo_smtp->setObjectName(QString::fromUtf8("combo_smtp"));

        horizontalLayout_6->addWidget(combo_smtp);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        button_send = new QPushButton(WFeedback);
        button_send->setObjectName(QString::fromUtf8("button_send"));
        button_send->setMinimumSize(QSize(130, 60));

        verticalLayout_2->addWidget(button_send);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(WFeedback);

        QMetaObject::connectSlotsByName(WFeedback);
    } // setupUi

    void retranslateUi(QWidget *WFeedback)
    {
        WFeedback->setWindowTitle(QCoreApplication::translate("WFeedback", "\345\234\250\347\272\277\345\217\215\351\246\210", nullptr));
        label->setText(QCoreApplication::translate("WFeedback", "\346\240\207\351\242\230:", nullptr));
        label_2->setText(QCoreApplication::translate("WFeedback", "\350\201\224\347\263\273\346\226\271\345\274\217:", nullptr));
        label_3->setText(QCoreApplication::translate("WFeedback", "\345\206\205\345\256\271:", nullptr));
        label_4->setText(QCoreApplication::translate("WFeedback", "\344\275\277\347\224\250\350\256\276\347\275\256\347\232\204\351\202\256\347\256\261\345\217\221\351\200\201\345\217\215\351\246\210:", nullptr));
        button_send->setText(QCoreApplication::translate("WFeedback", "\346\217\220\344\272\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WFeedback: public Ui_WFeedback {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WFEEDBACK_H
