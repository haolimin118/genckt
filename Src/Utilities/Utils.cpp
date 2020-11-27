#include "Utils.h"
#include <assert.h>
#include <stdlib.h>
#include <random>
#include <ctime>

using namespace std;

static default_random_engine e(time(0));

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
    for (size_t i = 0; i < vec.size(); ++ i) {
        sum += vec.at(i);
    }
    return sum;
}

double RandomDouble(double min, double max)
{
    uniform_real_distribution<double> u(min, max);
    return u(e);
}
