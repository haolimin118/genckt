#include "LadderRC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

LadderRC::LadderRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
    m_outIndex = 0;
}

LadderRC::~LadderRC()
{
}

int LadderRC::Generate(ofstream &fout)
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

int LadderRC::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif
    string vsrc = "VIN 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG;
    m_ss << vsrc << "\n";

    string r, c;

    for (int i = 1; i <= m_scale; ++ i) {
        r = "R" + STR(i) + " " + STR(i) + " " + STR(i+1) + " " + STR(RVAL);
        c = "C" + STR(i) + " " + STR(i+1) + " " + "0" + " " + STR(CVAL);
        m_ss << r << "\n";
        m_ss << c << "\n";
    }
    m_ss << "\n";

    m_outIndex = m_scale+1;

    return OKAY;

}

int LadderRC::GenerateCmd()
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
    }

    m_ss << ".end" << "\n";

    return OKAY;
}
