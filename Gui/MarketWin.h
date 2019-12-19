#pragma once

#include <QtWidgets/QMainWindow>
#include <qstandarditemmodel.h>
#include <qsqlquerymodel.h>
//#include <qfuture.h>
#include <qstring.h>
#include <qmessagebox.h>

#include "ui_MarketWin.h"

class mySqlQueryModel :public QSqlQueryModel
{
public:
	mySqlQueryModel(QObject* parent = nullptr) :QSqlQueryModel(parent) {};
	~mySqlQueryModel() {};
	QVariant data(const QModelIndex& item, int role) const
	{
		QVariant value = QSqlQueryModel::data(item, role);

		if (item.row() >= 0 && role == Qt::ForegroundRole)
		{
			QString text = QSqlQueryModel::data(QSqlQueryModel::index(item.row(), 3)).toString();
			//QMessageBox::information(NULL, text, "test");
			//if (item.row() == 0 && role == Qt::ForegroundRole)
			if (text == QString::fromLocal8Bit("系统"))
				value = QBrush(Qt::blue);
			else if (text == QString::fromLocal8Bit("发送成功"))
				value = QBrush(Qt::darkGreen);
			else if (text == QString::fromLocal8Bit("发送失败"))
				value = QBrush(Qt::red);
		}
		return value;
	}
};


class MarketWin : public QMainWindow
{
	Q_OBJECT

public:
	MarketWin(QWidget* parent = Q_NULLPTR);

	~MarketWin();


protected:
	//这是一个虚函数，继承自QEvent.只要重写了这个虚函数，当你按下窗口右上角的"×"时，就会调用你所重写的此函数.
	void closeEvent(QCloseEvent* event);

private:
	Ui::MarketWinClass ui;
	mySqlQueryModel* model;
	QString sql;
	QSqlDatabase db;
	//QFuture <void> updateLog;

	void readCount();

public slots:
	void OpenSmtpList();
	void OpenWordList();
	void OpenGroupList();
	void OpenSystem();
	void OpenOher();
	void OpenUpdata();
	void OpenEmailTest();
	void OpenFeedback();
	void readLog();
	void FilterLogSql();
	void slotRowDoubleClicked(const QModelIndex&);
	void onUpdataList();
	void OpenKeyWordGroup();
	void onClearLog();
};
