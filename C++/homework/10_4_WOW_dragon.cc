//ֻ��д��һ�������ܣ�δ����ʵ�ʲ���

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Warrior	//��ʿ
{
public:
	Warrior(int id, int life)
		: _id(id)
		, _life(life)
	{}

	static string _warrior_names[5];
	static string _weapons_names[3];

protected:
	int _id;	//���
	int _life;	//����ֵ
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
			<< ",and it's morale is " << _morale << endl;
	}

private:
	int _weapon;	//����
	double _morale;	//ʿ��
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
	int _weapon1;	//����1
	int _weapon2;	//����2
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
	int _weapon;	//����
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
	int _loyalty;	//�ҳ϶�
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


class Headquarter	//˾�
{
public:
	Headquarter(string color, int lifebase, int* needlife, int* order)
		: _color(color)
		, _lifebase(lifebase)
		, _time(0)
		, _flag(1)
		, _lastborn(0)
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
			printf("%03d ", _time);
			cout << _color << " headquarter stops making warriors" << endl;
			return -1;
		}
		++_time;
	}

	int born()
	{
		int nowborn = (_lastborn + 1) % 5;

		while (_lifebase < _needlife[_order[nowborn]] && nowborn != _lastborn) {
			nowborn = (nowborn + 1) % 5;
		}
		if (nowborn == _lastborn) {
			return -1;
		}
		else {
			_lastborn = nowborn;
		}//ȷ�������ĸ���ʿ

		int order = _order[nowborn];
		_lifebase -= _needlife[order];
		++_count[order];
		printf("%03d ", _time);
		cout << _color << " " << Warrior::_warrior_names[order]
			<< " " << (_time + 1)
			<< "born with strength " << _needlife[order]
			<< "," << _count[order] << " " << Warrior::_warrior_names[order]
			<< " in " << _color << " headquarter" << endl;
		
		switch (order)
		{
		case 0:
			dragon x(_lifebase, _time + 1, _needlife[nowborn]);
		case 1:
			ninja x(_lifebase, _time + 1, _needlife[nowborn]);
		case 2:
			iceman x(_lifebase, _time + 1, _needlife[nowborn]);
		case 3:
			lion x(_lifebase, _time + 1, _needlife[nowborn]);
		case 4:
			wolf x(_lifebase, _time + 1, _needlife[nowborn]);
		default:
			break;
		}

	}

private:
	string _color;	//�췽������
	int _lifebase;	//����Ԫ
	int _time;	//ʱ��
	bool _flag;	//�Ƿ�ֹͣ����
	int _lastborn;	//�ϴ���������ʿ˳��
	int _needlife[5]; //������ʿ�Ĳ�ͬ����ֵ
	int _order[5];	//������ʿ��˳��
	int _count[5];	//��������ʿ������
};