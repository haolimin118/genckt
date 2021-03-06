#include "MeshR.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

MeshR::MeshR(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
    m_outIndex = 0;
}

MeshR::~MeshR()
{
}

int MeshR::Generate(ofstream &fout)
{
#ifdef TRACE
    cout << LINE_INFO << endl;
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

int MeshR::GenerateCkt()
{
    string vsrc = "Vsrc 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG;
    m_ss << vsrc << "\n";

    string r;
    int pos = 0, neg = 0;
    int base = 1;
    int rIndex = 1;

    for (int i = 1; i <= 2 * m_scale + 1; ++ i) {
        if (i % 2 == 1) {
            base = (i - 1) / 2 * (m_scale + 1);
            for (int j = 1; j <= m_scale; ++ j) {
                pos =  base + j;
                neg = pos + 1;
                r = "R" + STR(rIndex) + " " + STR(pos) + " " + STR(neg) + " " + STR(RVAL);
                rIndex++;
                m_ss << r << "\n";
            }
            continue;
        }

        for (int j = 1; j <= m_scale + 1; ++ j) {
            pos = (i - 2) / 2 * (m_scale + 1) + j;
            neg = i / 2 * (m_scale + 1) + j;
            r = "R" + STR(rIndex) + " " + STR(pos) + " " + STR(neg) + " " + STR(RVAL);
            rIndex++;
            m_ss << r << "\n";
        }
    }

    pos = (m_scale + 1) * m_scale + 1;
    neg = 0;
    // r = "R" + STR(rIndex) + " " + STR(pos) + " " + STR(neg) + " " + STR(RVAL);
    r = "Rout " + STR(pos) + " " + STR(neg) + " " + STR(RVAL);
    rIndex++;
    m_ss << r << "\n";

    m_ss << "\n";

    m_outIndex = (m_scale + 1) * m_scale + 1;
    return OKAY;
}

int MeshR::GenerateCmd()
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
            m_ss << ".DC" << " " << "Vsrc" << " " << V_START << " "
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
