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
			if (text == QString::fromLocal8Bit("ϵͳ"))
				value = QBrush(Qt::blue);
			else if (text == QString::fromLocal8Bit("���ͳɹ�"))
				value = QBrush(Qt::darkGreen);
			else if (text == QString::fromLocal8Bit("����ʧ��"))
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
	//����һ���麯�����̳���QEvent.ֻҪ��д������麯�������㰴�´������Ͻǵ�"��"ʱ���ͻ����������д�Ĵ˺���.
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
