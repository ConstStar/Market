#pragma once

#include <QWidget>
#include "ui_WEmailTest.h"
#include <qstandarditemmodel.h>

#include <string>

using namespace std;

//��Ϣ��ʽ������
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
	bool get_otherConf();//��ȡ��Ϣ��ʽ


	void replace_all_random(string& str);
	void replace_all_distinct(string& str, string old_value, string new_value);
	void MsgValue(string& str);

	void readLastWrod();//��ȡ�ϴ����������
	void saveLastWrod();//�����ϴ����������

protected:
	//����һ���麯�����̳���QEvent.ֻҪ��д������麯�������㰴�´������Ͻǵ�"��"ʱ���ͻ����������д�Ĵ˺���.
	void closeEvent(QCloseEvent* event);

public slots:
	void onTest();
 	void onVerify();
	void onTableClicked(const QModelIndex& m);
	void slotRowDoubleClicked(const QModelIndex& w);
};
