#ifndef GENCKT_CIRCUIT_MESH_MESHRC_H 
#define GENCKT_CIRCUIT_MESH_MESHRC_H 

/*
 * @filename : MeshRC.h
 * @author   : Hao Limin
 * @date     : 2020.10.26
 * @desp     : RC Mesh circuit.
 * @ref      : Doc/Ladder/MeshRC.png
 * @modified : 2021.01.16
 */

#include "Circuit/CktBase.h"
#include <sstream>
#include <vector>

class MeshRC : public CktBase
{
public:
    MeshRC(int scale, const std::string &typeName);
    virtual ~MeshRC();

public:
    int Generate(std::ofstream &fout) override;

private:
    DISALLOW_COPY_AND_ASSIGN(MeshRC);

    int GenerateCkt() override;
    int GenerateCmd() override;

    std::stringstream m_ss;
    std::vector<int>  m_outIndex;

};

#endif // GENCKT_CIRCUIT_MESH_MESHRC_H 