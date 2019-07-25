/*
封装Linux下互斥锁和条件变量,并自行编写测试程序
    互斥锁MutexLock和条件变量Condition类的框架如下：

   class MutexLock
   {
   public:
      //...
			void lock();
			void unlock();
	 private:
	 	//...
   };

   class Condition
   {
   public:
      //...
			void wait();
			void notify();
			void notifyall();
	 private:
	    //...

   };
*/

#include <iostream>
using std::cout;
using std::endl;

class MutexLock
{
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex,NULL);
        cout << "MutexLock()" << endl;
    }

    ~MutexLock()
    {
        pthread_mutex_destroy(&_mutex);
        cout << "~MutexLock()" << endl;
    }

    void lock()
    {
        pthread_mutex_lock(&_mutex);
        cout << "lock()" << endl;
    }

    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
        cout << "unlock()" << endl;
    }

private:
    pthread_mutex_t _mutex;
};

class Condition
{
public:
    Condition()
    {
        pthread_cond_init(&_cond,NULL);
        cout << "Condition()" << endl;
    }

    ~Condition()
    {
        pthread_cond_destroy(&_cond);
        cout << "~Condition()" << endl;
    }

    void wait(pthread_mutex_t * pMutex)
    {
        pthread_cond_wait(&_cond,pMutex);
        cout << "void wait(pthread_mutex_t *)" << endl;
    }

    void notify()
    {
        pthread_cond_signal(&_cond);
        cout << "notify()" << endl;     
    } 

    void notifyall()
    {
        pthread_cond_broadcast(&_cond);
        cout << "notifyall()" << endl;
    }

private:
    pthread_cond_t _cond;
};

void * Thread_Func(void *p)
{
    MutexLock *pLock = (MutexLock*)p;
    pLock->lock(); 
    cout << "I am thread" << endl;
    pLock->unlock();
    return NULL;
}

int main()
{
    pthread_t pthid;
    MutexLock *pLock = new MutexLock();
    Condition cond;
    pthread_create(&pthid,NULL,Thread_Func,pLock);
    pLock->lock();
    cout << "I am main" << endl;
    pLock->unlock();
    pthread_join(pthid,NULL);
    delete pLock;
    return 0;
}

