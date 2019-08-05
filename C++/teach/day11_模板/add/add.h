#pragma once

template <class T>
T add(T x, T y);

#include "add.cc"
//使用模板时，要看到其所有的实现，不能仅仅是一部分
//所以一般情况下，不会将模板分成头文件和实现文件