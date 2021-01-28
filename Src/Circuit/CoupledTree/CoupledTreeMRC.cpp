#include "CoupledTreeMRC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

CoupledTreeMRC::CoupledTreeMRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
    m_outNode = "0";
}

CoupledTreeMRC::~CoupledTreeMRC()
{
    m_ss.clear();
}

int CoupledTreeMRC::Generate(ofstream &fout)
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

int CoupledTreeMRC::GenerateCkt()
{
    string vsrc = "";
    string vname = "";
    string pos = "", neg = "";
    for (int i = 1; i <= COUPLED_NUM; ++ i) {
        vname = "VIN" + string("_") + STR(i);
        pos = "n_1_" + STR(i);
        neg = "0";
        vsrc = vname + " " + pos + " " + neg + " " + V_DC + " " + "AC" + " " + V_AC_MAG;
        m_ss << vsrc << "\n";
    }

    /* RC */
    string r, c;
    string rname, cname;
    for (int i = 1; i <= m_scale; ++ i) {
        for (int j = 1; j <= COUPLED_NUM; ++ j) {
            pos = "n_" + STR(i) + "_" + STR(j);
            neg = "n_" + STR(i+1) + "_" + STR(j);
            rname = "R" + STR(i) + "_" + STR(j);
            cname = "C" + STR(i) + "_" + STR(j);
            r = rname + " " + pos + " " + neg + " " + STR(RVAL);
            c = cname + " " + neg + " " + "0" + " " + STR(CVAL);
            m_ss << r << "\n";
            m_ss << c << "\n";
        }
    }

    /* Couple C */
    string cc, ccname;
    for (int i = 1; i <= m_scale; ++ i) {
        for (int j = 1; j <= COUPLED_NUM; ++ j) {
            pos = "n_" + STR(i+1) + "_" + STR(j);
            for ( int k = j+1; k <= COUPLED_NUM; ++ k) {
                neg = "n_" + STR(i+1) + "_" + STR(k);
                ccname = "CC" + STR(i) + "_" + STR(j) + "_" + STR(k);
                cc = ccname + " " + pos + " " + neg + " " + STR(CVAL);
                m_ss << cc << "\n";
            }
        }
    }

    m_ss << "\n";

    m_outNode = "n_" + STR(m_scale+1) + "_" + "1";

    return OKAY;

}

int CoupledTreeMRC::GenerateCmd()
{
    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            m_ss << ".SAVE V(" << m_outNode << ")" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "VIN0" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            m_ss << ".SAVE V(" << m_outNode << ")" << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            m_ss << ".SAVE V(" << m_outNode << ")"<< "\n";
            break;
        case TRAN:
            break;
    }

    m_ss << ".end" << "\n";
    return OKAY;
}
