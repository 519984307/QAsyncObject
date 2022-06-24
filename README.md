# QAsyncObject
A helper base class for automatize movetothread() and initialize variables in thread's memory by running init()

## Usage
```C++
#include <QCoreApplication>
#include "qasyncobject.hpp"
#include <QDebug>

class MyClass : public QAsyncObject
{
public:
    MyClass()
    {
      // runs in same thread that this object is created (same as subclassing qthread)
    }

private slots:
    void init()
    {
      // runs in separate thread (same as QThread::run)
      qDebug() << __FUNCTION__ << QThread::currentThreadId();
    }
public slots:
    void my_slot()
    {
      // runs in separate thread or caller thread that depends on how calling this slot (direct call from object might not run in a separate thread but signal slot or invokemethod calling runs in separate thread
      qDebug() << __FUNCTION__ << QThread::currentThreadId();
    }

};

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  qDebug() << __FUNCTION__ << QThread::currentThreadId(); // main thread id - "main 0x38ac"

  MyClass c; // automatically runs init() in separate thread - "MyClass::init 0x2de8"

  QMetaObject::invokeMethod(&c, &MyClass::my_slot); // my_slot runs in separate thread - "MyClass::my_slot 0x2de8"

  c.my_slot(); // runs in main thread - "MyClass::my_slot 0x38ac"

  return app.exec();
}
```
    
    
    
    
    
    
    
