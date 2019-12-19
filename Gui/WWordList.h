#pragma once

#include <QWidget>
#include "ui_WWordList.h"

#include <qstandarditemmodel.h>
#include <qmenu.h>

class WWordList : public QWidget
{
	Q_OBJECT

public:
	WWordList(QWidget* parent = Q_NULLPTR);
	~WWordList();

private:
	Ui::WWordList ui;
	QStandardItemModel* m_model;
	int m_modelIndex;
	int m_editRow;

	QMenu* m_contextMenu;

	void addList(QString& name, QString& title, QString& word);
	void addList(QString& name, QString& title, QString& word, QString id, bool s);
	void delList(int id);
	void editList(QString& name, QString& title, QString& word);

	bool write_data();
	bool read_data();

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
	void onEdit();
	void onLook();
};
