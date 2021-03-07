#ifndef GENCKT_CIRCUIT_MESH_MESHRLC_H
#define GENCKT_CIRCUIT_MESH_MESHRLC_H

/*
 * @filename : MeshRLC.h 
 * @date     : 2021.03.07
 * @weather  : Showers
 * @author   : Hao Limin
 * @email    : haolimin01@sjtu.edu.cn
 * @desp     : RLC mesh.
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class MeshRLC : public CktBase
{
public:
    MeshRLC(int scale, const std::string &typeName);
    virtual ~MeshRLC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(MeshRLC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream        m_ss;
    std::vector<std::string> m_outs;

};

#endif // GENCKT_CIRCUIT_MESH_MESHRLC_H