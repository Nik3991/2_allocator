#include <iostream>
#include <vector>
#include <map>
#include "allocator.h"
#include "List.h"

using namespace std;

struct x_ray
{
    int i;
    x_ray (int _i) : i(_i)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    x_ray (x_ray& _ray) : i(_ray.i)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    x_ray (x_ray&& _ray) : i(_ray.i)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    ~x_ray()
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

int main()
{
    vector<x_ray, user_allocator<x_ray, 10>> v;
    v.reserve(10);
    map<int, int> m;

    v.push_back(x_ray(100));

    List<int, user_allocator<int, 10>> l(1);
    for (int ix = 0; ix < 11; ++ix)
    {
        l.add(ix);
    }

    return 0;
}
