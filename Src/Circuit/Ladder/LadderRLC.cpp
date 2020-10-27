#include "LadderRLC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

LadderRLC::LadderRLC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

LadderRLC::~LadderRLC()
{
    m_ss.clear();
}

int LadderRLC::Generate(ofstream &fout)
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

int LadderRLC::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif
    string vsrc = "VIN 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG;
    m_ss << vsrc << "\n";

    string c0 = "C0 1 0 " + STR(CVAL);
    m_ss << c0 << "\n";

    string r, l, c;
    int start = 0;

    for (int i = 1; i <= m_scale; ++ i) {
        start = 2 * i - 1;
        r = "R" + STR(i) + " " + STR(start) + " " + STR(start+1) + " " + STR(RVAL);
        l = "L" + STR(i) + " " + STR(start+1) + " " + STR(start+2) + " " + STR(LVAL);
        c = "C" + STR(i) + " " + STR(start+2) + " " + "0" + " " + STR(CVAL);
        m_ss << r << "\n";
        m_ss << l << "\n";
        m_ss << c << "\n";
    }
    m_ss << "\n";

    return OKAY;

}

int LadderRLC::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            m_ss << ".PRINT OP V(" << (2*m_scale+1) << ")" << "\n";
            break;
        case DC:
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            m_ss << ".PRINT AC vdb(" << STR(2*m_scale+1) << ")" << "\n";
            break;
        case TRAN:
            break;
    }

    m_ss << ".end" << "\n";

    return OKAY;
}
