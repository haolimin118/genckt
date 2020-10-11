#include "Utils.h"
#include <assert.h>
#include <stdlib.h>

using std::vector;

int RandomInt(int min, int max)
{
    assert(min >= 0 && max >= 0);
    if (min > max) {
        int tmp = min;
        min = max;
        max = tmp;
    }

    return (rand() % (max-min+1)) + min;
}

int VectorSum(const vector<int> &vec)
{
    int sum = 0;
    for (int i = 0; i < vec.size(); ++ i) {
        sum += vec.at(i);
    }
    return sum;
}
