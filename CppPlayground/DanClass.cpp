#include "DanClass.h"
#include "widget.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <list>

// TESTS AND PIECES OF CODE 

void functionUsingWidget()
{
    widget w(1000000);  // lifetime automaticalle tied to enclosing scope
    // construct w, including the w.data gadget member
// ...
    w.do_something();
    // ...
} // automatic destruction and deallocation for w and w.data

struct S
{
    std::string name;
    float num;
    S(std::string s, float f) : name(s), num(f) {}
};

void testCoding()
{
    std::vector<std::string> apples;
    apples.push_back("Granny Smith");

    std::map<std::string, std::string> apple_color;
    apple_color["Granny Smith"] = "Green";

    std::vector<widget> v;
    
    auto comp = [](const widget& w1, const widget& w2)
        { return w1.get_weight() < w2.get_weight(); }; 

    sort(v.begin(), v.end(), comp);

    auto i = lower_bound(v.begin(), v.end(), widget{ 0 }, comp);

    auto j = apples.begin();

    std::vector<int> u { 1,2,3 };

    for (auto& num : u)
    {
        std::cout << num << std::endl;
    }

    constexpr int size = 10; // size is a compile-time constant here 

    S s1("Norah", 2.7f);
    S s2("Frank", 3.5f);
    S s3("Jeri", 85.9f);

    std::vector<S> vec{s1, s2, s3};

    // or ... 
    std::vector<S> vec2{ {"Norah", 2.7f}, {"Frank", 3.5f}, {"Jeri", 85.9f} };
}
