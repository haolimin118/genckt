#include "ClockTreeRCLink.h"
#include <iostream>
#include <cmath>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

ClockTreeRCLink::ClockTreeRCLink(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

ClockTreeRCLink::~ClockTreeRCLink()
{
    m_ss.clear();
    m_ss.str("");
}

int ClockTreeRCLink::Generate(ofstream &fout)
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

int ClockTreeRCLink::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    string vsrc = "Vsrc 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG + " " + V_TRAN_PULSE; // vsrc
    m_ss << vsrc << "\n";

    string r = "R2 1 2 " + STR(RVAL); // R2
    m_ss << r << "\n";

    string c = "C2 2 0 " + STR(CVAL); // C2
    m_ss << c << "\n";

    r = "R3 2 3 " + STR(RVAL); // R3
    m_ss << r << "\n";

    c = "C3 3 0 " + STR(CVAL); // C3
    m_ss << c << "\n";

    r = "R4 2 4 " + STR(RVAL); // R4
    m_ss << r << "\n";

    c = "C4 4 0 " + STR(CVAL); // C4
    m_ss << c << "\n";

    r = "R5 3 5 " + STR(RVAL); // R5
    m_ss << r << "\n";

    c = "C5 5 0 " + STR(CVAL); // C5
    m_ss << c << "\n";

    r = "R6 3 6 " + STR(RVAL); // R6
    m_ss << r << "\n";

    c = "C6 6 0 " + STR(CVAL); // C6
    m_ss << c << "\n";

    r = "R7 4 7 " + STR(RVAL); // R7
    m_ss << r << "\n";

    c = "C7 7 0 " + STR(CVAL); // C7
    m_ss << c << "\n";

    r = "R8 4 8 " + STR(RVAL); // R8
    m_ss << r << "\n";

    c = "C8 8 0 " + STR(CVAL); // C8
    m_ss << c << "\n";

    r = "R9 5 9 " + STR(RVAL); // R9
    m_ss << r << "\n";

    c = "C9 9 0 " + STR(CVAL); // C9
    m_ss << c << "\n";

    r = "R10 5 10 " + STR(RVAL); // R10
    m_ss << r << "\n";

    c = "C10 10 0 " + STR(CVAL); // C10
    m_ss << c << "\n";

    r = "R11 6 11 " + STR(RVAL); // R11
    m_ss << r << "\n";

    c = "C11 11 0 " + STR(CVAL); // C11
    m_ss << c << "\n";

    r = "R12 6 12 " + STR(RVAL); // R12
    m_ss << r << "\n";

    c = "C10 12 0 " + STR(CVAL); // C12
    m_ss << c << "\n";

    m_outs.push_back(STR(1));
    m_outs.push_back(STR(2));
    m_outs.push_back(STR(3));
    m_outs.push_back(STR(4));
    m_outs.push_back(STR(5));
    m_outs.push_back(STR(6));
    m_outs.push_back(STR(7));
    m_outs.push_back(STR(8));
    m_outs.push_back(STR(9));
    m_outs.push_back(STR(10));
    m_outs.push_back(STR(11));
    m_outs.push_back(STR(12));

    /* adaptive part */
    int maxH = MAX_H_LENGTH;
    if (maxH == 0) {
        r = "R13 9 10 " + STR(RVAL);
        m_ss << r << "\n\n";
        return OKAY;
    }

    int rIndex = 13, cIndex = 13;
    int nodeIndex = 13, posNodeIndex = 0, negNodeIndex = 0;

    if (maxH == 1) {
        for (int i = 0; i < m_scale; ++ i) {
            posNodeIndex = 9;
            negNodeIndex = nodeIndex + i;
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n";
            c = "C" + STR(cIndex++) + " " + STR(negNodeIndex) + " " + "0" + " " + STR(CVAL);
            m_ss << c << "\n";
        }
        for (int i = 0; i < m_scale; ++ i) {
            posNodeIndex = 10;
            negNodeIndex = nodeIndex + m_scale + i;
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n";
            c = "C" + STR(cIndex++) + " " + STR(negNodeIndex) + " " + "0" + " " + STR(CVAL);
            m_ss << c << "\n";
        }
        r = "R" + STR(rIndex++) + " " + "9" + " " + "10" + " " + STR(RVAL);
        m_ss << r << "\n";

        return OKAY;
    }

    for (int i = 0; i < m_scale; ++ i) {
        posNodeIndex = 9;
        negNodeIndex = nodeIndex + i;
        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";
        c = "C" + STR(cIndex++) + " " + STR(negNodeIndex) + " " + "0" + " " + STR(CVAL);
        m_ss << c << "\n";
    }
    for (int i = 0; i < m_scale; ++ i) {
        posNodeIndex = 10;
        negNodeIndex = nodeIndex + m_scale + i;
        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";
        c = "C" + STR(cIndex++) + " " + STR(negNodeIndex) + " " + "0" + " " + STR(CVAL);
        m_ss << c << "\n";
    }

    r = "R" + STR(rIndex++) + " " + "9" + " " + "10" + " " + STR(RVAL);
    m_ss << r << "\n";

    int nodeCount = 2 * m_scale;
    for (int i = 2; i <= maxH; ++ i) {
        for (int j = 0; j < nodeCount; ++ j) {
            posNodeIndex = nodeIndex + j;
            negNodeIndex = nodeIndex + nodeCount + j;
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n";
            c = "C" + STR(cIndex++) + " " + STR(negNodeIndex) + " " + "0" + " " + STR(CVAL);
            m_ss << c << "\n";
        }

        /* extra R link */
        posNodeIndex = nodeIndex + m_scale - 1;
        negNodeIndex = nodeIndex + m_scale;

        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";

        nodeIndex += nodeCount;
    }

    return OKAY;
}

int ClockTreeRCLink::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "VIN" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            break;
        case TRAN:
            m_ss << ".TRAN" << " " << TSTEP << " " << TSTOP << " "
                 << TSTART << "\n";
            break;
        default:;
    }

    m_ss << ".SAVE ";
    for (size_t i = 0; i < m_outs.size(); ++ i) 
        m_ss << "V(" << m_outs.at(i) << ") ";
    m_ss << "\n";

    m_ss << ".end" << "\n";

    return OKAY;
}
