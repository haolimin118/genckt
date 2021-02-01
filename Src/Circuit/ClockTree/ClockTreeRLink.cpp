#include "ClockTreeRLink.h"
#include <iostream>
#include <cmath>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

ClockTreeRLink::ClockTreeRLink(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

ClockTreeRLink::~ClockTreeRLink()
{
    m_ss.clear();
    m_ss.str("");
}

int ClockTreeRLink::Generate(ofstream &fout)
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

#if 0
int ClockTreeRLink::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    string vsrc = "VIN 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG + " " + V_TRAN_SIN; // vsrc
    m_ss << vsrc << "\n";

    string r = "R0 1 2 " + STR(RVAL); // R0
    m_ss << r << "\n";

    r = "R1 2 3 " + STR(RVAL); // R1
    m_ss << r << "\n";

    r = "R2 2 4 " + STR(RVAL); // R2
    m_ss << r << "\n";

    r = "R3 3 5 " + STR(RVAL); // R3
    m_ss << r << "\n";

    r = "R4 3 6 " + STR(RVAL); // R4
    m_ss << r << "\n";

    r = "R5 4 0 " + STR(RVAL); // R5
    m_ss << r << "\n";

    r = "R6 4 0 " + STR(RVAL); // R6
    m_ss << r << "\n";

    r = "R7 5 7 " + STR(RVAL); // R7
    m_ss << r << "\n";

    r = "R8 5 8 " + STR(RVAL); // R8
    m_ss << r << "\n";

    r = "R9 6 0 " + STR(RVAL); // R9
    m_ss << r << "\n";

    r = "R10 6 0 " + STR(RVAL); // R10
    m_ss << r << "\n";

    m_outs.push_back(STR(1));
    m_outs.push_back(STR(2));
    m_outs.push_back(STR(3));
    m_outs.push_back(STR(4));
    m_outs.push_back(STR(5));
    m_outs.push_back(STR(7));
    m_outs.push_back(STR(8));

    /* adaptive part */
    int maxH = MAX_H_LENGTH;
    int flag = 0;
    if (maxH == 0) {
        r = "R11 7 8 " + STR(RVAL);
        m_ss << r << "\n\n";
        return OKAY;
    }

    int rIndex = 11, rCount = 0, rPrevCount = 0;
    int nodeIndex = 7, posNodeIndex = 0, negNodeIndex = 0;
    int fanout = m_scale; // scale -> fanout

    int i = 0;
    for (i = 1; i < maxH; ++ i) {
        rPrevCount = pow(fanout, i);
        rCount = rPrevCount * fanout;

        for (int j = 0; j < rCount; ++ j) {
            posNodeIndex = j / fanout + nodeIndex;
            negNodeIndex = nodeIndex + rPrevCount + j;
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n"; 
        }

        /* extra R links */
        flag = 1;
        for (int j = 0; j < rPrevCount - 1; ++ j) {
            posNodeIndex = j + nodeIndex;
            negNodeIndex = j + nodeIndex + 1;
            if (flag) {
                r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
                m_ss << r << "\n";
            }
            // flag = 1 - flag;
        }

        nodeIndex += rPrevCount;
    }

    /* i == maxH, negNodeIndex = 0 (ground) */
    negNodeIndex = 999999999;
    rCount = pow(fanout, i+1);
    for (int j = 0; j < rCount; ++ j) {
        posNodeIndex = j / fanout + nodeIndex;
        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";
    }

    // extra R links
    flag = 1;
    rPrevCount = pow(fanout, i);
    for (int j = 0; j < rPrevCount - 1; ++ j) {
        posNodeIndex = j + nodeIndex;
        negNodeIndex = j + nodeIndex + 1;
        if (flag) {
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n";
        }
        // flag = 1 - flag;
    }

    return OKAY;
}
#endif

