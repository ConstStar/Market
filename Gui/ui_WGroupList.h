/********************************************************************************
** Form generated from reading UI file 'WGroupList.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGROUPLIST_H
#define UI_WGROUPLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_WGroupList
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QLabel *label_zt;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edit_groupId;
    QPushButton *button_add;

    void setupUi(QWidget *WGroupList)
    {
        if (WGroupList->objectName().isEmpty())
            WGroupList->setObjectName(QString::fromUtf8("WGroupList"));
        WGroupList->resize(393, 553);
        verticalLayout = new QVBoxLayout(WGroupList);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox = new QCheckBox(WGroupList);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        label_zt = new QLabel(WGroupList);
        label_zt->setObjectName(QString::fromUtf8("label_zt"));

        verticalLayout->addWidget(label_zt);

        tableView = new QTableView(WGroupList);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new QPushButton(WGroupList);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new QPushButton(WGroupList);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(WGroupList);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        edit_groupId = new QLineEdit(WGroupList);
        edit_groupId->setObjectName(QString::fromUtf8("edit_groupId"));

        horizontalLayout->addWidget(edit_groupId);

        button_add = new QPushButton(WGroupList);
        button_add->setObjectName(QString::fromUtf8("button_add"));

        horizontalLayout->addWidget(button_add);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(WGroupList);

        QMetaObject::connectSlotsByName(WGroupList);
    } // setupUi

    void retranslateUi(QWidget *WGroupList)
    {
        WGroupList->setWindowTitle(QCoreApplication::translate("WGroupList", "\347\276\244\345\210\227\350\241\250", nullptr));
        checkBox->setText(QCoreApplication::translate("WGroupList", "\347\233\221\346\216\247\347\276\244\346\250\241\345\274\217/\350\277\207\346\273\244\347\276\244\346\250\241\345\274\217", nullptr));
        label_zt->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("WGroupList", "\345\205\250\351\200\211", nullptr));
        pushButton->setText(QCoreApplication::translate("WGroupList", "\345\217\215\351\200\211", nullptr));
        label->setText(QCoreApplication::translate("WGroupList", "\350\257\267\350\276\223\345\205\245\347\276\244\345\217\267:", nullptr));
        button_add->setText(QCoreApplication::translate("WGroupList", "\346\211\213\345\212\250\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WGroupList: public Ui_WGroupList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGROUPLIST_H
