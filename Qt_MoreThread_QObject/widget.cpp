#include <QDebug>
#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	createView();
}

Widget::~Widget()
{
}

void Widget::createView()
{
	/*UI界面*/
	mainLayout = new QVBoxLayout(this);
	QPushButton *openThreadBtn = new QPushButton(tr("Open Thread"));
	QPushButton *closeThreadBtn = new QPushButton(tr("Close Thread"));
	mainLayout->addWidget(openThreadBtn);
	mainLayout->addWidget(closeThreadBtn);
	mainLayout->addStretch();
	connect(openThreadBtn, SIGNAL(clicked(bool)), this, SLOT(openThreadSlot()));
	connect(closeThreadBtn, SIGNAL(clicked(bool)), this, SLOT(closeThreadSlot()));
}

void Widget::openThreadSlot()
{
	/*开启一条多线程*/
	qDebug() << tr("Begin Thread");
	firstThread = new QThread;                                                      //线程容器
	myObjectThread = new MyThread;
	myObjectThread->moveToThread(firstThread);                                      //将创建的对象移到线程容器中
	connect(firstThread, SIGNAL(finished()), firstThread, SLOT(deleteLater()));        //终止线程时要调用deleteLater槽函数
	connect(firstThread, SIGNAL(started()), myObjectThread, SLOT(startThreadSlot()));  //开启线程槽函数
	connect(firstThread, SIGNAL(finished()), this, SLOT(finishedThreadSlot()));
	firstThread->start();                                                           //开启多线程槽函数
	qDebug() << "mainWidget QThread::currentThreadId()==" << QThread::currentThreadId();
}

void Widget::closeThreadSlot()
{
	qDebug() << tr("Close Thread Finish");
	if (firstThread->isRunning())
	{
		myObjectThread->closeThread();  //关闭线程槽函数
		firstThread->quit();            //退出事件循环
		firstThread->wait();            //释放线程槽函数资源
	}
}

void Widget::finishedThreadSlot()
{
	qDebug() << tr("多线程触发了finished信号123");
}
