/*Day8��ҵ0 ʵ��PIMPL���ģʽ*/

//Line_PIMPL.h
#pragma once

class Line
{
	class LineIMPL;
public:
	Line(int, int, int, int);//����
	~Line();//����

	void print() const;//��ӡ

private:
	LineIMPL* _pLineIMPL;
};