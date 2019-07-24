/*
编写一个类，实现简单的队列。队列中有以下操作：
       > 元素入队             void push(int);
       > 元素出队             void pop();
       > 读取队头元素         int front();
       > 读取队尾元素         int back();
       > 判断队列是否为空     bool emty();
	   > 判断队列是否已满     bool full();
*/
#include <iostream>
using std::cout;
using std::endl;

class Queue
{
public:
    Queue()
    : _head(0)
    , _tail(0)
    {
        cout << "Queue()" << endl;
    }

    void push(int val)
    {
        if(!full())
        {
            cout << "PUSH " << val << endl;
            _arr[_tail]=val;
            _tail = (_tail+1)%10;     
        }else{
            cout << "QUEUE FULL! CANNOT PUSH" << endl;
        }
    }

    void pop()
    {
        if(!empty())
        {
            cout << "POP" << endl;
            _head = (_head+1)%10;
        }else{
            cout << "QUEUE EMPTY! CANNOT POP" << endl;
        }
    }

    int front()
    {
        if(!empty())
        {
            return _arr[_head];
        }else{
            cout << "QUEUE EMPTY! CANNOT GET FRONT VAL" << endl;
            return  0;
        }
    }

    int back()
    {
        if(!empty())
        {
            return _arr[(_tail+9)%10];
        }else{
            cout << "QUEUE EMPTY! CANNOT GET BACK VAL" << endl;
            return 0;
        }
    }

    bool empty()
    {
        if(_head == _tail)
        {
            return true;
        }else{
            return  false;
        }
    }

    bool full()
    {
        if(_head == (_tail+1)%10)
        {
            return true;
        }else{
            return  false;
        }
    }

private:
    int _arr[10];
    int _head;
    int _tail;
};

int main()
{
    Queue q;
    q.push(10);
    q.push(12);
    q.push(14);
    cout << "q.front() = " <<q.front() << endl;
    q.pop();
    cout << "q.front() = " <<q.front() << endl;

    return 0;
}

