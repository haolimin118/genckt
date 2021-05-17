#include "MeshRLC.h"
#include <iostream>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

MeshRLC::MeshRLC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.str("");
}

MeshRLC::~MeshRLC()
{
    m_ss.str("");
}

int MeshRLC::Generate(ofstream &fout)
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

int MeshRLC::GenerateCkt()
{
#ifdef TRACE
    cout << LINE_INFO << endl;
#endif

    string vsrc1 = "Vsrc 1 0 " + V_DC + " " + "AC" + " " + V_AC_MAG1;
    m_ss << vsrc1 << "\n";

    string r, l, c;
    int nodeIndex = 1, posIndex = 0, negIndex = 0;
    int mnodeIndex = 1;
    int rIndex = 0, lIndex = 0, cIndex = 0;

    for (int i = 0; i < m_scale; ++ i) {
        // skeleton part
        c = "C" + STR(cIndex++) + " " + STR(nodeIndex) + " " + STR(0) + " " + STR(CVAL);
        m_ss << c << "\n";

        for (int j = 0; j < m_scale; ++ j) {
            posIndex = nodeIndex;
            negIndex = posIndex + 1;
            r = "R" + STR(rIndex++) + " " + STR(posIndex) + " " + STR(negIndex) + " " + STR(RVAL);
            m_ss << r << "\n";

            posIndex = negIndex;
            negIndex = posIndex + 1;
            l = "L" + STR(lIndex++) + " " + STR(posIndex) + " " + STR(negIndex) + " " + STR(LVAL);
            m_ss << l << "\n";

            posIndex = negIndex;
            negIndex = 0;
            c = "C" + STR(cIndex++) + " " + STR(posIndex) + " " + STR(negIndex) + " " + STR(CVAL);
            m_ss << c << "\n";

            nodeIndex += 2;
        }
        nodeIndex++;

        // middle part
        for (int j = 0; j <= m_scale; ++ j) {
            int right = nodeIndex + 2 * j;
            posIndex = right - (2 * m_scale + 1);
            negIndex = mnodeIndex++;
            r = "R" + STR(rIndex++) + " " + STR(posIndex) + " " + "m" + STR(negIndex) + " " + STR(RVAL);
            m_ss << r << "\n";

            posIndex = negIndex;
            negIndex = right;
            l = "L" + STR(lIndex++) + " " + "m" + STR(posIndex) + " " + STR(negIndex) + " " + STR(LVAL);
            m_ss << l << "\n";
        }
    }

    // the last column
    c = "C" + STR(cIndex++) + " " + STR(nodeIndex) + " " + STR(0) + " " + STR(CVAL);
    m_ss << c << "\n";
    for (int j = 0; j < m_scale; ++ j) {
        posIndex = nodeIndex;
        negIndex = posIndex + 1;
        r = "R" + STR(rIndex++) + " " + STR(posIndex) + " " + STR(negIndex) + " " + STR(RVAL);
        m_ss << r << "\n";

        posIndex = negIndex;
        negIndex = posIndex + 1;
        l = "L" + STR(lIndex++) + " " + STR(posIndex) + " " + STR(negIndex) + " " + STR(LVAL);
        m_ss << l << "\n";

        posIndex = negIndex;
        negIndex = 0;
        c = "C" + STR(cIndex++) + " " + STR(posIndex) + " " + STR(negIndex) + " " + STR(CVAL);
        m_ss << c << "\n";

        nodeIndex += 2;
    }

    m_ss << "\n";

    m_outs.push_back(STR(1));
    m_outs.push_back(STR(nodeIndex - 2 * m_scale));

    return OKAY;
}

int MeshRLC::GenerateCmd()
{
#ifdef TRACE
    cout << LINE_INFO << endl;
#endif

    switch (m_anaType) {
        case OP:
            m_ss << ".OP" << "\n";
            m_ss << ".SAVE V(" << m_outs[0] << ") "
                 << "V(" << m_outs[1] << ")" << "\n";
            break;
        case DC:
            m_ss << ".DC" << " " << "Vsrc" << " " << V_START << " "
                 << V_STOP << " " << V_INCR << "\n";
            m_ss << ".SAVE V(" << m_outs[0] << ") "
                 << "V(" << m_outs[1] << ")" << "\n";
            break;
        case AC:
            m_ss << ".AC" << " " << STEP_TYPE << " " << NUM_STEPS << " "
                 << FSTART << " " << FSTOP << "\n";
            m_ss << ".SAVE V(" << m_outs[0] << ") "
                 << "V(" << m_outs[1] << ")" << "\n";
            break;
        case TRAN:
            break;
        default:;
    }

    m_ss << ".end" << "\n";

    return OKAY;
}