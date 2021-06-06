#ifndef GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERLC_H
#define GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERLC_H

/*
 * @filename : ClockTreeRLC.h
 * @date     : 2021.05.20
 * @weather  : Mostly Cloudy
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn 
 * @desp     : balanced rlc clock tree.
 */

#include "Circuit/CktBase.h"
#include "Define/Define.h"
#include <sstream>
#include <vector>

class ClockTreeRLC : public CktBase
{
public:
    ClockTreeRLC(int scale, const std::string &typeName);
    virtual ~ClockTreeRLC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(ClockTreeRLC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    std::vector<int>  m_outs;
};

#endif // GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREERLC_H