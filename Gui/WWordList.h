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
	void onEdit();
	void onLook();
};
