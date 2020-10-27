#ifndef GENCKT_CIRCUIT_TREE_CLOCKTREERC_H
#define GENCKT_CIRCUIT_TREE_CLOCKTREERC_H

/*
 * @filename : ClockTreeRC.h
 * @author   : Hao Limin
 * @dete     : 2020.09.07
 * @desp     : Clock Tree, RC.
 * @ref      : Doc/Tree/ClockTreeRC.png
 */

#include "Circuit/CktBase.h"
#include <sstream>

class ClockTreeRC : public CktBase
{
public:
    ClockTreeRC(int scale, const std::string &typeName);
    virtual ~ClockTreeRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    int               m_outNode;
};

#endif // GENCKT_CIRCUIT_TREE_CLOCKTREERC_H
