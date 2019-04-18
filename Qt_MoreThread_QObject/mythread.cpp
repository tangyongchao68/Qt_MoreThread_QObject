#include "mythread.h"
#include <QDebug>
#include <QThread>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
	isStop = false;
}

void MyThread::closeThread()
{
	isStop = true;
}

void MyThread::startThreadSlot()
{
	while (1)
	{
		if (isStop)
			return;
		qDebug() << "MyThread::startThreadSlot QThread::currentThreadId()==" << QThread::currentThreadId();
		QThread::sleep(1);
	}
}
