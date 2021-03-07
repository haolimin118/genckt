#include "RLine.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

RLine::RLine(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
    m_outIndex = 0;
}

RLine::~RLine()
{
}

int RLine::Generate(ofstream &fout)
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

int RLine::GenerateCkt()
{
#ifdef TRACE
    cout << LINE_INFO << endl;
#endif

    string vsrc = "VIN 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG;
    m_ss << vsrc << "\n";

    string r;
    string pos, neg;

    int i = 1;
    for (i = 1; i <= m_scale; ++ i) {
        pos = STR(i);
        neg = STR(i+1);
        r = "R" + STR(i) + " " + pos + " " + neg + " " + STR(RVAL);
        m_ss << r << "\n";
    }
    r = "R" + STR(i) + " " + STR(i) + " " + "0" + " " + STR(RVAL);
    m_ss << r << "\n";

    m_outIndex = i;

    return OKAY;
}

int RLine::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

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
        default:;
    }

    m_ss << ".end" << "\n";

    return OKAY;
}

