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
	// 0 #  1 邮箱  2 密码  3今发  4 日限  5 smtp  6 端口
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

	void readLastWrod();//读取上次输入的内容
	void saveLastWrod();//保存上次输入的内容

	bool eventFilter(QObject* obj, QEvent* evt);

protected:
	//这是一个虚函数，继承自QEvent.只要重写了这个虚函数，当你按下窗口右上角的"×"时，就会调用你所重写的此函数.
	void closeEvent(QCloseEvent* event);

public slots:
	void buttonAddList();
	void onTableClicked(const QModelIndex&);
	void onDelete();
	void onFromFile();
	void onOutFile();
	//void onTableUpdata(const QModelIndex& topLeft, const QModelIndex& bottomRight);
};
