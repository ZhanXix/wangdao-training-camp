#pragma once

#include <pthread.h>
#include <stdio.h> 
 #include <errno.h>

namespace wd{

class MutexLock
{
public:
    MutexLock() 
    {
        if(pthread_mutex_init(&_mutex, nullptr)){
            perror(">> pthread_mutex_init");
        }
    }

    ~MutexLock() 
    {
        if(pthread_mutex_destroy(&_mutex)){
            perror(">> pthread_mutex_destroy");
        }
    }

    void lock()
    {
        if(pthread_mutex_lock(&_mutex)){
            perror(">> pthread_mutex_lock");
        }
    }

    void unlock()
    {
        if(pthread_mutex_unlock(&_mutex)){
            perror(">> pthread_mutex_unlock");
        }
    }

    pthread_mutex_t * getMutexLockPtr()
    {
        return &_mutex;
    }

    //C++11的用法，禁止复制操作
    MutexLock(const MutexLock &rhs) = delete;
    MutexLock & operator=(const MutexLock &rhs) = delete;

private:
    //C++11之前的用法，禁止复制操作
    //MutexLock(const MutexLock &rhs);
    //MutexLock & operator=(const MutexLock &rhs);
    pthread_mutex_t _mutex;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
    : _mutex(mutex)
    {
       _mutex.lock(); 
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock & _mutex;
};

}//end of namespace wd
