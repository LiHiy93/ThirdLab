#pragma once

#include <optional>

template <typename KeyType, typename ValType>
class IDictionary
{
public:
    virtual ~IDictionary() = default;

    virtual int GetCount() const = 0;
    virtual int GetCapacity() const = 0;

    virtual std::optional<ValType> GetValue(const KeyType& key) const = 0;
    virtual bool ContainsKey(const KeyType& key) const = 0;

    virtual void Add(const KeyType& key, const ValType& element) = 0;
    virtual void Remove(const KeyType& key) = 0;
};
