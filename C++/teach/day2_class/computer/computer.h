#pragma once

#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    //防止public区域的称为类对外的接口、功能、服务
    void setBrand(const char * brand);
    void setPrice(float price);
    void print();

private://封装的效果
    //私有的成员不能在类之外直接访问
    char _brand[20];//数据成员名字前要加下划线（约定俗成），有时候别人会写 brand_ 或 m_brand
    float _price;

};
