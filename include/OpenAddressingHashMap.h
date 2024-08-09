#ifndef OPEN_ADDRESSING_HASHMAP_H
#define OPEN_ADDRESSNING_HASHMAP_H

#include <algorithm>
namespace benn
{
    template <typename K, typename V>
    class OpenAddressingHashMap
    {
    public:
        void insert(std::pair<int, int> kv);
        void remove(K key);

    private:
        V buckets;
        int bucketCount;
        int totalElements;
    };

} // namespace benn

#endif // OPEN_ADDRESSING_HASHMAP_H