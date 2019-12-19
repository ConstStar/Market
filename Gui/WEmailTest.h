#pragma once

#include <QWidget>
#include "ui_WEmailTest.h"
#include <qstandarditemmodel.h>

#include <string>

using namespace std;

//消息格式配置项
struct OTHER_CONF
{
	bool useHtml;

	string verifyEmail;
	string verifyPasswd;
};

class WEmailTest : public QWidget
{
	Q_OBJECT

public:
	WEmailTest(QWidget *parent = Q_NULLPTR);
	~WEmailTest();

private:
	Ui::WEmailTest ui;
	QStandardItemModel* m_model;

	bool get_word(int id, string& name, string& title, string& word);
	bool read_emailList();
	bool read_wordList();
	bool get_otherConf();//获取消息格式


	void replace_all_random(string& str);
	void replace_all_distinct(string& str, string old_value, string new_value);
	void MsgValue(string& str);

	void readLastWrod();//读取上次输入的内容
	void saveLastWrod();//保存上次输入的内容

protected:
	//这是一个虚函数，继承自QEvent.只要重写了这个虚函数，当你按下窗口右上角的"×"时，就会调用你所重写的此函数.
	void closeEvent(QCloseEvent* event);

public slots:
	void onTest();
 	void onVerify();
	void onTableClicked(const QModelIndex& m);
	void slotRowDoubleClicked(const QModelIndex& w);
};
