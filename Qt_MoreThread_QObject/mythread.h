#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class MyThread : public QObject
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = nullptr);

	void closeThread();

signals:

	public slots :
		void startThreadSlot();

private:
	volatile bool isStop;
};

#endif // MYTHREAD_H
