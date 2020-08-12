#ifndef GENCKT_CIRCUIT_CKTBASE_H
#define GENCKT_CIRCUIT_CKTBASE_H

/*
 * @filename : CktBase.h
 * @author   : Hao Limin
 * @date     : 2020.08.12
 * @desp     : Circuit base class, CktXXX inherit this class.
 */

#include "Define/Define.h"
#include <string>
#include <fstream>


class CktBase
{
public:
    CktBase(int scale, const std::string &typeName);
    virtual ~CktBase() {}

public:
    virtual int Generate(std::ofstream &fout) = 0;

protected:
    virtual int GenerateCkt() = 0;
    virtual int GenerateCmd() = 0;

    int         m_scale;
    std::string m_typeName;
    std::string m_title;
};

#endif // GENCKT_CIRCUIT_CKTBASE_H