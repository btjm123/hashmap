#ifndef CHAINING_HASHMAP_H
#define CHAINING_HASHMAP_H

#include "HashMapItem.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <functional> // for std::hash

namespace benn
{
    template <typename K, typename V>
    class ChainingHashMap
    {
    public:
        ChainingHashMap();
        ~ChainingHashMap();
        V &operator[](K key);
        void insert(std::pair<K, V> kv);
        void remove(K key);
        size_t size();

    private:
        std::list<HashMapItem<int, int> *> *buckets;
        size_t bucketCount;
        size_t totalElements;
        HashMapItem<K, V> *find(K key);
        void rebalance();
        int hashKey(const K &key) const;
    };

    template <typename K, typename V>
    ChainingHashMap<K, V>::ChainingHashMap()
    {
        totalElements = 0;
        bucketCount = 100;
        buckets = new std::list<HashMapItem<K, V> *>[bucketCount];
    }

    template <typename K, typename V>
    ChainingHashMap<K, V>::~ChainingHashMap()
    {
        for (size_t i = 0; i < bucketCount; i++)
        {
            buckets[i].clear();
        }
        delete[] buckets;
    }

    template <typename K, typename V>
    int ChainingHashMap<K, V>::hashKey(const K &key) const
    {
        std::hash<K> hasher;
        return static_cast<int>(hasher(key) % bucketCount);
    }

    /*
    I tried to use optionals as I thought this would this make the code cleaner.
    But its still not supported for reference types :{
    Reason why I wanted to return reference types so its that the end user will be able to modify the key-value pair directly

    https://stackoverflow.com/questions/26858034/why-does-stdoptional-not-have-a-specialization-for-reference-types
    std::optional<HashMapItem<K, V>&> ChainingHashMap<K, V>::find(K key) {
        ...
        return std::nullopt;
    }
    */
    template <typename K, typename V>
    HashMapItem<K, V> *ChainingHashMap<K, V>::find(K key)
    {
        int bucketIndex = hashKey(key);
        auto &items = buckets[bucketIndex];
        for (const auto &item : items)
        {
            if (item->key == key)
            {
                return item;
            }
        }

        return nullptr;
    }

    template <typename K, typename V>
    void ChainingHashMap<K, V>::rebalance()
    {
        // TODO: rehash
    }

    template <typename K, typename V>
    void ChainingHashMap<K, V>::insert(std::pair<K, V> kv)
    {
        auto [key, value] = kv;
        auto kvInMap = this->find(key);
        if (kvInMap == nullptr)
        {
            int bucketIndex = hashKey(key);
            auto &items = buckets[bucketIndex];

            auto newItem = new HashMapItem<K, V>{key, value};
            ++totalElements;
            items.push_back(newItem);
        }
        else
        {
            kvInMap->value = value;
        }
    }

    template <typename K, typename V>
    V &ChainingHashMap<K, V>::operator[](K key)
    {
        auto kv = this->find(key);
        if (kv != nullptr)
        {
            return kv->value;
        }
        // If key does not exist, follow C++ convention of auto construction of values
        this->insert(std::pair<K, V>{key, V()});
        auto newKv = this->find(key);
        if (newKv == nullptr)
            throw std::runtime_error("Failed to insert key into map");
        return newKv->value;
    }

    template <typename K, typename V>
    void ChainingHashMap<K, V>::remove(K key)
    {
        int bucketIndex = hashKey(key);
        auto &items = buckets[bucketIndex];
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if ((*it)->key == key)
            {
                items.erase(it);
                --totalElements;
                return;
            }
        }
    }

    template <typename K, typename V>
    size_t ChainingHashMap<K, V>::size()
    {
        return totalElements;
    }

} // namespace benn

#endif // CHAINING_HASHMAP_H