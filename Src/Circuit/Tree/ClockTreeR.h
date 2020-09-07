#ifndef GENCKT_CIRCUIT_TREE_CLOCKTREER_H
#define GENCKT_CIRCUIT_TREE_CLOCKTREER_H

/*
 * @filename : ClockTreeR.h
 * @author   : Hao Limin
 * @date     : 2020.09.05
 * @desp     : Clock Tree, only R.
 * @ref      : Doc/Tree/ClockTreeR.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class ClockTreeR : public CktBase
{
public:
    ClockTreeR(int scale, const std::string &typeName);
    virtual ~ClockTreeR();

public:
    int Generate(std::ofstream &fout) override;

private:
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;

};

#endif // GENCKT_CIRCUIT_TREE_CLOCKTREER_H
