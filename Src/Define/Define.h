#ifndef GENCKT_DEFINE_DEFINE_H
#define GENCKT_DEFINE_DEFINE_H

/*
 * @filename : Define.h
 * @author   : Hao Limin
 * @date:    : 2020.08.09
 * @desp     : Basic defines
 */

#include <string>

#ifndef LINE_INFO
#define LINE_INFO "\n[" << __FILE__ << " : line " << __LINE__ << " : " << __FUNCTION__ << "()] - "
#endif

#ifndef TRACE_LINE
#define TRACE_LINE "\n[" << __FILE__ << " : line " << __LINE__ << " : " << __FUNCTION__ << "()]"
#endif

#ifndef UNUSED
#define UNUSED(x) (void*)(x)
#endif

/* Disallow copy and assign functions that generated by compiler. */
 #define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &);             \
    TypeName &operator=(const TypeName &)

#define OKAY  0
#define ERROR 1

#define NOT !
#define AND &&

#define EXIT exit(1)

/* For ClockTree circuit */
const static int MAX_H_LENGTH = 100;
const static int MAX_CTM_LENGTH = 10000;

enum AnalysisType { OP = 0, DC, AC, TRAN };

/* For DC */
const std::string V_DC = "1";
const std::string V_START = "0";
const std::string V_STOP = "1";
const std::string V_INCR = "0.1";

/* For AC */
const std::string STEP_TYPE = "DEC";
const std::string NUM_STEPS = "10";
const std::string FSTART = "1";
const std::string FSTOP  = "1G";
const std::string V_AC_PHASE = "0";
const std::string V_AC_MAG = "1";
const std::string V_AC_MAG1 = "1";
const std::string V_AC_MAG2 = "2";

/* For Tran */
const std::string V_TRAN_SIN = "sin(0 1 100MEG)";
const std::string V_TRAN_PULSE = "PULSE(0 1 100n 1f 1f 0.5u 2u)";
const std::string TSTEP = "1n";
const std::string TSTOP = "4u";
const std::string TSTART = "0";

#define RVAL RandomDouble(0.1, 10)
// #define RVAL 10
#define CVAL RandomDouble(1e-13, 1e-12)
// #define CVAL 1e-12
// #define LVAL RandomDouble(1e-10, 1e-8)
#define LVAL  1e-8
#define RLOAD 1000
#define CLOAD 2e-12
#define RV    50
#define CV    2e-12

const static int L_GAP = 5;
const static int COUPLED_NUM = 20;

/* for powergrid */
const static int PG_NUM_PER_SCALE = 100;
const static int PG_LAYER = 2;   // fixed
const static int PG_CONTACT = 2; // fixed
const std::string PG_R = "1.25";
const std::string PG_V = "1";
const std::string PG_I = "0.3125m";

#endif // GENCKT_DEFINE_DEFINE_H