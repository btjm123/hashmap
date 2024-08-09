#ifndef OPEN_ADDRESSING_HASHMAP_H
#define OPEN_ADDRESSING_HASHMAP_H

#include "HashMapItem.hpp"
#include "constants.h"

#include <algorithm>
#include <optional>
#include <vector>
#include <functional> // for std::hash

namespace benn
{
    template <typename K, typename V>
    class OpenAddressingHashMap
    {
    public:
        OpenAddressingHashMap();
        ~OpenAddressingHashMap() = default;
        void insert(std::pair<K, V> kv);
        void remove(K key);
        V &operator[](K key);
        size_t size() const;
        size_t getBucketCount() const;

    private:
        std::vector<HashMapItem<K, V> *> buckets;
        std::optional<int> getBucketIndexFor(const K &key) const;
        size_t bucketCount;
        size_t totalElements;
        int hashKey(const K &key) const;
        void rebalance();
    };

    template <typename K, typename V>
    OpenAddressingHashMap<K, V>::OpenAddressingHashMap() : bucketCount(1), totalElements(0)
    {
        buckets.resize(bucketCount, nullptr);
    }

    template <typename K, typename V>
    int OpenAddressingHashMap<K, V>::hashKey(const K &key) const
    {
        std::hash<K> hasher;
        return static_cast<int>(hasher(key) % this->bucketCount);
    }

    template <typename K, typename V>
    void OpenAddressingHashMap<K, V>::rebalance()
    {
        int loadFactor = totalElements / bucketCount;
        if (loadFactor < MAX_LOAD_FACTOR)
        {
            return;
        }

        this->bucketCount *= 2;
        std::vector<HashMapItem<K, V> *> newBuckets;
        newBuckets.resize(this->bucketCount, nullptr);
        for (auto item : buckets)
        {
            if (item == nullptr)
                continue;
            int bucketIndex = hashKey(item->key);
            int currentIndex = bucketIndex;

            while (newBuckets[currentIndex] != nullptr)
            {
                ++currentIndex;
                if (currentIndex >= bucketCount)
                    currentIndex = 0;
                if (currentIndex == bucketIndex)
                {
                    break;
                }
            }

            newBuckets[currentIndex] = item;
        }

        this->buckets = newBuckets;
        std::cout << "resized to " << this->bucketCount << std::endl;
    }

    template <typename K, typename V>
    std::optional<int> OpenAddressingHashMap<K, V>::getBucketIndexFor(const K &key) const
    {
        int bucketIndex = hashKey(key);
        int currentIndex = bucketIndex;

        while (buckets[currentIndex] != nullptr)
        {
            if (buckets[currentIndex]->key == key)
            {
                return currentIndex;
            }
            ++currentIndex;
            if (currentIndex >= bucketCount)
                currentIndex = 0;
            if (currentIndex == bucketIndex)
            {
                // we came full circle, let's exit
                return std::nullopt;
            }
        }

        return std::nullopt;
    }

    template <typename K, typename V>
    void OpenAddressingHashMap<K, V>::insert(std::pair<K, V> kv)
    {
        auto [key, value] = kv;
        auto itemIndex = this->getBucketIndexFor(key);
        if (itemIndex.has_value())
        {
            // we already located an existing key in the hashmap
            // can just overwrite the value; no need to conduct linear probing to find a new bucket
            buckets[itemIndex.value()]->value = value;
            return;
        }

        // let's find a home for this new key
        int bucketIndex = hashKey(key);
        int currentIndex = bucketIndex;

        while (buckets[currentIndex] != nullptr)
        {
            ++currentIndex;
            if (currentIndex >= bucketCount)
                currentIndex = 0;
            if (currentIndex == bucketIndex)
            {
                break;
            }
        }

        // currentIndex == bucketIndex gives rise to 2 possibilities:
        // 1. we cycled our currentIndex throughout our entire buckets array -> no space at all
        // 2. this current bucket is already empty
        if (currentIndex == bucketIndex && buckets[currentIndex] != nullptr)
        {
            return;
        }

        ++totalElements;
        buckets[currentIndex] = new HashMapItem<K, V>(key, value);
        rebalance();
    }

    template <typename K, typename V>
    V &OpenAddressingHashMap<K, V>::operator[](K key)
    {
        auto itemIndex = this->getBucketIndexFor(key);
        if (itemIndex.has_value())
        {
            return buckets[itemIndex.value()]->value;
        }

        // Let's follow C++ convention of auto construction of default values
        this->insert(std::pair<K, V>(key, V()));
        auto newItemIndex = this->getBucketIndexFor(key);
        if (!newItemIndex.has_value())
        {
            // http://stackoverflow.com/questions/57908992/better-alternatives-to-assertfalse-in-c-c
            __builtin_unreachable();
        }

        return buckets[newItemIndex.value()]->value;
    }

    template <typename K, typename V>
    void OpenAddressingHashMap<K, V>::remove(K key)
    {
        auto itemIndex = this->getBucketIndexFor(key);
        if (itemIndex.has_value())
        {
            --totalElements;
            buckets[itemIndex.value()] = nullptr;
        }
    }

    template <typename K, typename V>
    size_t OpenAddressingHashMap<K, V>::size() const
    {
        return totalElements;
    }

    template <typename K, typename V>
    size_t OpenAddressingHashMap<K, V>::getBucketCount() const
    {
        return bucketCount;
    }

} // namespace benn

/*
    Realized it might more useful to might be more useful to return bucketIndex instead of the object pointer
    template <typename K, typename V>
    HashMapItem<K, V> *OpenAddressingHashMap<K, V>::find(const K &key) const
    {
        int bucketIndex = hashKey(key);
        int currentIndex = bucketIndex;

        while (buckets[currentIndex] != nullptr)
        {
            if (buckets[currentIndex]->key == key)
            {
                return buckets[currentIndex];
            }
            ++currentIndex;
            if (currentIndex >= bucketCount)
                currentIndex = 0;
            if (currentIndex == bucketIndex)
            {
                // we came full circle, let's exit
                return nullptr;
            }
        }

        return nullptr;
    }
*/

#endif // OPEN_ADDRESSING_HASHMAP_H