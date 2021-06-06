#include "ClockTreeRLC.h"
#include <iostream>
#include <cmath>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;
using std::vector;

ClockTreeRLC::ClockTreeRLC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
}

ClockTreeRLC::~ClockTreeRLC()
{
    m_outs.clear();
    m_outs.shrink_to_fit();
}

int ClockTreeRLC::Generate(ofstream &fout)
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

int ClockTreeRLC::GenerateCkt()
{
    string vsrc = "vin 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG + " " + V_AC_PHASE + " " + V_TRAN_PULSE;
    string rv   = "Rv " + STR(1) + " " + STR(2) + " " + STR(RV);
    string cv   = "Cv " + STR(2) + " " + STR(0) + " " + STR(CV);
    string rp   = "Rp " + STR(2) + " " + STR(3) + " " + STR(RVAL);
    m_ss << vsrc << "\n" << rv << "\n" << cv << "\n" << rp << "\n";

    string r, c, l;
    int rIndex = 0, cIndex = 0, lindex = 0;
    int nodeIndex = 3;
    const int fanout = 2;
    int numCsec = 0;

    // the horizontal part, i = 0
    c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
    r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
    l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
    nodeIndex += 2;
    m_ss << c << "\n" << r << "\n" << l << "\n";
    c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
    r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
    l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
    nodeIndex += 2;
    m_ss << c << "\n" << r << "\n" << l << "\n";
    vector<int> currCstarts, nextCstarts;
    currCstarts.push_back(nodeIndex);

    for (int i = 1; i < m_scale; ++ i) {
        numCsec = pow(fanout, i-1);
        for (int j = 0; j < numCsec; ++ j) {
            // the top half
            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";


            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";

            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";

            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";

            nextCstarts.push_back(nodeIndex);

            // the bottom half
            r = "R" + STR(rIndex++) + " " + STR(currCstarts.at(j)) + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << r << "\n" << l << "\n";

            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";

            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";

            c = "C" + STR(cIndex++) + " " + STR(nodeIndex)   + " " + STR(0) + " " + STR(CVAL);
            r = "R" + STR(rIndex++) + " " + STR(nodeIndex)   + " " + STR(nodeIndex+1) + " " + STR(RVAL);
            l = "L" + STR(lindex++) + " " + STR(nodeIndex+1) + " " + STR(nodeIndex+2) + " " + STR(LVAL);
            nodeIndex += 2;
            m_ss << c << "\n" << r << "\n" << l << "\n";

            nextCstarts.push_back(nodeIndex);
        }

        currCstarts = nextCstarts;
        nextCstarts.clear();
    }

    // i == m_scale
    nextCstarts.clear();
    for (size_t i = 0; i < currCstarts.size(); ++ i) {
        int index = currCstarts.at(i);
        r = "R" + STR(rIndex++) + " " + STR(index)   + " " + STR(index+1) + " " + STR(RLOAD);
        c = "C" + STR(cIndex++) + " " + STR(index+1) + " " + STR(0) + " " + STR(CLOAD);
        m_ss << r << "\n" << c << "\n";
        nextCstarts.push_back(index+1);
    }

    currCstarts = nextCstarts;

    // for output
    for (size_t i = 0; i < currCstarts.size(); ++ i) {
        if ((i) % 4 == 0) {
            m_outs.push_back(currCstarts.at(i));
        }
    }

    m_ss << "\n";

    return OKAY;
}

int ClockTreeRLC::GenerateCmd()
{
    // preserved nodes
    m_ss << ".save " << "V(" << 1 << ")" << " " << "V(" << 2 << ")" << " " << "V(" << 3 << ")" << " ";
    for (size_t i = 0; i < m_outs.size(); ++ i)
        m_ss << "V(" << m_outs.at(i) << ")" << " ";
    m_ss << "\n";

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "Vin" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            break;
        case TRAN:
            m_ss << ".tran" << " " << TSTEP << " " << TSTOP << " " << TSTART << "\n";
            break;
        default:;
    }

    m_ss << ".print ";
    for (size_t i = 0; i < m_outs.size(); ++ i)
        m_ss << "V(" << m_outs.at(i) << ")" << " ";
    m_ss << "\n";


    m_ss << ".end" << "\n";
    return OKAY;
}
