#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QThread>
#include "mythread.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

	void createView();

	private slots:
	void openThreadSlot();
	void closeThreadSlot();
	void finishedThreadSlot();

private:
	QVBoxLayout *mainLayout;
	QThread *firstThread;
	MyThread *myObjectThread;
};

#endif // WIDGET_H
