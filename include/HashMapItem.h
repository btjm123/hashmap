#ifndef HASHMAP_ITEM_H
#define HASHMAP_ITEM_H

#include <iostream>
namespace benn
{
    template <typename K, typename V>
    class HashMapItem
    {
    public:
        K key;
        V value;
        HashMapItem(K key, V value);
    };

    template <typename K, typename V>
    HashMapItem<K, V>::HashMapItem(K key, V value)
    {
        this->key = key;
        this->value = value;
    }
}
#endif // HASHMAP_ITEM_H