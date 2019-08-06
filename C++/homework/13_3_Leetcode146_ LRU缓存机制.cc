/*
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。
它应该支持以下操作： 获取数据 get 和 写入数据 put 。
	获取数据 get(key) - 
		如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
	写入数据 put(key, value) - 
		如果密钥不存在，则写入其数据值。
		当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，
		从而为新的数据值留出空间。

进阶:
	你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:
	LRUCache cache = new LRUCache( 2 ); //缓存容量
	cache.put(1, 1);
	cache.put(2, 2);
	cache.get(1);       // 返回  1
	cache.put(3, 3);    // 该操作会使得密钥 2 作废
	cache.get(2);       // 返回 -1 (未找到)
	cache.put(4, 4);    // 该操作会使得密钥 1 作废
	cache.get(1);       // 返回 -1 (未找到)
	cache.get(3);       // 返回  3
	cache.get(4);       // 返回  4

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
		if (it == _map.end()) {	//没找到相应值
			return -1;
		}
		else {
			if (it->second != _list.begin()) {	
				//该节点不在队头，需要换到队头
				pair<int, int> node = *(it->second);	//复制结点
				_list.erase(it->second);	//从链表中删除结点
				_list.push_front(node);	//将结点放到队头
				//更新_map中的位置
				_map[key] = _list.begin();
			}
			return it->second->second;
		}
	}

	void put(int key, int value) {
		auto it = _map.find(key);
		if (it == _map.end()) {	//没找到相应值
			if (_map.size() == _capacity) {	//缓存满，删除最近久未使用元素
				int erase_key = _list.back().first;
				_list.pop_back();
				_map.erase(erase_key);
			}
			_list.push_front(std::make_pair(key, value));
			_map[key] = _list.begin();
		}
		else {//找到了相应值
			if (it->second != _list.begin()) {
				//该节点不在队头，需要换到队头
				pair<int, int> node = *(it->second);	//复制结点
				_list.erase(it->second);	//从链表中删除结点
				_list.push_front(node);	//将结点放到队头
				//更新_map中的位置
				_map[key] = _list.begin();
			}
			_list.begin()->second = value;	//改变相应值
		}
	}

private:
	int _capacity;
	list<pair<int, int>> _list;		//双向链表结点 (key,value)
	unordered_map<int, list<pair<int, int>>::iterator> _map; //隐射key和链表结点位置
};


//提交leetcode显示成功，所以这里就不写测试代码了