#include <iostream>

//using namespace std;  //std  standard
                        //using编译指令
                        //一次性把std空间中的所有实体全部引入
                        //不推荐，因为现在对std空间中的所有实体不熟悉

namespace wd
{

//命名空间中的实体
int number=10;

void display()
{
    std::cout << "display()" << std::endl;    //endl  endline
}

}//end of namespace wd

int main(void)
{
    std::cout << "number = " << wd::number << std::endl;
    wd::display();  //::作用域限定符
    return 0;
}

