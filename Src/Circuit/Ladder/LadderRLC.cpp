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
    m_outIndex = 0;
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
    int nIndex = 1;
    int rIndex = 1, cIndex = 1, lIndex = 1;

    for (int i = 1; i <= m_scale; ++ i) {
        r = "R" + STR(rIndex) + " " + STR(nIndex) + " " + STR(nIndex+1) + " " + STR(RVAL);
        rIndex++;
        nIndex++;
        m_ss << r << "\n";

        if (i % L_GAP == 0) {
            l = "L" + STR(lIndex) + " " + STR(nIndex) + " " + STR(nIndex+1) + " " + STR(LVAL);
            lIndex++;
            nIndex++;
            m_ss << l << "\n";
        }

        c = "C" + STR(cIndex) + " " + STR(nIndex) + " " + "0" + " " + STR(CVAL);
        cIndex++;
        m_ss << c << "\n";
    }
    m_ss << "\n";

    m_outIndex = nIndex;

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
            m_ss << ".PRINT OP V(" << m_outIndex << ")" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "VIN" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            m_ss << ".PRINT DC V(" << m_outIndex << ")" << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            m_ss << ".PRINT AC vdb(" << m_outIndex << ")" << "\n";
            break;
        case TRAN:
            break;
    }

    m_ss << ".end" << "\n";

    return OKAY;
}
