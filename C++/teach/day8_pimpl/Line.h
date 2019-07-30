 ///
 /// @file    Line.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 10:59:28
 ///
 
#pragma once

#include <stdio.h>

#include <iostream>
using std::cout;
using std::endl;

//PIMPL设计模式
//
//作用：
//	1. 实现信息隐藏
//	2. 降低编译依赖, 
//	3. 只要接口不变, 头文件不变，实现可以随便改造, 可以以一个最小代价完成库的平滑升级
//

class Line
{
	class LineImpl;
public:
	Line(int, int, int, int);
	~Line();

	void printLine() const;

private:
	LineImpl * _pimpl;
};

