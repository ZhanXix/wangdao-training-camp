/*Day8作业0 实现PIMPL设计模式*/

//Line_PIMPL.h
#pragma once

class Line
{
	class LineIMPL;
public:
	Line(int, int, int, int);//构造
	~Line();//析构

	void print() const;//打印

private:
	LineIMPL* _pLineIMPL;
};