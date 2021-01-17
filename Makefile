# Makefile for genckt

TARGET = genckt

SRC_DIR = Src

INC_PATH = -I$(SRC_DIR) \
           -I$(SRC_DIR)/Define \
		   -I$(SRC_DIR)/Utilities \
		   -I$(SRC_DIR)/Circuit \
		   -I$(SRC_DIR)/Circuit/Ladder \
		   -I$(SRC_DIR)/Circuit/Tree \
		   -I$(SRC_DIR)/Circuit/Mesh \
           -I$(SRC_DIR)/Circuit/RLine

LIB_PATH = 

LIBS = -lgflags

SRCS = $(SRC_DIR)/Main/Main.cpp \
	   $(SRC_DIR)/Utilities/MyString.cpp \
	   $(SRC_DIR)/Utilities/Utils.cpp \
	   $(SRC_DIR)/Circuit/CktBase.cpp \
	   $(SRC_DIR)/Circuit/CktContext.cpp \
	   $(SRC_DIR)/Circuit/Ladder/LadderRC.cpp \
	   $(SRC_DIR)/Circuit/Ladder/LadderRLC.cpp \
	   $(SRC_DIR)/Circuit/Tree/CoupledTreeRC.cpp \
	   $(SRC_DIR)/Circuit/Tree/CoupledTreeMRC.cpp \
	   $(SRC_DIR)/Circuit/Tree/ClockTreeR.cpp \
	   $(SRC_DIR)/Circuit/Tree/ClockTreeRC.cpp \
	   $(SRC_DIR)/Circuit/Tree/ClockTreeRRand.cpp \
	   $(SRC_DIR)/Circuit/Tree/ClockTreeRCRand.cpp \
	   $(SRC_DIR)/Circuit/Mesh/MeshR.cpp \
	   $(SRC_DIR)/Circuit/Mesh/MeshRC.cpp \
       $(SRC_DIR)/Circuit/RLine/RLine.cpp

OBJ_DIR = build

OBJS = $(addprefix $(OBJ_DIR)/, $(subst .cpp,.o, $(SRCS)))

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	CXX = clang++
endif
ifeq ($(UNAME), Linux)
	CXX = g++
endif

# for debug
CXXFLAGS = -Wall -g -std=c++11 $(INC_PATH) -DDEBUG -DTRACE
# for release
# CXXFLAGS = -w -O3 -std=c++11 $(INC_PATH) -DNDEBUG -DTRACE
# CXXFLAGS = -w -O3 -std=c++11 $(INC_PATH) -DNDEBUG

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
	$(RM) $(OBJS) $(TARGET)
