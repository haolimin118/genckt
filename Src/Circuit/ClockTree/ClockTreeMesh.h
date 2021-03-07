#ifndef GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREEMESH_H
#define GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREEMESH_H

/*
 * @filename : ClockTreeMesh.h
 * @date     : 2021.03.01 
 * @weather  : Showers
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn
 * @desp     : ClockTree Mesh Circuit.
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class ClockTreeMesh : public CktBase
{
public:
    ClockTreeMesh(int scale, const std::string &typeName);
    virtual ~ClockTreeMesh();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(ClockTreeMesh);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream        m_ss;
    std::vector<std::string> m_outs;
};

#endif // GENCKT_CIRCUIT_CLOCKTREE_CLOCKTREEMESH_H