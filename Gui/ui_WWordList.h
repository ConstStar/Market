/********************************************************************************
** Form generated from reading UI file 'WWordList.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WWORDLIST_H
#define UI_WWORDLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WWordList
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QTableView *tableView;
    QFrame *line;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QLineEdit *edit_title;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *edit_value;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *edit_name;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QPlainTextEdit *text_word;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *button_look;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_8;
    QPushButton *button_add;

    void setupUi(QWidget *WWordList)
    {
        if (WWordList->objectName().isEmpty())
            WWordList->setObjectName(QString::fromUtf8("WWordList"));
        WWordList->resize(901, 770);
        verticalLayout_6 = new QVBoxLayout(WWordList);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(WWordList);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(WWordList);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(verticalLayout_4);

        tableView = new QTableView(WWordList);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMinimumSize(QSize(600, 300));

        verticalLayout->addWidget(tableView);

        line = new QFrame(WWordList);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_5 = new QLabel(WWordList);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(label_5);

        edit_title = new QLineEdit(WWordList);
        edit_title->setObjectName(QString::fromUtf8("edit_title"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(edit_title->sizePolicy().hasHeightForWidth());
        edit_title->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(edit_title);


        verticalLayout->addLayout(horizontalLayout_8);


        horizontalLayout_9->addLayout(verticalLayout);

        line_3 = new QFrame(WWordList);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_9->addWidget(line_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(WWordList);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout);

        edit_value = new QTextEdit(WWordList);
        edit_value->setObjectName(QString::fromUtf8("edit_value"));
        sizePolicy1.setHeightForWidth(edit_value->sizePolicy().hasHeightForWidth());
        edit_value->setSizePolicy(sizePolicy1);
        edit_value->setMinimumSize(QSize(0, 300));
        edit_value->setReadOnly(true);

        verticalLayout_5->addWidget(edit_value);

        line_2 = new QFrame(WWordList);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(WWordList);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        edit_name = new QLineEdit(WWordList);
        edit_name->setObjectName(QString::fromUtf8("edit_name"));

        horizontalLayout_2->addWidget(edit_name);


        verticalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_9->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(WWordList);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        text_word = new QPlainTextEdit(WWordList);
        text_word->setObjectName(QString::fromUtf8("text_word"));
        text_word->setMinimumSize(QSize(0, 200));

        verticalLayout_2->addWidget(text_word);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        button_look = new QPushButton(WWordList);
        button_look->setObjectName(QString::fromUtf8("button_look"));

        horizontalLayout_5->addWidget(button_look);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_8 = new QLabel(WWordList);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_6->addWidget(label_8);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_3);

        button_add = new QPushButton(WWordList);
        button_add->setObjectName(QString::fromUtf8("button_add"));
        button_add->setMinimumSize(QSize(200, 70));

        horizontalLayout_7->addWidget(button_add);


        verticalLayout_6->addLayout(horizontalLayout_7);


        retranslateUi(WWordList);

        QMetaObject::connectSlotsByName(WWordList);
    } // setupUi

    void retranslateUi(QWidget *WWordList)
    {
        WWordList->setWindowTitle(QCoreApplication::translate("WWordList", "\345\206\205\345\256\271\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("WWordList", "\345\206\205\345\256\271\345\210\227\350\241\250(\345\217\263\345\207\273\344\277\256\346\224\271)", nullptr));
        label_2->setText(QCoreApplication::translate("WWordList", "\345\220\257\345\212\250\345\244\232\344\270\252\345\206\205\345\256\271\346\227\266\345\260\206\350\275\256\346\265\201\345\217\221\351\200\201", nullptr));
        label_5->setText(QCoreApplication::translate("WWordList", "\346\240\207\351\242\230:", nullptr));
        label_3->setText(QCoreApplication::translate("WWordList", "\345\217\230\351\207\217\345\210\227\350\241\250", nullptr));
        edit_value->setHtml(QCoreApplication::translate("WWordList", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\346\227\245\346\234\237}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\346\227\266\351\227\264}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\346\230\237\346\234\237}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-"
                        "block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{QQ\345\217\267\347\240\201}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{QQ\345\220\215\347\247\260}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\345\234\260\345\214\272}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\346\200\247\345\210\253}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\345\271\264\351\276\204}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-inden"
                        "t:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\347\276\244\345\217\267\347\240\201}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\347\276\244\345\220\215\347\211\207}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\347\276\244\345\220\215\347\247\260}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\351\232\217\346\234\272\346\225\260\345\255\227}	</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\351\232\217\346\234\272\347\254\246\345\217\267}</span></p>\n"
"<p style=\" margin-top:0px;"
                        " margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\351\232\217\346\234\272\345\244\247\345\206\231\345\255\227\346\257\215}</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">{\351\232\217\346\234\272\345\260\217\345\206\231\345\255\227\346\257\215}</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("WWordList", "\345\217\221\351\200\201\345\220\215\347\247\260:", nullptr));
        label_6->setText(QCoreApplication::translate("WWordList", "\351\202\256\347\256\261\345\206\205\345\256\271:", nullptr));
        button_look->setText(QCoreApplication::translate("WWordList", "\346\225\210\346\236\234\346\265\217\350\247\210", nullptr));
        label_8->setText(QCoreApplication::translate("WWordList", "\346\225\210\346\236\234\346\265\217\350\247\210\344\270\216\345\256\236\351\231\205\344\274\232\347\225\245\346\234\211\345\267\256\345\274\202\357\274\214\350\257\267\344\273\245\345\256\236\351\231\205\346\225\210\346\236\234\344\270\272\345\207\206", nullptr));
        button_add->setText(QCoreApplication::translate("WWordList", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WWordList: public Ui_WWordList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WWORDLIST_H
