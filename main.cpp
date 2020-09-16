#include <iostream>
#include <vector>
#include <map>
#include "allocator.h"
#include "List.h"

using namespace std;

template <typename L>
void print(L& _l, const char* _name)
{
    cout << _name << endl;
    auto begin = _l.begin();
    auto end = _l.end();

    while(begin != end)
    {
        cout << begin->m_value << endl;
        ++begin;
    }
    cout << endl;
}

template <typename B, typename E>
void print(B _begin, E _end, const char* _name)
{
    cout << _name << endl;
    while (_begin != _end)
    {
        cout << _begin->first << " " << _begin->second << endl;
        ++_begin;
    }
    cout << endl;
}

int main()
{
    int factorial[] = {1,1,2,3,4,5,6,7,8,9};
    for (int ix = 1; ix < 10; ++ix)
    {
        factorial[ix] *= (factorial[ix - 1]);
    }
    factorial[0] = 0;

    map<int, int> m;
    map<int, int, less<int>, user_allocator<pair<int, int>, 10>> mu;

    for (int ix = 0; ix < 10; ++ix)
    {
        m.insert(pair<const int, int>(ix, factorial[ix]));
        mu.insert(pair<const int, int>(ix, factorial[ix]));
    }

    print(m.begin(), m.end(), "map with std::allocator");
    print(m.begin(), m.end(), "map with user_allocator");

    List<int> l(0);
    List<int, user_allocator<int, 10>> lu(0);

    for (int ix = 1; ix < 10; ++ix)
    {
        l.add(factorial[ix]);
        lu.add(factorial[ix]);
    }

    print(l, "list with std::allocator");
    print(lu, "list with user_allocator");

    return 0;
}

//struct x_ray
//{
//    int i;
//    x_ray (int _i) : i(_i)
//    {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }

//    x_ray (x_ray& _ray) : i(_ray.i)
//    {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }

//    x_ray (x_ray&& _ray) : i(_ray.i)
//    {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }

//    ~x_ray()
//    {
//        cout << __PRETTY_FUNCTION__ << endl;
//    }
//};
