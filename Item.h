#pragma once

struct Item
{
    int weight;
    int volume;
    int value;

    Item(int w, int vol, int val) : weight(w), volume(vol), value(val) {}
    Item() : weight(0), volume(0), value(0) {}

    bool operator==(const Item& other) const
    {
        return (other.weight == weight &&
            other.volume == volume &&
            other.value == value);
    }
    bool operator!=(const Item& other) const
    {
        return !(*this == other);
    }
};
