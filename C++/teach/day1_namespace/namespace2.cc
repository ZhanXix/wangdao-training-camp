#include <iostream>

//using namespace std;  //using编译指令
                        
using std::cout;    //using声明机制
using std::endl;

namespace wd
{

//命名空间中的实体
int number=10;

void display()
{
    cout << "display()" << endl;    //endl  endline
}

}//end of namespace wd

int main(void)
{
    cout << "number = " << wd::number << endl;
    wd::display();  //作用域限定符
    return 0;
}

