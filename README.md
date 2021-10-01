# QThreadedObject
A helper base class for automatize movetothread() and initialize variables in thread's memory by running init()

## Usage
```C++
#include "qthreadedobject.hpp"
#include <QDebug>

class MyClass : public QThreadedObject
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
      qDebug() << QThread::currentThreadId();
    }
public slots:
    void my_slot()
    {
      // runs in separate thread or caller thread that depends on how calling this slot (direct call from object might not run in a separate thread but signal slot or invokemethod calling runs in separate thread
      qDebug() << QThread::currentThreadId();
    }
    
signals:
      ...
private:
      ...
};
    
int main()
{
  QApplication app();
  
  qDebug() << QThread::currentThreadId(); // main thread id
  
  Myclass c; // automatically runs init() in separate thread
  
  QMetaObject::invokeMethod(&c, &MyClass::my_slot); // my_slot runs in separate thread
  
  c.my_slot(); // runs in main thread
  
  return app.exec();
}
```
    
    
    
    
    
    
    
