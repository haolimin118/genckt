#include "CoupledLineMRC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

CoupledLineMRC::CoupledLineMRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
}

CoupledLineMRC::~CoupledLineMRC()
{
}

int CoupledLineMRC::Generate(ofstream &fout)
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

int CoupledLineMRC::GenerateCkt()
{
    string vsrc = "";
    string vname = "";
    string pos = "", neg = "";
    for (int i = 1; i <= COUPLED_NUM; ++ i) {
        vname = "vin" + string("_") + STR(i);
        pos = "n_1_" + STR(i);
        neg = "0";
        vsrc = vname + " " + pos + " " + neg + " " + V_DC + " " + "AC" + " " +
               V_AC_MAG + " " + V_AC_PHASE + " " + V_TRAN_PULSE;
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

			if (i == m_scale)
				c = cname + " " + neg + " " + "0" + " " + STR(CLOAD);
			else
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

    // vsrc pos node
    string savenode("");
    for (int i = 1; i <= COUPLED_NUM; ++ i) {
        savenode = "n_1_" + STR(i);
        m_outs.push_back(savenode); 
    }

    // the last column nodes
    for (int i = 1; i <= COUPLED_NUM; ++ i) {
        savenode = "n_" + STR(m_scale+1) + "_" + STR(i);
        m_outs.push_back(savenode);
    }

    return OKAY;

}

int CoupledLineMRC::GenerateCmd()
{
    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "vin_1" << " " << V_START << " "
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

    m_ss << ".save ";
    for (size_t i = 0; i < m_outs.size(); ++ i)
        m_ss << "v(" << m_outs.at(i) << ") ";
    m_ss << "\n";

    m_ss << ".end" << "\n";
    return OKAY;
}
