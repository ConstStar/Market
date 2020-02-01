/********************************************************************************
** Form generated from reading UI file 'MarketWin.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKETWIN_H
#define UI_MARKETWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MarketWinClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_state;
    QCheckBox *check_updata;
    QTableView *tableView;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QCheckBox *check_ok;
    QCheckBox *check_intoGroup;
    QCheckBox *check_keyWord;
    QCheckBox *check_error;
    QCheckBox *check_quit;
    QCheckBox *check_system;
    QPushButton *button_filter;
    QPushButton *button_clearLog;
    QFrame *line_2;
    QLabel *label_3;
    QLineEdit *edit_countDay;
    QLabel *label_4;
    QLineEdit *edit_countAll;
    QLabel *label_5;
    QLineEdit *edit_countGroup;
    QPushButton *button_updateList;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *button_smtpList;
    QPushButton *button_wordList;
    QPushButton *button_groupList;
    QPushButton *button_keyWordGroup;
    QPushButton *button_other;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_system;
    QPushButton *button_update;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_emailTest;

    void setupUi(QMainWindow *MarketWinClass)
    {
        if (MarketWinClass->objectName().isEmpty())
            MarketWinClass->setObjectName(QString::fromUtf8("MarketWinClass"));
        MarketWinClass->resize(896, 585);
        MarketWinClass->setAcceptDrops(false);
        MarketWinClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MarketWinClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_8->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_8->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        label_state = new QLabel(centralWidget);
        label_state->setObjectName(QString::fromUtf8("label_state"));

        horizontalLayout_8->addWidget(label_state);

        check_updata = new QCheckBox(centralWidget);
        check_updata->setObjectName(QString::fromUtf8("check_updata"));

        horizontalLayout_8->addWidget(check_updata);


        verticalLayout->addLayout(horizontalLayout_8);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setStyleSheet(QString::fromUtf8(""));
        tableView->setFrameShape(QFrame::Panel);
        tableView->setLineWidth(1);
        tableView->setShowGrid(true);

        verticalLayout->addWidget(tableView);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(70, 0));
        label_2->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(label_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        check_ok = new QCheckBox(centralWidget);
        check_ok->setObjectName(QString::fromUtf8("check_ok"));
        check_ok->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(check_ok, 0, 0, 1, 1);

        check_intoGroup = new QCheckBox(centralWidget);
        check_intoGroup->setObjectName(QString::fromUtf8("check_intoGroup"));
        check_intoGroup->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(check_intoGroup, 0, 1, 1, 1);

        check_keyWord = new QCheckBox(centralWidget);
        check_keyWord->setObjectName(QString::fromUtf8("check_keyWord"));
        check_keyWord->setMinimumSize(QSize(100, 20));

        gridLayout->addWidget(check_keyWord, 0, 2, 1, 1);

        check_error = new QCheckBox(centralWidget);
        check_error->setObjectName(QString::fromUtf8("check_error"));
        check_error->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(check_error, 1, 0, 1, 1);

        check_quit = new QCheckBox(centralWidget);
        check_quit->setObjectName(QString::fromUtf8("check_quit"));
        check_quit->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(check_quit, 1, 1, 1, 1);

        check_system = new QCheckBox(centralWidget);
        check_system->setObjectName(QString::fromUtf8("check_system"));

        gridLayout->addWidget(check_system, 1, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        button_filter = new QPushButton(centralWidget);
        button_filter->setObjectName(QString::fromUtf8("button_filter"));
        button_filter->setMinimumSize(QSize(80, 30));
        button_filter->setMaximumSize(QSize(80, 30));

        horizontalLayout->addWidget(button_filter);

        button_clearLog = new QPushButton(centralWidget);
        button_clearLog->setObjectName(QString::fromUtf8("button_clearLog"));
        button_clearLog->setMinimumSize(QSize(80, 30));
        button_clearLog->setMaximumSize(QSize(80, 30));

        horizontalLayout->addWidget(button_clearLog);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_3);

        edit_countDay = new QLineEdit(centralWidget);
        edit_countDay->setObjectName(QString::fromUtf8("edit_countDay"));
        edit_countDay->setEnabled(true);
        edit_countDay->setMinimumSize(QSize(0, 0));
        edit_countDay->setReadOnly(true);

        horizontalLayout->addWidget(edit_countDay);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_4);

        edit_countAll = new QLineEdit(centralWidget);
        edit_countAll->setObjectName(QString::fromUtf8("edit_countAll"));
        edit_countAll->setEnabled(true);
        edit_countAll->setFrame(true);
        edit_countAll->setDragEnabled(false);
        edit_countAll->setReadOnly(true);

        horizontalLayout->addWidget(edit_countAll);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_5);

        edit_countGroup = new QLineEdit(centralWidget);
        edit_countGroup->setObjectName(QString::fromUtf8("edit_countGroup"));
        edit_countGroup->setEnabled(true);
        edit_countGroup->setReadOnly(true);

        horizontalLayout->addWidget(edit_countGroup);

        button_updateList = new QPushButton(centralWidget);
        button_updateList->setObjectName(QString::fromUtf8("button_updateList"));
        button_updateList->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(button_updateList);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        button_smtpList = new QPushButton(centralWidget);
        button_smtpList->setObjectName(QString::fromUtf8("button_smtpList"));
        button_smtpList->setMinimumSize(QSize(0, 0));
        button_smtpList->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(button_smtpList);

        button_wordList = new QPushButton(centralWidget);
        button_wordList->setObjectName(QString::fromUtf8("button_wordList"));
        button_wordList->setMinimumSize(QSize(100, 40));
        button_wordList->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(button_wordList);

        button_groupList = new QPushButton(centralWidget);
        button_groupList->setObjectName(QString::fromUtf8("button_groupList"));
        button_groupList->setMinimumSize(QSize(100, 40));
        button_groupList->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(button_groupList);

        button_keyWordGroup = new QPushButton(centralWidget);
        button_keyWordGroup->setObjectName(QString::fromUtf8("button_keyWordGroup"));
        button_keyWordGroup->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(button_keyWordGroup);

        button_other = new QPushButton(centralWidget);
        button_other->setObjectName(QString::fromUtf8("button_other"));
        button_other->setMinimumSize(QSize(100, 40));
        button_other->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(button_other);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        button_system = new QPushButton(centralWidget);
        button_system->setObjectName(QString::fromUtf8("button_system"));
        button_system->setMinimumSize(QSize(100, 40));
        button_system->setMaximumSize(QSize(120, 40));

        horizontalLayout_7->addWidget(button_system);

        button_update = new QPushButton(centralWidget);
        button_update->setObjectName(QString::fromUtf8("button_update"));
        button_update->setMinimumSize(QSize(100, 40));

        horizontalLayout_7->addWidget(button_update);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_emailTest = new QPushButton(centralWidget);
        button_emailTest->setObjectName(QString::fromUtf8("button_emailTest"));
        button_emailTest->setMinimumSize(QSize(100, 40));
        button_emailTest->setMaximumSize(QSize(120, 40));

        horizontalLayout_3->addWidget(button_emailTest);


        horizontalLayout_7->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_7);

        MarketWinClass->setCentralWidget(centralWidget);

        retranslateUi(MarketWinClass);

        QMetaObject::connectSlotsByName(MarketWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *MarketWinClass)
    {
        MarketWinClass->setWindowTitle(QCoreApplication::translate("MarketWinClass", "\344\270\273\347\225\214\351\235\242", nullptr));
        label->setText(QCoreApplication::translate("MarketWinClass", "\346\227\245\345\277\227(\345\217\214\345\207\273\345\244\215\345\210\266)", nullptr));
        label_6->setText(QString());
        label_state->setText(QString());
        check_updata->setText(QCoreApplication::translate("MarketWinClass", "\345\256\236\346\227\266\346\233\264\346\226\260\346\227\245\345\277\227", nullptr));
        label_2->setText(QCoreApplication::translate("MarketWinClass", "\346\227\245\345\277\227\347\261\273\345\236\213:", nullptr));
        check_ok->setText(QCoreApplication::translate("MarketWinClass", "\346\210\220\345\212\237", nullptr));
        check_intoGroup->setText(QCoreApplication::translate("MarketWinClass", "\350\277\233\347\276\244", nullptr));
        check_keyWord->setText(QCoreApplication::translate("MarketWinClass", "\350\247\246\345\217\221\345\205\263\351\224\256\350\257\215", nullptr));
        check_error->setText(QCoreApplication::translate("MarketWinClass", "\345\244\261\350\264\245", nullptr));
        check_quit->setText(QCoreApplication::translate("MarketWinClass", "\351\200\200\347\276\244", nullptr));
        check_system->setText(QCoreApplication::translate("MarketWinClass", "\347\263\273\347\273\237", nullptr));
        button_filter->setText(QCoreApplication::translate("MarketWinClass", "\350\277\207\346\273\244", nullptr));
        button_clearLog->setText(QCoreApplication::translate("MarketWinClass", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
        label_3->setText(QCoreApplication::translate("MarketWinClass", "\344\273\212\345\217\221:", nullptr));
        label_4->setText(QCoreApplication::translate("MarketWinClass", "\347\264\257\345\217\221:", nullptr));
        label_5->setText(QCoreApplication::translate("MarketWinClass", "\347\276\244\346\225\260:", nullptr));
        button_updateList->setText(QCoreApplication::translate("MarketWinClass", "\345\210\267\346\226\260", nullptr));
        button_smtpList->setText(QCoreApplication::translate("MarketWinClass", "\345\217\221\351\200\201SMTP\350\256\276\347\275\256", nullptr));
        button_wordList->setText(QCoreApplication::translate("MarketWinClass", "\345\217\221\351\200\201\345\206\205\345\256\271\350\256\276\347\275\256", nullptr));
        button_groupList->setText(QCoreApplication::translate("MarketWinClass", "QQ\347\276\244\350\256\276\347\275\256", nullptr));
        button_keyWordGroup->setText(QCoreApplication::translate("MarketWinClass", "\347\276\244\346\266\210\346\201\257\345\205\263\351\224\256\350\257\215", nullptr));
        button_other->setText(QCoreApplication::translate("MarketWinClass", "\345\205\266\344\273\226\350\256\276\347\275\256", nullptr));
        button_system->setText(QCoreApplication::translate("MarketWinClass", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        button_update->setText(QCoreApplication::translate("MarketWinClass", "\345\234\250\347\272\277\346\233\264\346\226\260", nullptr));
        button_emailTest->setText(QCoreApplication::translate("MarketWinClass", "\351\202\256\347\256\261\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MarketWinClass: public Ui_MarketWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKETWIN_H
