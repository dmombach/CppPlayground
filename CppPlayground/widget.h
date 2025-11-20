#pragma once
#include <memory>

class widget
{
private:
    std::unique_ptr<int[]> data;
    int weight = 0;
public:
    widget(const int size) { data = std::make_unique<int[]>(size); }
    void do_something() {}
    int get_weight() const { return weight; }
};
