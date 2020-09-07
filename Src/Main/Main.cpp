#include <iostream>
#include <string>
#include <fstream>
#include "Circuit/CktContext.h"
#include "Define/Define.h"
#include <gflags/gflags.h>

using namespace std;

// default params
static int     scale = 1;
static CktType cktType = LADDERRC;
static string  pathname = "genckt.sp";

DEFINE_string(t, "ladderrc",  "Set method to generate circuit.");
DEFINE_int64(s,  1,           "Set circuit scale.");
DEFINE_string(o, "genckt.sp", "Set output netlist pathname.");

static void ParseCommandLineArgs(int argc, char **argv);
static void InitProjectInfo();
static void GenerateNetlist();


/* use gflags to parse command line args */
static void ParseCommandLineArgs(int argc, char **argv)
{
    InitProjectInfo();

    google::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_s <= 0) {
        cout << "[ERROR] scale <= 0" << endl;
        EXIT;
    }
    scale = FLAGS_s;

    string flag_type = FLAGS_t;
    if (flag_type.compare("ladderrc") == 0) {
        cktType = LADDERRC;
    } else if (flag_type.compare("ladderrlc") == 0) {
        cktType = LADDERRLC;
    } else if (flag_type.compare("coupledtreerc") == 0) {
        cktType = COUPLEDTREERC;
    } else if (flag_type.compare("clocktreer") == 0) {
        cktType = CLOCKTREER;
    } else if (flag_type.compare("clocktreerc") == 0) {
        cktType = CLOCKTREERC;
    } else {
        cout << "[ERROR] Circuit type is unknown" << endl;
        EXIT;
    }
    
    pathname = FLAGS_o;

    google::ShutDownCommandLineFlags();

    /* dump summary */
    printf("[NOTE] Pathname (%s), circuit type (%s), scale (%d)\n",
        pathname.c_str(), flag_type.c_str(), scale);

}


static void InitProjectInfo()
{
    google::SetVersionString("0.1");
    google::SetUsageMessage("Usage: genckt <options>\n\n"
                            "options:\n"
                            "-o        set generated netlist pathname.\n"
                            "-s        set circuit scale.\n"
                            "-m        set circuit type.\n"
                            "Circuit Type(s):\n"
                            "ladderrc\n"
                            "ladderrlc\n"
                            "coupledtreerc\n"
                            "clocktreer\n"
                            "clocktreerc");
}


/* Generate netlist */
static void GenerateNetlist()
{
    ofstream fout(pathname, ios::out);
    if (NOT fout.is_open()) {
        cout << "Can't open " << pathname << endl;
        EXIT;
    }

    // comment
    CktContext *context = new CktContext(cktType, scale);
    int error = context->executeGeneration(fout);
    if (error)
        cout << "[ERROR] Generate netlist failed." << endl;

    fout.close();
}


int main(int argc, char **argv)
{
    ParseCommandLineArgs(argc, argv);
    GenerateNetlist();

    cout << "\n[NOTE] Finished!" << endl;
    return 0;
}

