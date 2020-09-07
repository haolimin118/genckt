#include "CoupledTreeRC.h"
#include <iostream>
#include "Utilities/MyString.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

CoupledTreeRC::CoupledTreeRC(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

CoupledTreeRC::~CoupledTreeRC()
{
    m_ss.clear();
}

int CoupledTreeRC::Generate(ofstream &fout)
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

int CoupledTreeRC::GenerateCkt()
{
    string vsrc0 = "VIN0 10 0 1";
    string vsrc1 = "VIN1 11 0 1";

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

       r0 = "R" + STR(i) + "0" + " " + r0PosNode + " " + r0NegNode + " " + "100";
       c0 = "C" + STR(i) + "0" + " " + r0NegNode + " " + "0" + " " + "1p";
       r1 = "R" + STR(i) + "1" + " " + r1PosNode + " " + r1NegNode + " " + "100";
       c1 = "C" + STR(i) + "1" + " " + r1NegNode + " " + "0" + " " + "1p";
       cc = "C" + STR(i) + "C" + " " + r0NegNode + " " + r1NegNode + " " + "1p";

       m_ss << r0 << "\n" << c0 << "\n";
       m_ss << r1 << "\n" << c1 << "\n";
       m_ss << cc << "\n";
    }

    m_ss << "\n";

    return OKAY;

}

int CoupledTreeRC::GenerateCmd()
{
    m_ss << ".OP" << "\n";

    string out0 = "V(" + STR(m_scale+1) + "0" + ")";
    string out1 = "V(" + STR(m_scale+1) + "1" + ")";

    m_ss << ".PRINT" << " " << out0 << " " << out1 << "\n";
    m_ss << ".ENDS" << "\n";

    return OKAY;
}
