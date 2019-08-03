//只是写了一个大体框架，未进行实际测试

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Warrior	//武士
{
public:
	Warrior(int id, int life)
		: _id(id)
		, _life(life)
	{}

	static string _warrior_names[5];
	static string _weapons_names[3];

protected:
	int _id;	//编号
	int _life;	//生命值
};

string Warrior::_warrior_names[5] = { "dragon","ninja","iceman","lion","wolf" };
string Warrior::_weapons_names[3] = { "sword","bomb","arrow" };

class dragon
	: public Warrior
{
public:
	dragon(int lifebase, int id, int life)
		: Warrior(id, life)
		, _weapon(id % 3)
		, _morale((double)lifebase / double(life))
	{}

	void print() const
	{
		cout << "It has a " << _weapons_names[_weapon]
			<< ",and it's morale is ";
		printf("%.2f\n", _morale);
	}

private:
	int _weapon;	//武器
	double _morale;	//士气
};

class ninja
	: public Warrior
{
public:
	ninja(int lifebase, int id, int life)
		: Warrior(id, life)
		, _weapon1(id % 3)
		, _weapon2((id + 1) % 3)
	{}

	void print() const
	{
		cout << "It has a " << _weapons_names[_weapon1]
			<< " and a " << _weapons_names[_weapon2] << endl;
	}

private:
	int _weapon1;	//武器1
	int _weapon2;	//武器2
};

class iceman
	: public Warrior
{
public:
	iceman(int lifebase, int id, int life)
		: Warrior(id, life)
		, _weapon(id % 3)
	{}

	void print() const
	{
		cout << "It has a " << _weapons_names[_weapon] << endl;
	}

private:
	int _weapon;	//武器
};

class lion
	: public Warrior
{
public:
	lion(int lifebase, int id, int life)
		: Warrior(id, life)
		, _loyalty(lifebase)
	{}

	void print() const
	{
		cout << "It's loyalty is " << _loyalty << endl;
	}

private:
	int _loyalty;	//忠诚度
};

class wolf
	: public Warrior
{
public:
	wolf(int lifebase, int id, int life)
		: Warrior(id, life)
	{}

	void print() const
	{}

};


class Headquarter	//司令部
{
public:
	Headquarter(string color, int lifebase, int* needlife, int* order)
		: _color(color)
		, _lifebase(lifebase)
		, _time(0)
		, _flag(1)
		, _lastborn(4)
	{
		for (int i = 0; i < 5; ++i) {
			_needlife[i] = needlife[i];
			_order[i] = order[i];
			_count[i] = 0;
		}
	}

	int go_on()
	{
		if (_flag)
		{
			if (born())
			{
				_flag = 0;
			}
		}
		else {
			return -1;
		}
		++_time;
		return 0;
	}

	int born()
	{
		int nowborn = (_lastborn + 1) % 5;

		while (_lifebase < _needlife[_order[nowborn]] && nowborn != _lastborn) {
			nowborn = (nowborn + 1) % 5;
		}
		if (nowborn == _lastborn) {//停止生产
			printf("%03d ", _time);
			cout << _color << " headquarter stops making warriors" << endl;
			return -1;
		}
		else {
			_lastborn = nowborn;
		}//确定生产哪个武士

		int order = _order[nowborn];
		_lifebase -= _needlife[order];
		++_count[order];
		printf("%03d ", _time);
		cout << _color << " " << Warrior::_warrior_names[order]
			<< " " << (_time + 1)
			<< " born with strength " << _needlife[order]
			<< "," << _count[order] << " " << Warrior::_warrior_names[order]
			<< " in " << _color << " headquarter" << endl;

		if (order == 0) {
			dragon d(_lifebase, _time + 1, _needlife[order]);
			d.print();
		}
		else if (order == 1) {
			ninja n(_lifebase, _time + 1, _needlife[order]);
			n.print();
		}
		else if (order == 2) {
			iceman i(_lifebase, _time + 1, _needlife[order]);
			i.print();
		}
		else if (order == 3) {
			lion l(_lifebase, _time + 1, _needlife[order]);
			l.print();
		}
		else if (order == 4) {
			wolf w(_lifebase, _time + 1, _needlife[order]);
			w.print();
		}

		return 0;
	}

	bool get_flag()
	{
		return _flag;
	}

private:
	string _color;	//红方或蓝方
	int _lifebase;	//生命元
	int _time;	//时间
	bool _flag;	//是否停止生产
	int _lastborn;	//上次生产的武士顺次
	int _needlife[5]; //五种武士的不同生命值
	int _order[5];	//制造武士的顺序
	int _count[5];	//计五种武士的数量
};

//测试代码
void test1()
{
	cout << "Case1" << endl;
	int lifebase = 20;
	int needlife[5] = { 3,4,5,6,7 };
	int red_order[5] = { 2,3,4,1,0 };
	int blue_order[5] = { 3,0,1,2,4 };
	Headquarter red("red", lifebase, needlife, red_order);
	Headquarter blue("blue", lifebase, needlife, blue_order);

	int red_flag = 0, blue_flag = 0;

	while (1)
	{
		if (!red_flag) {
			red_flag = red.go_on();
		}
		if (!blue_flag) {
			blue_flag = blue.go_on();
		}
		if (red_flag && blue_flag) {
			break;
		}
	}

}

int main()
{
	//test1();
	
	int case_num;
	cin >> case_num;

	int lifebase;
	cin >> lifebase;

	int needlife[5];
	for (int i = 0; i < 5; ++i)
	{
		cin >> needlife[i];
	}

	int red_order[5] = { 2,3,4,1,0 };
	int blue_order[5] = { 3,0,1,2,4 };

	Headquarter red("red", lifebase, needlife, red_order);
	Headquarter blue("blue", lifebase, needlife, blue_order);

	cout << "Case:" << case_num << endl;
	while (1)
	{
		if (red.get_flag()) {
			red.go_on();
		}
		if (blue.get_flag()) {
			blue.go_on();
		}
		if (!red.get_flag() && !blue.get_flag()) {
			break;
		}
	}

	return 0;
}