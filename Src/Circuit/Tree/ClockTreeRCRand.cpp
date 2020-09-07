#include "ClockTreeRCRand.h"
#include <time.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;
using std::vector;

ClockTreeRCRand::ClockTreeRCRand(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

ClockTreeRCRand::~ClockTreeRCRand()
{
    m_ss.clear();
}

int ClockTreeRCRand::Generate(ofstream &fout)
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    int error = GenerateCkt();
    if (error)
        return ERROR;

    error = GenerateCmd();
    if (error)
        return ERROR;

    fout << "*" << m_title << "\n\n";
    fout << m_ss.str();

    return OKAY;
}

int ClockTreeRCRand::GenerateCkt()
{
    srand((int)time(0)); // random number seed

    string vsrc = "VIN 1 0 1";
    m_ss << vsrc << "\n";

    int maxH = MAX_H_LENGTH;
    if (maxH == 0) {
        string r0 = "R0 1 2 100";
        string c0 = "C0 2 0 1p";
        m_ss << r0 << "\n";
        m_ss << c0 << "\n";
        m_ss << "\n";
        return OKAY;
    }

    string r0 = "R0 1 2 100";
    string c0 = "C0 2 0 1p";
    m_ss << r0 << "\n";
    m_ss << c0 << "\n";

    string r, c;
    int nodeIndex = 2;
    int rIndex = 1;
    vector<int> fanoutList, prevFanoutList;
    int i = 0, k = 0;
    int prevFanoutSum = 0;
    int maxFanout = m_scale, minFanout = 1;
    int posNodeIndex = 0, negNodeIndex = 0;
    int currLevelRIndex = 0;

    prevFanoutList.push_back(1);

    for (i = 1; i <= maxH; ++ i) {
        /* generate current fanout list */
        prevFanoutSum = VectorSum(prevFanoutList);
        for (int j = 0; j < prevFanoutSum; ++ j)
            fanoutList.push_back(RandomInt(minFanout, maxFanout));

        currLevelRIndex = 0;
        for (int j = 0; j < fanoutList.size(); ++ j) {
            k = fanoutList.at(j);
            for (int m = 0; m < k; ++ m) {
                posNodeIndex = nodeIndex + j;
                negNodeIndex = nodeIndex + prevFanoutSum + currLevelRIndex;
                r = "R" + STR(rIndex) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + "100";
                c = "C" + STR(rIndex) + " " + STR(negNodeIndex) + " " + STR(0) + " " + "1p";
                currLevelRIndex++;
                rIndex++;
                m_ss << r << "\n";
                m_ss << c << "\n";
            }
        }

        nodeIndex += prevFanoutSum;
        prevFanoutList = fanoutList;
        fanoutList.clear();
    }

    return OKAY;
}

int ClockTreeRCRand::GenerateCmd()
{
    m_ss << ".OP" << "\n";
    m_ss << ".ENDS" << "\n";

    return OKAY;
}
