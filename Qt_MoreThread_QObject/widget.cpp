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
	/*UI����*/
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
	/*����һ�����߳�*/
	qDebug() << tr("Begin Thread");
	firstThread = new QThread;                                                      //�߳�����
	myObjectThread = new MyThread;
	myObjectThread->moveToThread(firstThread);                                      //�������Ķ����Ƶ��߳�������
	connect(firstThread, SIGNAL(finished()), firstThread, SLOT(deleteLater()));        //��ֹ�߳�ʱҪ����deleteLater�ۺ���
	connect(firstThread, SIGNAL(started()), myObjectThread, SLOT(startThreadSlot()));  //�����̲߳ۺ���
	connect(firstThread, SIGNAL(finished()), this, SLOT(finishedThreadSlot()));
	firstThread->start();                                                           //�������̲߳ۺ���
	qDebug() << "mainWidget QThread::currentThreadId()==" << QThread::currentThreadId();
}

void Widget::closeThreadSlot()
{
	qDebug() << tr("Close Thread Finish");
	if (firstThread->isRunning())
	{
		myObjectThread->closeThread();  //�ر��̲߳ۺ���
		firstThread->quit();            //�˳��¼�ѭ��
		firstThread->wait();            //�ͷ��̲߳ۺ�����Դ
	}
}

void Widget::finishedThreadSlot()
{
	qDebug() << tr("���̴߳�����finished�ź�123");
}