int ClockTreeRLink::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    string vsrc = "VIN 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG + " " + V_TRAN_SIN; // vsrc
    m_ss << vsrc << "\n";

    string r = "R0 1 2 " + STR(RVAL); // R0
    m_ss << r << "\n";

    r = "R1 2 3 " + STR(RVAL); // R1
    m_ss << r << "\n";

    r = "R2 2 4 " + STR(RVAL); // R2
    m_ss << r << "\n";

    r = "R3 3 5 " + STR(RVAL); // R3
    m_ss << r << "\n";

    r = "R4 3 6 " + STR(RVAL); // R4
    m_ss << r << "\n";

    r = "R5 4 0 " + STR(RVAL); // R5
    m_ss << r << "\n";

    r = "R6 4 0 " + STR(RVAL); // R6
    m_ss << r << "\n";

    r = "R7 5 7 " + STR(RVAL); // R7
    m_ss << r << "\n";

    r = "R8 5 8 " + STR(RVAL); // R8
    m_ss << r << "\n";

    r = "R9 6 0 " + STR(RVAL); // R9
    m_ss << r << "\n";

    r = "R10 6 0 " + STR(RVAL); // R10
    m_ss << r << "\n";

    m_outs.push_back(STR(1));
    m_outs.push_back(STR(2));
    m_outs.push_back(STR(3));
    m_outs.push_back(STR(4));
    m_outs.push_back(STR(5));
    m_outs.push_back(STR(7));
    m_outs.push_back(STR(8));

    /* adaptive part */
    int maxH = MAX_H_LENGTH;
    if (maxH == 0) {
        r = "R11 7 8 " + STR(RVAL);
        m_ss << r << "\n\n";
        return OKAY;
    }

    int rIndex = 11;

    if (maxH == 1) {
        for (int i = 0; i < m_scale; ++ i) {
            r = "R" + STR(rIndex++) + " " + "7" + " " + "0" + " " + STR(RVAL);
            m_ss << r << "\n";
        }
        for (int i = 0; i < m_scale; ++ i) {
            r = "R" + STR(rIndex++) + " " + "8" + " " + "0" + " " + STR(RVAL);
            m_ss << r << "\n";
        }
        r = "R" + STR(rIndex++) + " " + "7" + " " + "8" + " " + STR(RVAL);
        m_ss << r << "\n";

        return OKAY;
    }

    int nodeIndex = 9, posNodeIndex = 0, negNodeIndex = 0;
    int nodeCount = 0;

    for (int i = 0; i < m_scale; ++ i) {
        posNodeIndex = 7;
        negNodeIndex = nodeIndex + i;
        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";
    }

    for (int i = 0; i < m_scale; ++ i) {
        posNodeIndex = 8;
        negNodeIndex = nodeIndex + m_scale + i;
        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";
    }

    r = "R" + STR(rIndex++) + " " + "7" + " " + "8" + " " + STR(RVAL);
    m_ss << r << "\n";


    int randomNum = 0;
    nodeCount = 2 * m_scale;
    for (int i = 2; i < maxH; ++ i) {
        for (int j = 0; j < nodeCount; ++ j) {
            posNodeIndex = nodeIndex + j;
            negNodeIndex = nodeIndex + nodeCount + j;
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n";
        }

        /* extra R link */
        for (int j = 0; j < nodeCount - 1; ++ j) {
            posNodeIndex = nodeIndex + j;
            negNodeIndex = nodeIndex + j + 1;
            randomNum = RandomInt(1, 100);
            if (randomNum % P_RLINK == 0) {
                r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
                m_ss << r << "\n";
            }
        }

        nodeIndex += nodeCount;
    }

    /* i == maxH */
    for (int j = 0; j < nodeCount; ++ j) {
        posNodeIndex = nodeIndex + j;
        negNodeIndex = 0;
        r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
        m_ss << r << "\n";
    }

    /* extra R link */
    for (int j = 0; j < nodeCount - 1; ++ j) {
        posNodeIndex = nodeIndex + j;
        negNodeIndex = nodeIndex + j + 1;
        randomNum = RandomInt(1, 100);
        if (randomNum % P_RLINK == 0) {
            r = "R" + STR(rIndex++) + " " + STR(posNodeIndex) + " " + STR(negNodeIndex) + " " + STR(RVAL);
            m_ss << r << "\n";
        }
    }

    return OKAY;
}

int ClockTreeRLink::GenerateCmd()
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
