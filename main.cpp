#include <bits/stdc++.h>

using namespace std;

class Cache
{
private:
	int capacity;

	// key -> {value, position in list}
	unordered_map<string, pair<int, list<string>::iterator>> cache;

	// Front = Most Recently Used
	// Back  = Least Recently Used
	list<string> lru;

public:
	Cache(int capacity)
	{
		this->capacity = capacity;
	}

	int get(string key)
	{
		if (cache.find(key) == cache.end())
		{
			return -1;
		}

		// Move key to the front (Most Recently Used)
		lru.erase(cache[key].second);
		lru.push_front(key);

		// Update iterator
		cache[key].second = lru.begin();

		return cache[key].first;
	}

	void put(string key, int value)
	{
		// Key already exists
		if (cache.find(key) != cache.end())
		{
			lru.erase(cache[key].second);
			lru.push_front(key);

			cache[key] = {value, lru.begin()};

			return;
		}

		// Cache is full
		if (cache.size() == capacity)
		{
			string lruKey = lru.back();

			lru.pop_back();
			cache.erase(lruKey);
		}

		// Insert new key
		lru.push_front(key);
		cache[key] = {value, lru.begin()};
	}
};

int main()
{
	Cache cache(2);

	cache.put("A", 10);
	cache.put("B", 20);

	cout << cache.get("A") << endl; // 10

	cache.put("C", 30);

	cout << cache.get("B") << endl; // -1
	cout << cache.get("C") << endl; // 30
	cout << cache.get("A") << endl; // 10

	return 0;
}