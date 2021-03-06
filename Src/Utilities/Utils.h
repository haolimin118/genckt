#ifndef GENCKT_UTILITIES_UTILS_H
#define GENCKT_UTILITIES_UTILS_H

#include <vector>

/* return random number in [min, max] */
extern int RandomInt(int min, int max);

extern int VectorSum(const std::vector<int> &vec);

extern double RandomDouble(double min, double max);

#endif // GENCKT_UTILITIES_UTILS_H
