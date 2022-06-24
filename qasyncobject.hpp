#ifndef QASYNCOBJECT_HPP
#define QASYNCOBJECT_HPP

#include <QObject>
#include <QThread>
#include <QEvent>

class QAsyncObject : public QObject
{
    Q_OBJECT
public:
    explicit QAsyncObject(QObject *parent = nullptr);
    virtual ~QAsyncObject();

    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    virtual void init();

private:
    QThread mThread;
};

inline QAsyncObject::QAsyncObject(QObject *parent) : QObject(parent)
{
    installEventFilter(this);
    moveToThread(&mThread);
}

inline QAsyncObject::~QAsyncObject(){
    mThread.quit();
    mThread.wait();
}

inline bool QAsyncObject::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    switch (event->type()) {
    case QEvent::ThreadChange:
        connect(&mThread, &QThread::started, this, &QAsyncObject::init);
        mThread.start();
        return true;
    default:
        return false;
    }
}

inline void QAsyncObject::init(){}

#endif // QASYNCOBJECT_HPP
