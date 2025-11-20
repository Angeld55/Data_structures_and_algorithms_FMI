// Task:
// Design and build a "least recently used" cache, which evicts the least
// recently used item. The cache should map from keys to values (allowing you
// to insert and retrieve a value associated with a particular key) and be
// initialized with a max size. When it is full, it should evict the least
// recently used item.


#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <unordered_map> 
#include <optional> //we need c++ 17

template<typename KeyType, typename ValueType>
class LeastRecentlyUsedCache
{
    using CacheList         = std::list<std::pair<KeyType, ValueType>>;
    using CacheListIterator = typename CacheList::iterator;
    using CacheMap          = std::unordered_map<KeyType, CacheListIterator>;

    CacheList _cache;
    CacheMap  _keyToCacheMap;
    size_t    _capacity;

    void markAsMostRecentlyUsed(typename CacheMap::iterator mapIt)
    {
        CacheListIterator cacheIt = mapIt->second;
        _cache.splice(_cache.end(), _cache, cacheIt);
    }

    void handleCacheSize()
    {
        if(_cache.size() > _capacity)
        {
            KeyType key = _cache.front().first;
            _keyToCacheMap.erase(key);
            _cache.pop_front();
        }
    }

public:
    LeastRecentlyUsedCache(size_t capacity) : _capacity(capacity) {}

    // Return an optional value. If key is not found, returns std::nullopt
    std::optional<ValueType> findInCache(const KeyType& key)
    {
        auto it = _keyToCacheMap.find(key);
        if (it == _keyToCacheMap.end())
        {
            return std::nullopt;
        }
        markAsMostRecentlyUsed(it);
        return it->second->second;
    }

    // If key is new, add it. If key is already present, update its value
    bool addInCache(const KeyType& key, const ValueType& value)
    {
        auto [mapIt, inserted] = _keyToCacheMap.insert({key, _cache.end()});

        if (!inserted)
        {
            // mapIt points to the existing element
            mapIt->second->second = value;  // update value
            markAsMostRecentlyUsed(mapIt);
            return true;
        }

        _cache.push_back({key, value});
        auto endIter = _cache.end();
        --endIter;
        mapIt->second = endIter;

        handleCacheSize();
        return true;
    }
};


////Mocking

// Simulates heavy work
template<typename Key, typename Value>
Value workHard(const Key &request) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return Value(request);
}

// Specialization for std::string
template<>
std::string workHard(const std::string &request) {
    static const std::string request_suffix("request");
    static const std::string response_suffix("response");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    size_t request_body_length = request.size() - request_suffix.size(); 
    return request.substr(0, request_body_length) + response_suffix;
}

// Specialization for int
template<>
std::string workHard(const int& request) {
    static const std::string response_pref("response ");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return response_pref + std::to_string(request);
}

// Retrieves from cache if possible. Otherwise computes using workHard and caches it
template<typename Key, typename Value>
Value handle(const Key &request, LeastRecentlyUsedCache<Key, Value>& cache) {
    auto res = cache.findInCache(request);
    if (res.has_value()) {
        return *res;
    }
    Value response = workHard<Key, Value>(request);
    cache.addInCache(request, response);
    return response;
}

int main(int argc, char *argv[]) {

    const size_t CACHE_CAPACITY = 2;
    LeastRecentlyUsedCache<int, std::string> cache(CACHE_CAPACITY);

    std::string response = handle(1, cache);
    std::cout << response << "(s)" << std::endl;

    response = handle(1, cache);
    std::cout << response << "(f)" << std::endl;

    response = handle(2, cache);
    std::cout << response << "(s)" << std::endl;

    response = handle(2, cache);
    std::cout << response << "(f)" << std::endl;

    response = handle(1, cache);
    std::cout << response << "(f)" << std::endl;

    response = handle(3, cache);
    std::cout << response << "(s)" << std::endl;

    response = handle(3, cache);
    std::cout << response << "(f)" << std::endl;

    response = handle(1, cache);
    std::cout << response << "(f)" << std::endl;

    response = handle(2, cache);
    std::cout << response << "(s)" << std::endl;

    return 0;
}
