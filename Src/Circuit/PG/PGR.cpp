#include "PGR.h"
#include <iostream>
#include <assert.h>
#include "Utilities/MyString.h"
#include "Utilities/Utils.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

PGR::PGR(int scale, const string &typeName)
    : CktBase(scale, typeName)
{
    m_ss.clear();
    m_ss.str("");
}

PGR::~PGR()
{
    m_ss.clear();
}

int PGR::Generate(ofstream &fout)
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

int PGR::GenerateCkt()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    assert(m_scale >= 2);

    int NUM_PER_SCALE = PG_NUM_PER_SCALE;

    /* 1. layer: M2, contact */
    m_ss << "*layer M2 contact" << "\n";
    m_ss << "rr0" << " " << "n3_0x_0x" << " " << "_X_n3_0x_0x" << " " << 0.5 << "\n"; // vdd contact
    m_ss << "vv1" << " " << "_X_n3_0x_0x" << " " << "0" << " " << 1 << "\n";          // vdd contact
    int vssContactIndex = 2 * m_scale - 1;
    string vssContactNode = "n2_" + STR(vssContactIndex) + "x" + "_" + STR(vssContactIndex) + "x";
    m_ss << "rr2" << " " << vssContactNode << " " << "_X_" << vssContactNode << " " << 0.5 << "\n"; // vss contact
    m_ss << "vv3" << " " << "_X_" << vssContactNode << " " << "0" << " " << 0 << "\n";

    /* some notation */
    string pos = "", neg = "";
    int begin = 0, end = 0;
    string r, vsrc, isrc;
    int rIndex = 0, vIndex = 0, iIndex = 0;
    int x = 0, y = 0;

    /* 2. layer: M1, VDD net: 1 */
    m_ss << "*layer: M1, VDD net: 1" << "\n";
    for (int i = 0; i <= m_scale; ++ i) {
        y = 2 * i;
        int nIndex = 0;

        for (int j = 0; j < m_scale; ++ j) {
            begin = 2 * j;
            end = 2 * (j+1);

            if (NUM_PER_SCALE == 1) {
                pos = "n1_" + STR(begin) + "x" + "_" + STR(y) + "x";
                neg = "n1_" + STR(end) + "x" + "_" + STR(y) + "x";
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                continue;
            }

            int k = 0;
            do {
                pos = "n1_" + STR(begin) + "x" + "_" + STR(y) + "x";
                neg = "n1_" + STR(nIndex) + "_" + STR(y) + "x";
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                k++;

                if (k < NUM_PER_SCALE - 1) {
                    pos = "n1_" + STR(nIndex) + "_" + STR(y) + "x";
                    nIndex++;
                    neg = "n1_" + STR(nIndex) + "_" + STR(y) + "x";
                }

            } while (k < NUM_PER_SCALE - 1);

            pos = "n1_" + STR(nIndex++) + "_" + STR(y) + "x";
            neg = "n1_" + STR(end) + "x" + "_" + STR(y) + "x"; 
            r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
            m_ss << r << "\n";
        }
    }

    /* 3. layer: M1, GND net: 0 */
    m_ss << "*layer: M1, GND net: 0" << "\n";
    for (int i = 0; i < m_scale; ++ i) {
        y = 2 * i + 1;
        int nIndex = 0;
        for (int j = 0; j < m_scale - 1; ++ j) {
            begin = 2 * j + 1;
            end =  2 * j + 3;

            if (NUM_PER_SCALE == 1) {
                pos = "n0_" + STR(begin) + "x" + "_" + STR(y) + "x";
                neg = "n0_" + STR(end) + "x" + "_" + STR(y) + "x";
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                continue;
            }

            int k = 0;
            do {
                pos = "n0_" + STR(begin) + "x" + "_" + STR(y) + "x";
                neg = "n0_" + STR(nIndex) + "_" + STR(y) + "x";
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                k++;

                if (k < NUM_PER_SCALE - 1) {
                    pos = "n0_" + STR(nIndex) + "_" + STR(y) + "x";
                    nIndex++;
                    neg = "n0_" + STR(nIndex) + "_" + STR(y) + "x";
                }

            } while (k < NUM_PER_SCALE - 1);

            pos = "n0_" + STR(nIndex++) + "_" + STR(y) + "x";
            neg = "n0_" + STR(end) + "x" + "_" + STR(y) + "x";
            r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
            m_ss << r << "\n";
        }
    }

    /* 4. layer: M2, VDD net: 3 */
    m_ss << "*layer: M2, VDD net: 3" << "\n";
    for (int i = 0; i <= m_scale; ++ i) {
        x = 2 * i;
        int nIndex = 0;

        for (int j = 0; j < m_scale; ++ j) {
            begin = 2 * j;
            end = 2 * (j+1);

            if (NUM_PER_SCALE == 1) {
                pos = "n3_" + STR(x) + "x" + "_" + STR(begin) + "x";
                neg = "n3_" + STR(x) + "x" + "_" + STR(end) + "x";
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                continue;
            }

            int k = 0;
            do {
                pos = "n3_" + STR(x) + "x" + "_" + STR(begin) + "x";
                neg = "n3_" + STR(x) + "x" + "_" + STR(nIndex);
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                k++;

                if (k < NUM_PER_SCALE - 1) {
                    pos = "n3_" + STR(x) + "x" + "_" + STR(nIndex);
                    nIndex++;
                    neg = "n3_" + STR(x) + "x" + "_" + STR(nIndex);
                }

            } while (k < NUM_PER_SCALE - 1);

            pos = "n3_" + STR(x) + "x" + "_" + STR(nIndex++);
            neg = "n3_" + STR(x) + "x" + "_" + STR(end) + "x";
            r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
            m_ss << r << "\n";
        }
    }

    /* 5. layer: M2, GND net: 2 */
    m_ss << "*layer: M2, GND net: 2" << "\n";
    for (int i = 0; i < m_scale; ++ i) {
        x = 2 * i + 1;
        int nIndex = 0;
        for (int j = 0; j < m_scale - 1; ++ j) {
            begin = 2 *j + 1;
            end = 2 * j + 3;

            if (NUM_PER_SCALE == 1) {
                pos = "n2_" + STR(x) + "x" + "_" + STR(begin) + "x";
                neg = "n2_" + STR(x) + "x" + "_" + STR(end) + "x";
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                continue;
            }

            int k = 0;
            do {
                pos = "n2_" + STR(x) + "x" + "_" + STR(begin) + "x";
                neg = "n2_" + STR(x) + "x" + "_" + STR(nIndex);
                r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
                m_ss << r << "\n";
                k++;

                if (k < NUM_PER_SCALE - 1) {
                    pos = "n2_" + STR(x) + "x" + "_" + STR(nIndex);
                    nIndex++;
                    neg = "n2_" + STR(x) + "x" + "_" + STR(nIndex); 
                }

            } while (k < NUM_PER_SCALE - 1);

            pos = "n2_" + STR(x) + "x" + "_" + STR(nIndex++);
            neg = "n2_" + STR(x) + "x" + "_" + STR(end) + "x";
            r = "R" + STR(rIndex++) + " " + pos + " " + neg + " " + PG_R;
            m_ss << r << "\n";
        }
    }

    /* 6. vias from: 1 to 3 */
    m_ss << "*vias from: 1 to 3" << "\n";
    for (int i = 0; i <= m_scale; ++ i) {
        x = 2 * i;
        for (int j = 0; j <= m_scale; ++ j) {
            y = 2 * j;
            pos = "n1_" + STR(x) + "x" + "_" + STR(y) + "x";
            neg = "n3_" + STR(x) + "x" + "_" + STR(y) + "x";
            vsrc = "V" + STR(vIndex++) + " " + pos + " " + neg + " " + "0.0";
            m_ss << vsrc << "\n";
        }
    }

    /* 7. vias from: 0 to 2 */
    m_ss << "*vias from: 0 to 2" << "\n";
    for (int i = 0; i < m_scale; ++ i) {
        x = 2 * i + 1;
        for (int j = 0; j < m_scale; ++ j) {
            y = 2 * j + 1;
            pos = "n0_" + STR(x) + "x" + "_" + STR(y) + "x";
            neg = "n2_" + STR(x) + "x" + "_" + STR(y) + "x";
            vsrc = "V" + STR(vIndex++) + " " + pos + " " + neg + " " + "0.0";
            m_ss << vsrc << "\n";
        }
    }

    /* 8. isrcS */
    m_ss << "*isrcS" << "\n";
    for (int i = 0; i <= m_scale; ++ i) {
        x = 2 * i;
        for (int j = 0; j <= m_scale; ++ j) {
            y = 2 * j;
            pos = "n1_" + STR(x) + "x" + "_" + STR(y) + "x";
            neg = "0";
            isrc = "I" + STR(iIndex++) + " " + pos + " " + neg + " " + PG_I;
            m_ss << isrc << "\n";
        }
    }

    for (int i = 0; i < m_scale; ++ i) {
        x = 2 * i + 1;
        for (int j = 0; j < m_scale; ++ j) {
            y = 2 * j + 1;
            pos = "0";
            neg = "n0_" + STR(x) + "x" + "_" + STR(y) + "x";
            isrc = "I" + STR(iIndex++) + " " + pos + " " + neg + " " + PG_I;
            m_ss << isrc << "\n";
        }
    }

    /* 9. collect some output nodes */
    int ox1 = (m_scale/2) * 2;
    int ox2 = ox1 + 1;
    int oy1 = ox1;
    int oy2 = ox2;

    m_outs.push_back("n1_" + STR(ox1) + "x" + "_" + "0x");
    m_outs.push_back("n0_" + STR(ox2) + "x" + "_" + "0x");
    m_outs.push_back("n3_" + STR(ox1) + "x" + "_" + STR(oy1) + "x");
    m_outs.push_back("n2_" + STR(ox2) + "x" + "_" + STR(oy2) + "x");

    return OKAY;
}

int PGR::GenerateCmd()
{
#ifdef TRACE
    cout << TRACE_LINE << endl;
#endif

    switch (m_anaType) {
        case OP:
        case DC:
        case AC:
        case TRAN:
            m_ss << ".OP" << "\n";
            m_ss << ".SAVE ";
            for (size_t i = 0; i < m_outs.size(); ++ i) {
                m_ss << "V(" << m_outs.at(i) << ") ";
            }
            m_ss << "\n";
            break;
        default:;
    }

    m_ss << ".end" << "\n";
    return OKAY;
}