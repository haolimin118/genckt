#include "ClockTreeR.h"
#include <iostream>
#include <cmath>
#include "Utilities/MyString.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

ClockTreeR::ClockTreeR(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

ClockTreeR::~ClockTreeR()
{
    m_ss.clear();
}

int ClockTreeR::Generate(ofstream &fout)
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

int ClockTreeR::GenerateCkt()
{
    string vsrc = "VIN 1 0 1";
    m_ss << vsrc << "\n";

    int maxH = MAX_H_LENGTH;
    if (maxH == 0) {
        string r0 = "R0 1 0 100";
        m_ss << r0 << "\n";
        m_ss << "\n";
        return OKAY; 
    }
    
    string r;
    int i = 0;
    int rIndex = 1, rCount = 0, rPrevCount = 0;
    int nodeIndex = 2;
    int posNodeIndex = 0, negNodeIndex = 0;
    int fanout = m_scale;

    string r0 = "R0 1 2 100";
    m_ss << r0 << "\n";

    for (i = 1; i < maxH; ++ i) {

        rCount = pow(fanout, i);
        rPrevCount = pow(fanout, i - 1);

        for (int j = 0; j < rCount; ++ j) {
            posNodeIndex = j / fanout + nodeIndex;
            negNodeIndex = nodeIndex + rPrevCount + j;
            r = "R" + STR(rIndex) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + "100";
            m_ss << r << "\n";
            rIndex++;
        }

        nodeIndex += rPrevCount;
    }

    /* i == maxH, negNodeIndex = 0 (ground) */
    rCount = pow(fanout, i);
    for (int j = 0; j < rCount; ++ j) {
        posNodeIndex = j / fanout + nodeIndex;
        negNodeIndex = 0;
        r = "R" + STR(rIndex) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + "100";
        m_ss << r << "\n";
        rIndex++;
    }

    return OKAY;
}

int ClockTreeR::GenerateCmd()
{
    m_ss << ".OP" << "\n";
    m_ss << ".ENDS" << "\n";
    return OKAY;
}
