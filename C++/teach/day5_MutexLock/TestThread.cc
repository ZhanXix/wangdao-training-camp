#include "MutexLock.h"
#include "Condition.h"

#include <iostream>
using std::cout;
using std::endl;


int ticket = 200;
int flag = true;
wd::MutexLock gmutex;
wd::Condition gcondition(gmutex);

//wd::MutexLock gmutex2(gmutex);//要让该语句不能编译通过

void * windows1(void *arg)
{
    int cnt = 20;
    while(cnt--) {
        //使用MutexLockGuard对象，可以保证不会发生死锁
        wd::MutexLockGuard autolock(gmutex);//RAII
        //gmutex.lock();
        while(!flag) {//flag == false
            gcondition.wait();//出现异常（虚假）唤醒
        }

        //当flag为true时，执行卖票
        --ticket;
        cout << ">> windows1 " << pthread_self() 
            << " : left ticket = " << ticket << endl;
        if(flag) {
            flag = false;
        }
        gcondition.notify();

        //gmutex.unlock();
    }

    return nullptr;
}

void * windows2(void *arg)
{
    int cnt=20;
    while(cnt--){
        //gmutex.lock();
        wd::MutexLockGuard autolock(gmutex);
        while(flag) {
            gcondition.wait();
        }

        //当flag为false时，执行卖票
        --ticket;
        cout << ">> windows2 " << pthread_self()
            << " : left ticket = " << ticket << endl;
        if(!flag) {
            flag = true;
        }
        gcondition.notify();

        //gmutex.unlock();
    }
    return nullptr;
}

int main()
{
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, nullptr, windows1, nullptr);
    pthread_create(&pthid2, nullptr, windows2, nullptr);
    pthread_join(pthid1, nullptr);
    pthread_join(pthid2, nullptr);
    return 0;
}

