#include "ClockTreeRC.h"
#include <iostream>
#include <cmath>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

ClockTreeRC::ClockTreeRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
    m_outIndex = 0;
}

ClockTreeRC::~ClockTreeRC()
{
}

int ClockTreeRC::Generate(ofstream &fout)
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

int ClockTreeRC::GenerateCkt()
{
    string vsrc = "VIN 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG;
    m_ss << vsrc << "\n";

    int maxH = MAX_H_LENGTH;
    if (maxH == 0) {
        string r0 = "R0 1 2 " + STR(RVAL);
        string c0 = "C0 2 0 " + STR(CVAL);
        m_ss << r0 << "\n";
        m_ss << c0 << "\n";
        m_ss << "\n";
        return OKAY;
    }

    string r, c;
    int rIndex = 1, rCount = 0, rPrevCount = 0; // the same as cap
    int nodeIndex = 2;
    int posNodeIndex = 0, negNodeIndex = 0;
    int fanout = m_scale;

    string r0 = "R0 1 2 " + STR(RVAL);
    string c0 = "C0 2 0 " + STR(CVAL);
    m_ss << r0 << "\n";
    m_ss << c0 << "\n";

    for (int i = 1; i <= maxH; ++ i) {
        rCount = pow(fanout, i);
        rPrevCount = pow(fanout, i - 1);
        for (int j = 0; j < rCount; ++ j) {
            posNodeIndex = j / fanout + nodeIndex;
            negNodeIndex = nodeIndex + rPrevCount + j;
            r = "R" + STR(rIndex) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            c = "C" + STR(rIndex) + " " + STR(negNodeIndex) + " " + "0" + " " + STR(CVAL);
            m_ss << r << "\n";
            m_ss << c << "\n";
            rIndex++;
            m_outIndex = posNodeIndex;
        }

        nodeIndex += rPrevCount;
    }

    return OKAY;
}

int ClockTreeRC::GenerateCmd()
{
    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            m_ss << ".SAVE V(" << m_outIndex << ")" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "VIN" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            m_ss << ".SAVE V(" << m_outIndex << ")" << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            m_ss << ".SAVE V(" << m_outIndex << ")" << "\n";
            break;
        case TRAN:
            break;
    }

    m_ss << ".end" << "\n";

    return OKAY;
}
