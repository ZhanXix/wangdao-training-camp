#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void display(vector<int> &vec)
{
    cout << "vec's size = " << vec.size() << endl;
    cout << "vec's capacity = " << vec.capacity() << endl;
}

void test0()
{
    //vector称为动态数组， 可以动态扩容
    //策略: 当size() == capacity() 时，
    //  先申请2 * size() 的空间,
    //  再将原来的元素全部复制到新空间
    //  然后再回收原来的空间
    //  最后再添加新元素
    //
    //动态扩容的开销比较大

    vector<int> vec;
    vec.reserve(1000);//只开空间，并不创建元素
    display(vec);
    cout << "sizeof(vec) = " << sizeof(vec) << endl;

    vec.push_back(1);
    display(vec);
    vec.push_back(2);
    display(vec);
    vec.push_back(3);
    display(vec);
    vec.push_back(4);
    display(vec);
    vec.push_back(5);
    display(vec);
    vec.push_back(6);
    display(vec);
    vec.push_back(7);
    display(vec);
    vec.push_back(8);
    display(vec);
    vec.pop_back();
    display(vec);

    for(size_t idx = 0; idx != vec.size(); ++idx) {
        cout << vec[idx] << " ";

    }
    cout << endl;

    for(auto & number : vec) {
        cout << number << " ";

    }
    cout << endl;

    cout << "sizeof(vec) = " << sizeof(vec) << endl;

}

int main()
{
    test0();
    return 0;
}

