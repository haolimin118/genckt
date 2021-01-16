#include "MeshRC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

MeshRC::MeshRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

MeshRC::~MeshRC()
{
    m_ss.clear();
}

int MeshRC::Generate(ofstream &fout)
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

int MeshRC::GenerateCkt()
{
    string vsrc1 = "V1 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG1;
    m_ss << vsrc1 << "\n";
    string vsrc2 = "V2 " + STR(m_scale) + " 0 " + V_DC + " " + "AC" + " " + V_AC_MAG2; 
    m_ss << vsrc2 << "\n";

    string r, c;
    int pos = 0, neg = 0;
    int base = 1;
    int rIndex = 1, cIndex = 1;

    for (int i = 1; i <= 2 * m_scale + 1; ++ i) {
        if (i % 2 == 1) {
            base = (i - 1) / 2 * (m_scale + 1);
            for (int j = 1; j <= m_scale; ++ j) {
                pos =  base + j;
                neg = pos + 1;
                r = "R" + STR(rIndex) + " " + STR(pos) + " " + STR(neg) + " " + STR(RVAL);
                rIndex++;
                m_ss << r << "\n";
                c = "C" + STR(cIndex) + " " + STR(pos) + " " + "0" + " " + STR(CVAL);
                cIndex++;
                m_ss << c << "\n";
            }
            c = "C" + STR(cIndex) + " " + STR(neg) + " " + "0" + " " + STR(CVAL);
            cIndex++;
            m_ss << c << "\n";

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
    r = "R" + STR(rIndex) + " " + STR(pos) + " " + STR(neg) + " " + STR(RVAL);
    rIndex++;
    m_ss << r << "\n";

    m_ss << "\n";

    m_outIndex.push_back((m_scale+1)*m_scale+1);
    m_outIndex.push_back((m_scale+1)*(m_scale+1));

    return OKAY;
}

int MeshRC::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            m_ss << ".PRINT OP V(" << m_outIndex[0] << ")" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "VIN" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            m_ss << ".PRINT DC V(" << m_outIndex[0] << ")" << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            m_ss << ".PRINT AC vdb(" << m_outIndex[0] << ") "
                 << "vdb(" << m_outIndex[1] << ")" << "\n";
            break;
        case TRAN:
            break;
    }

    m_ss << ".end" << "\n";

    return OKAY;
}