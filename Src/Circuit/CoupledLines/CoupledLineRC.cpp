#include "CoupledLineRC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

CoupledLineRC::CoupledLineRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
}

CoupledLineRC::~CoupledLineRC()
{
}

int CoupledLineRC::Generate(ofstream &fout)
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

int CoupledLineRC::GenerateCkt()
{
    string vsrc0 = "VIN0 10 0 " + V_DC + " " + "AC" + " " + V_AC_MAG + " " + V_AC_PHASE + " " + V_TRAN_PULSE;
    // string vsrc1 = "VIN1 11 0 " + V_DC + " " + "AC" + " " + V_AC_MAG;
    string vsrc1 = "VIN1 11 0 0 AC 0 0";

    m_ss << vsrc0 << "\n";
    m_ss << vsrc1 << "\n";

    string r0, c0;
    string r1, c1;
    string cc;
    string r0PosNode, r0NegNode;
    string r1PosNode, r1NegNode;

    for (int i = 1; i <= m_scale; ++ i) {
       r0PosNode = STR(i) + "0";
       r0NegNode = STR(i+1) + "0";
       r1PosNode = STR(i) + "1";
       r1NegNode = STR(i+1) + "1";

       r0 = "R" + STR(i) + "0" + " " + r0PosNode + " " + r0NegNode + " " + STR(RVAL);
       c0 = "C" + STR(i) + "0" + " " + r0NegNode + " " + "0" + " " + STR(CVAL);
       r1 = "R" + STR(i) + "1" + " " + r1PosNode + " " + r1NegNode + " " + STR(RVAL);
       c1 = "C" + STR(i) + "1" + " " + r1NegNode + " " + "0" + " " + STR(CVAL);
       cc = "C" + STR(i) + "C" + " " + r0NegNode + " " + r1NegNode + " " + STR(CVAL);

       m_ss << r0 << "\n" << c0 << "\n";
       m_ss << r1 << "\n" << c1 << "\n";
       m_ss << cc << "\n";
    }

    m_ss << "\n";

    m_outs.push_back(STR(m_scale+1)+"0");
    m_outs.push_back(STR(m_scale+1)+"1");

    return OKAY;
}

int CoupledLineRC::GenerateCmd()
{
    string out0 = m_outs.at(0);
    string out1 = m_outs.at(1);

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "VIN0" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            break;
        case TRAN:
            m_ss << ".tran" << " " << TSTEP << " " << TSTOP << "\n";
            break;
    }

    m_ss << ".SAVE V(" << out0 << ") "
         << "V(" << out1 << ")" << endl;

    m_ss << ".end" << "\n";
    return OKAY;
}
