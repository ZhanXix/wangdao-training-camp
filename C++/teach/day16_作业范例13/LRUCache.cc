#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache
{
public:
	LRUCache(size_t capacity)
		: _capacity(capacity)
	{}

	int get(int key)
	{
		auto it = _hashlist.find(key);
		if (it != _hashlist.end()) {
			//查找到元素
			int ret = it->second->value;
			_nodes.splice(_nodes.begin(), _nodes, it->second);
			_hashlist[key] = _nodes.begin();
			return ret;
		}
		else {
			return -1;
		}
	}

	void put(int key, int value)
	{
		auto it = _hashlist.find(key);
		if (it == _hashlist.end()) {
			//新结点
			if (_nodes.size() == _capacity) {
				//淘汰结点
				int k = _nodes.back().key;
				_nodes.pop_back();
				_hashlist.erase(k);
			}
			_nodes.push_front(CacheNode(key, value));
			_hashlist[key] = _nodes.begin();
		}
		else {
			//更新节点值
			it->second->value = value;
			_nodes.splice(_nodes.begin(), _nodes, it->second);
			_hashlist[key] = _nodes.begin();
		}
	}

private:
	struct CacheNode
	{
		CacheNode(int k,int v)
			: key(k),value(v)
		{}
		int key;
		int value;
	};
private:
	size_t _capacity;
	unordered_map<int,list<CacheNode>::iterator> _hashlist;
	list<CacheNode> _nodes;
};

int main()
{
	LRUCache cache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	cout << cache.get(1) << endl;
	cache.put(3, 3);
	cout << cache.get(2) << endl;
	cache.put(4, 4);
	cout << cache.get(1) << endl;
	cout << cache.get(3) << endl;
	cout << cache.get(4) << endl;
	cache.put(5, 5);
	cout << cache.get(3) << endl;

	return 0;
}