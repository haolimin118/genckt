#include "CktContext.h"
#include <cassert>
#include "CktBase.h"
#include "AllCkt.h"
#include "Define/Define.h"

using std::ofstream;

CktContext::CktContext(CktType type, int scale)
{
    m_ckt = nullptr;

    switch (type) {
        case LADDERRC:
            m_ckt = new LadderRC(scale, "RC ladder");
            break;
        case LADDERRLC:
            m_ckt = new LadderRLC(scale, "RLC ladder");
            break;
        default:;
    }

}

int CktContext::executeGeneration(ofstream &fout)
{
    if (NOT m_ckt)
        return ERROR;
    return m_ckt->Generate(fout);
}