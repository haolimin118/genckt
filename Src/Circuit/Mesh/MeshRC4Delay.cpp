#include "MeshRC4Delay.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

MeshRC4Delay::MeshRC4Delay(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
}

MeshRC4Delay::~MeshRC4Delay()
{
}

int MeshRC4Delay::Generate(ofstream &fout)
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

int MeshRC4Delay::GenerateCkt()
{
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

    string rout;
    rout = "R" + STR(rIndex++) + " " + STR(1) + " " + STR(0) + " " + "10K";
    m_ss << rout << "\n";
    m_outIndex.push_back(1);

    rout = "R" + STR(rIndex++) + " " + STR(m_scale+1) + " " + STR(0) + " " + "10K";
    m_ss << rout << "\n";
    m_outIndex.push_back(m_scale+1);

    rout = "R" + STR(rIndex++) + " " + STR(m_scale*(m_scale+1)+1) + " " + STR(0) + " " + "10K";
    m_ss << rout << "\n";
    m_outIndex.push_back(m_scale*(m_scale+1)+1);

    rout = "R" + STR(rIndex) + " " + STR((m_scale+1)*(m_scale+1)) + " " + STR(0) + " " + "10K";
    m_ss << rout << "\n";
    m_outIndex.push_back((m_scale+1)*(m_scale+1));

    return OKAY;
}

int MeshRC4Delay::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "Vsrc" << " " << V_START << " "
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
    for (size_t i = 0; i < m_outIndex.size(); ++ i) {
        m_ss << "v(" << m_outIndex.at(i) << ") ";
    }
    m_ss << "\n";

    m_ss << ".end" << "\n";

    return OKAY;
}
