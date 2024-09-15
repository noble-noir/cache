#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace
{
template <typename KeyT, typename T> class Cache
{
    int size_;
    std::list<std::pair<KeyT, T>> cache_;
    using It = typename std::list<std::pair<KeyT, T>>::iterator;
    std::unordered_map<KeyT, It> hash_;
public:
    Cache(int size) : size_(size) {};
    int Cache_step(KeyT key_, T t_)
    {
        auto search = hash_.find(key_);
        if(search != hash_.end())
        {
            cache_.push_front(**search);
            cache_.erase(search);
            return 1;
        }
        else if(cache_.size() == size_)
        {
            auto i = hash_.find(cache_.back()->first);
            hash_.erase(i);
            cache_.pop_back();
        }
        cache_.push_front(std::pair<KeyT, T> (key_, t_));
        hash_.insert(key_, cache_.begin());
        return 0;
    }
    void cache_print()
    {
        for(auto i : cache_)
            std::cout << i.second << std::endl;
    }
};
}

int main()
{
    int hits, size, amount;
    std::cin >> size >> amount;
    Cache<int, int> cache_{size};
    int i = 0;
    while(i < amount)
    {
        int a;
        std::cin >> a;
        hits += cache_.Cache_step(a, a);
    }
    cache_.cache_print();
    std::cout << hits << std::endl;
    return 0;
}