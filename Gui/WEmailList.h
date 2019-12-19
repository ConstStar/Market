#pragma once

#include <QWidget>
#include "ui_WEmailList.h"

#include <qstandarditemmodel.h>
#include <qmenu.h>
#include <qaction.h>

#include <map>
#include <string>

class WEmailList : public QWidget
{
	Q_OBJECT

public:
	WEmailList(QWidget* parent = Q_NULLPTR);
	~WEmailList();

private:
	Ui::WEmailList ui;
	// 0 #  1 ����  2 ����  3��  4 ����  5 smtp  6 �˿�
	QStandardItemModel* m_model;
	int m_modelIndex;

	QMenu* m_contextMenu;
	std::map<std::string, int> emailDayNum;

	void addList(QString& email, QString& passwd, QString& adyMax, QString& port, bool ssl, QString& smtp);
	void addList(QString& email, QString& passwd, QString& adyMax, QString dayNum, QString& port, bool ssl, QString& smtp, QString id,bool s);
	void delList(int id);

	bool write_data();
	bool read_data();
	bool readCount();

	void readLastWrod();//��ȡ�ϴ����������
	void saveLastWrod();//�����ϴ����������

	bool eventFilter(QObject* obj, QEvent* evt);

protected:
	//����һ���麯�����̳���QEvent.ֻҪ��д������麯�������㰴�´������Ͻǵ�"��"ʱ���ͻ����������д�Ĵ˺���.
	void closeEvent(QCloseEvent* event);

public slots:
	void buttonAddList();
	void onTableClicked(const QModelIndex&);
	void onDelete();
	void onFromFile();
	void onOutFile();
	//void onTableUpdata(const QModelIndex& topLeft, const QModelIndex& bottomRight);
};
