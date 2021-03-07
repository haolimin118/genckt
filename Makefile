# Makefile for genckt

TARGET = genckt

SRC_DIR = Src

INC_PATH = -I$(SRC_DIR) \
           -I$(SRC_DIR)/Define \
		   -I$(SRC_DIR)/Utilities \
		   -I$(SRC_DIR)/Circuit \
		   -I$(SRC_DIR)/Circuit/Ladder \
		   -I$(SRC_DIR)/Circuit/ClockTree \
		   -I$(SRC_DIR)/Circuit/CoupledTree \
		   -I$(SRC_DIR)/Circuit/Mesh \
           -I$(SRC_DIR)/Circuit/RLine \
           -I$(SRC_DIR)/Circuit/PG

LIB_PATH = 

LIBS = -lgflags

SRCS = $(SRC_DIR)/Main/Main.cpp \
	   $(SRC_DIR)/Utilities/MyString.cpp \
	   $(SRC_DIR)/Utilities/Utils.cpp \
	   $(SRC_DIR)/Circuit/CktBase.cpp \
	   $(SRC_DIR)/Circuit/CktContext.cpp \
	   $(SRC_DIR)/Circuit/Ladder/LadderRC.cpp \
	   $(SRC_DIR)/Circuit/Ladder/LadderRLC.cpp \
	   $(SRC_DIR)/Circuit/CoupledTree/CoupledTreeRC.cpp \
	   $(SRC_DIR)/Circuit/CoupledTree/CoupledTreeMRC.cpp \
	   $(SRC_DIR)/Circuit/ClockTree/ClockTreeR.cpp \
	   $(SRC_DIR)/Circuit/ClockTree/ClockTreeRC.cpp \
	   $(SRC_DIR)/Circuit/ClockTree/ClockTreeRRand.cpp \
	   $(SRC_DIR)/Circuit/ClockTree/ClockTreeRCRand.cpp \
	   $(SRC_DIR)/Circuit/ClockTree/ClockTreeRCLink.cpp \
       $(SRC_DIR)/Circuit/ClockTree/ClockTreeMesh.cpp \
	   $(SRC_DIR)/Circuit/Mesh/MeshR.cpp \
	   $(SRC_DIR)/Circuit/Mesh/MeshRC.cpp \
       $(SRC_DIR)/Circuit/RLine/RLine.cpp \
       $(SRC_DIR)/Circuit/PG/PGR.cpp \
       $(SRC_DIR)/Circuit/PG/PGRC.cpp

OBJ_DIR = build

OBJS = $(addprefix $(OBJ_DIR)/, $(subst .cpp,.o, $(SRCS)))
DEPS = $(addprefix $(OBJ_DIR)/, $(subst .cpp,.d, $(SRCS)))

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	CXX = clang++
endif
ifeq ($(UNAME), Linux)
	CXX = g++
endif

# for debug
CXXFLAGS = -Wall -g -std=c++11 -MMD $(INC_PATH) -DDEBUG -DTRACE
# for release
# CXXFLAGS = -w -O3 -std=c++11 -MMD $(INC_PATH) -DNDEBUG -DTRACE
# CXXFLAGS = -w -O3 -std=c++11 -MMD $(INC_PATH) -DNDEBUG

LDXXFLAGS = $(LIB_PATH) $(LIBS)

RM = rm -f

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDXXFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean distclean

clean:
	$(RM) $(OBJS)

distclean:
	$(RM) $(OBJS) $(TARGET) $(DEPS)

-include $(DEPS)
