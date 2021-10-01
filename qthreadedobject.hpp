#ifndef QTHREADEDOBJECT_HPP
#define QTHREADEDOBJECT_HPP

#include <QObject>
#include <QThread>
#include <QEvent>

class QThreadedObject : public QObject
{
    Q_OBJECT
public:
    explicit QThreadedObject(QObject *parent = nullptr);
    virtual ~QThreadedObject();

    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    virtual void init();

private:
    QThread mThread;
};

inline QThreadedObject::QThreadedObject(QObject *parent) : QObject(parent)
{
    installEventFilter(this);
    moveToThread(&mThread);
}

inline QThreadedObject::~QThreadedObject(){
    mThread.quit();
    mThread.wait();
}

inline bool QThreadedObject::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    switch (event->type()) {
    case QEvent::ThreadChange:
        connect(&mThread, &QThread::started, this, &QThreadedObject::init);
        mThread.start();
        return true;
    default:
        return false;
    }
}

inline void QThreadedObject::init(){}

#endif // QTHREADEDOBJECT_HPP
