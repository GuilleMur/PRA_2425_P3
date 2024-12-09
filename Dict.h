#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V> 
class Dict {
	public:
	void insert(const std::string key, const V val)= 0;

        V search(std::string key)= 0;

        V remove(std::string key)= 0;

        int entries()= 0;
};

#endif
