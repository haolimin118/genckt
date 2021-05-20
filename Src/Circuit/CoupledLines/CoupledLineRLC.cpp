#include "CoupledLineRLC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

CoupledLineRLC::CoupledLineRLC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
    // m_outs
}

CoupledLineRLC::~CoupledLineRLC()
{
    m_outs.clear();
    m_outs.shrink_to_fit();
}

int CoupledLineRLC::Generate(ofstream &fout)
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

int CoupledLineRLC::GenerateCkt()
{
    string vin = "Vin 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG + " " + V_AC_PHASE  + " " + V_TRAN_PULSE;
    string rv1 = "Rv1 1 2 " + STR(RV);
    string rv2 = "Rv2 0 3 " + STR(RV);
    string cc  = "Cc0 2 3 " + STR(CVAL);

    m_ss << vin << "\n";
    m_ss << rv1 << "\n";
    m_ss << rv2 << "\n";
    m_ss << cc  << "\n";

    string r0, r1;
    string c0, c1;
    string l0, l1;
    int N0 = 2, N1 = 3;
    int rIndex = 0, cIndex = 0, lIndex = 0;
    int ccIndex = 1;

    for (int i = 1; i <= m_scale; ++ i) {
        r0 = "R" + STR(rIndex++) + " " + STR(N0) + " " + STR(N0+2) + " " + STR(RVAL);
        r1 = "R" + STR(rIndex++) + " " + STR(N1) + " " + STR(N1+2) + " " + STR(RVAL);

        N0 += 2;
        N1 += 2;

        l0 = "L" + STR(lIndex++) + " " + STR(N0) + " " + STR(N0+2) + " " + STR(LVAL);
        l1 = "L" + STR(lIndex++) + " " + STR(N1) + " " + STR(N1+2) + " " + STR(LVAL);

        N0 += 2;
        N1 += 2;

        c0 = "C" + STR(cIndex++) + " " + STR(N0) + " " + STR(0) + " " + STR(CVAL);
        c1 = "C" + STR(cIndex++) + " " + STR(N1) + " " + STR(0) + " " + STR(CVAL);

        cc = "Cc" + STR(ccIndex++) + " " + STR(N0) + " " + STR(N1) + " " + STR(CVAL);

        m_ss << r0 << "\n" << l0 << "\n" << c0 << "\n";
        m_ss << r1 << "\n" << l1 << "\n" << c1 << "\n";
        m_ss << cc << "\n";
    }

    m_ss << "\n";

    // output RES and CAP load
    r0 = "R" + STR(rIndex++) + " " + STR(N0) + " " + STR(N0+2) + " " + STR(RLOAD);
    r1 = "R" + STR(rIndex++) + " " + STR(N1) + " " + STR(N1+2) + " " + STR(RLOAD);
    N0 += 2;
    N1 += 2;
    c0 = "C" + STR(cIndex++) + " " + STR(N0) + " " + STR(0) + " " + STR(CLOAD);
    c1 = "C" + STR(cIndex++) + " " + STR(N1) + " " + STR(0) + " " + STR(CLOAD);

    m_ss << r0 << "\n" << r1 << "\n";
    m_ss << c0 << "\n" << c1 << "\n";

    m_ss << "\n";

    m_outs.push_back(N0);
    m_outs.push_back(N1);

    return OKAY;
}

int CoupledLineRLC::GenerateCmd()
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
