#ifndef GENCKT_CIRCUIT_CKTCONTEXT_H
#define GENCKT_CIRCUIT_CKTCONTEXT_H

/*
 * @filename : CktContext.h
 * @author   : Hao Limin
 * @date     : 2020.08.12
 * @desp     : Circuit Context, using Strategy Pattern.
 */

#include "Define/Define.h"
#include <string>
#include <fstream>

class CktBase;

enum CktType { LADDERRC = 0, LADDERRLC,
               COUPLEDTREERC, /* COUPLEDTREERLC */
               CLOCKTREER, CLOCKTREERC,
               CLOCKTREERRAND, CLOCKTREERCRAND,
               MESHR, MESHRC };


class CktContext
{
public:
    CktContext(CktType type, int scale, AnalysisType anaType);
    ~CktContext() {}

    int executeGeneration(std::ofstream &fout);

private:
    CktBase *m_ckt;
};

#endif // GENCKT_CIRCUIT_CKTCONTEXT_H
