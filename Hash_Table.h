#pragma once

#include <functional>
#include "Container_For_Unique_Pointer.h"
#include "IDictionary.h"
#include "UniquePointer.h"

template <typename K, typename V>
class HashNode
{
public:
    K key;
    V value;
    HashNode(K k, V v) : key(k), value(v) {}
};

template <typename K, typename V, typename HashFunc = std::hash<K>>
class HashTable : public IDictionary<K, V>
{
private:
    ContainerForUniquePtr< UniquePtr< HashNode<K, V> > > storage_;
    int capacity_;
    int currentSize_;
    HashFunc hasher_;

    int CalculateHashIndex(const K& k) const
    {
        return static_cast<int>(hasher_(k) % capacity_);
    }
    void ResizeInner(int newCap)
    {
        int oldCap = capacity_;
        capacity_ = newCap;
        ContainerForUniquePtr< UniquePtr< HashNode<K, V> > > newStore(capacity_);

        for (int i = 0; i < oldCap; i++)
        {
            if (storage_[i].Get())
            {
                int newIndex = static_cast<int>(hasher_(storage_[i].Get()->key) % capacity_);
                while (newStore[newIndex].Get())
                    newIndex = (newIndex + 1) % capacity_;
                newStore[newIndex] = std::move(storage_[i]);
            }
        }
        storage_ = std::move(newStore);
    }

public:
    explicit HashTable(int initCap = 20)
    {
        int validatedCap = (initCap <= 0) ? 20 : initCap;
        capacity_ = validatedCap;
        currentSize_ = 0;
        storage_ = ContainerForUniquePtr< UniquePtr< HashNode<K, V> > >(capacity_);
    }
    ~HashTable() override = default;

    // Реализация IDictionary
    void Add(const K& key, const V& value) override
    {
        if (currentSize_ >= capacity_ * 0.7)
            ResizeInner(capacity_ * 2);

        int index = CalculateHashIndex(key);

        while (storage_[index].Get())
        {
            if (storage_[index].Get()->key == key)
            {
                storage_[index].Get()->value = value;
                return;
            }
            index = (index + 1) % capacity_;
        }

        storage_[index] = UniquePtr<HashNode<K, V>>(new HashNode<K, V>(key, value));
        currentSize_++;
    }

    void Remove(const K& key) override
    {
        int index = CalculateHashIndex(key);

        while (storage_[index].Get())
        {
            if (storage_[index].Get()->key == key)
            {
                storage_[index].Reset();
                currentSize_--;

                int nextPos = (index + 1) % capacity_;
                while (storage_[nextPos].Get())
                {
                    auto tempNode = std::move(storage_[nextPos]);
                    storage_[nextPos].Reset();
                    currentSize_--;
                    Add(tempNode->key, tempNode->value);
                    nextPos = (nextPos + 1) % capacity_;
                }

                if (currentSize_ <= capacity_ / 4 && capacity_ > 20)
                    ResizeInner(capacity_ / 2);

                return;
            }
            index = (index + 1) % capacity_;
        }
    }

    std::optional<V> GetValue(const K& key) const override
    {
        int index = CalculateHashIndex(key);

        while (storage_[index].Get())
        {
            if (storage_[index].Get()->key == key)
                return storage_[index].Get()->value;
            index = (index + 1) % capacity_;
        }
        return std::nullopt;
    }

    bool ContainsKey(const K& key) const override
    {
        return GetValue(key).has_value();
    }

    int GetCount() const override
    {
        return currentSize_;
    }
    int GetCapacity() const override
    {
        return capacity_;
    }

 
    bool IsEmpty() const
    {
        return (currentSize_ == 0);
    }
    bool IndexContains(int idx) const
    {
        if (idx < 0 || idx >= capacity_)
            return false;
        return (storage_[idx].Get() != nullptr);
    }
    K& GetKeyByIndex(int idx) const
    {
        return storage_[idx].Get()->key;
    }
    V& GetValueByIndex(int idx) const
    {
        return storage_[idx].Get()->value;
    }
};
