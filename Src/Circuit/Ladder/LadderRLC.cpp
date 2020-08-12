#include "LadderRLC.h"
#include <iostream>
#include "Utilities/MyString.h"

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
    
    fout << m_title << "\n";
    fout << m_ss.str();

    return OKAY;

}

int LadderRLC::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif
    string vsrc = "VIN 1 0 1";
    m_ss << vsrc << "\n";

    string c0 = "C0 1 0 1p";
    m_ss << c0 << "\n";

    string r, l, c;
    int start = 0;

    for (int i = 1; i <= m_scale; ++ i) {
        start = 2 * i - 1;
        r = "R" + STR(i) + " " + STR(start) + " " + STR(start+1) + " " + "100";
        l = "L" + STR(i) + " " + STR(start+1) + " " + STR(start+2) + " " + "1m";
        c = "C" + STR(i) + " " + STR(start+2) + " " + "0" + " " + "1p";
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
    m_ss << ".OP" << "\n";
    m_ss << ".PRINT V(" << STR(2 * m_scale + 1) << ")" << "\n";
    m_ss << ".ends" << "\n";

    return OKAY;
}