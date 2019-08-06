/*
�����������յ����ݽṹ����ƺ�ʵ��һ��  LRU (�������ʹ��) ������ơ�
��Ӧ��֧�����²����� ��ȡ���� get �� д������ put ��
	��ȡ���� get(key) - 
		�����Կ (key) �����ڻ����У����ȡ��Կ��ֵ�����������������򷵻� -1��
	д������ put(key, value) - 
		�����Կ�����ڣ���д��������ֵ��
		�����������ﵽ����ʱ����Ӧ����д��������֮ǰɾ���������ʹ�õ�����ֵ��
		�Ӷ�Ϊ�µ�����ֵ�����ռ䡣

����:
	���Ƿ������ O(1) ʱ�临�Ӷ�����������ֲ�����

ʾ��:
	LRUCache cache = new LRUCache( 2 ); //��������
	cache.put(1, 1);
	cache.put(2, 2);
	cache.get(1);       // ����  1
	cache.put(3, 3);    // �ò�����ʹ����Կ 2 ����
	cache.get(2);       // ���� -1 (δ�ҵ�)
	cache.put(4, 4);    // �ò�����ʹ����Կ 1 ����
	cache.get(1);       // ���� -1 (δ�ҵ�)
	cache.get(3);       // ����  3
	cache.get(4);       // ����  4

*/

#include <iostream>
#include <list>
#include <unordered_map>
using std::cout;
using std::endl;
using std::list;
using std::unordered_map;
using std::pair;

class LRUCache
{
public:
	LRUCache(int capacity) 
		: _capacity(capacity)
	{}

	int get(int key) {
		auto it = _map.find(key);
		if (it == _map.end()) {	//û�ҵ���Ӧֵ
			return -1;
		}
		else {
			if (it->second != _list.begin()) {	
				//�ýڵ㲻�ڶ�ͷ����Ҫ������ͷ
				pair<int, int> node = *(it->second);	//���ƽ��
				_list.erase(it->second);	//��������ɾ�����
				_list.push_front(node);	//�����ŵ���ͷ
				//����_map�е�λ��
				_map[key] = _list.begin();
			}
			return it->second->second;
		}
	}

	void put(int key, int value) {
		auto it = _map.find(key);
		if (it == _map.end()) {	//û�ҵ���Ӧֵ
			if (_map.size() == _capacity) {	//��������ɾ�������δʹ��Ԫ��
				int erase_key = _list.back().first;
				_list.pop_back();
				_map.erase(erase_key);
			}
			_list.push_front(std::make_pair(key, value));
			_map[key] = _list.begin();
		}
		else {//�ҵ�����Ӧֵ
			if (it->second != _list.begin()) {
				//�ýڵ㲻�ڶ�ͷ����Ҫ������ͷ
				pair<int, int> node = *(it->second);	//���ƽ��
				_list.erase(it->second);	//��������ɾ�����
				_list.push_front(node);	//�����ŵ���ͷ
				//����_map�е�λ��
				_map[key] = _list.begin();
			}
			_list.begin()->second = value;	//�ı���Ӧֵ
		}
	}

private:
	int _capacity;
	list<pair<int, int>> _list;		//˫�������� (key,value)
	unordered_map<int, list<pair<int, int>>::iterator> _map; //����key��������λ��
};


//�ύleetcode��ʾ�ɹ�����������Ͳ�д���Դ�����