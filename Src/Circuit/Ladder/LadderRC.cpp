#include "LadderRC.h"
#include <iostream>
#include "Utilities/MyString.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

LadderRC::LadderRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

LadderRC::~LadderRC()
{
    m_ss.clear();
}

int LadderRC::Generate(ofstream &fout)
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

int LadderRC::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif
    string vsrc = "VIN 1 0 1";
    m_ss << vsrc << "\n";

    string r, c;

    for (int i = 1; i <= m_scale; ++ i) {
        r = "R" + STR(i) + " " + STR(i) + " " + STR(i+1) + " " + "100";
        c = "C" + STR(i) + " " + STR(i+1) + " " + "0" + " " + "1p";
        m_ss << r << "\n";
        m_ss << c << "\n";
    }
    m_ss << "\n";

    return OKAY;

}

int LadderRC::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif
    m_ss << ".OP" << "\n";
    m_ss << ".PRINT V(" << STR(m_scale+1) << ")" << "\n";
    m_ss << ".ends" << "\n";

    return OKAY;
}
