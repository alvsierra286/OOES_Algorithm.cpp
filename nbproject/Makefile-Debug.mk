#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Sources/Compute_Epsilon_Value.o \
	${OBJECTDIR}/Sources/OOES_Finders.o \
	${OBJECTDIR}/Sources/OOES_Solver.o \
	${OBJECTDIR}/Sources/Partial_Solutions.o \
	${OBJECTDIR}/Sources/Priority_Queue.o \
	${OBJECTDIR}/Sources/Read_Model.o \
	${OBJECTDIR}/Sources/Results.o \
	${OBJECTDIR}/Sources/Split_Triangle_Horizontal.o \
	${OBJECTDIR}/Sources/Split_Triangle_Vertical.o \
	${OBJECTDIR}/Sources/Variables_Declaration.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/opt/CPLEX/12.7/cplex/lib/x86-64_linux/static_pic/libilocplex.a /opt/CPLEX/12.7/cplex/lib/x86-64_linux/static_pic/libcplex.a /opt/CPLEX/12.7/concert/lib/x86-64_linux/static_pic/libconcert.a -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk OOES

OOES: /opt/CPLEX/12.7/cplex/lib/x86-64_linux/static_pic/libilocplex.a

OOES: /opt/CPLEX/12.7/cplex/lib/x86-64_linux/static_pic/libcplex.a

OOES: /opt/CPLEX/12.7/concert/lib/x86-64_linux/static_pic/libconcert.a

OOES: ${OBJECTFILES}
	${LINK.cc} -o OOES ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Sources/Compute_Epsilon_Value.o: Sources/Compute_Epsilon_Value.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Compute_Epsilon_Value.o Sources/Compute_Epsilon_Value.cpp

${OBJECTDIR}/Sources/OOES_Finders.o: Sources/OOES_Finders.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/OOES_Finders.o Sources/OOES_Finders.cpp

${OBJECTDIR}/Sources/OOES_Solver.o: Sources/OOES_Solver.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/OOES_Solver.o Sources/OOES_Solver.cpp

${OBJECTDIR}/Sources/Partial_Solutions.o: Sources/Partial_Solutions.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Partial_Solutions.o Sources/Partial_Solutions.cpp

${OBJECTDIR}/Sources/Priority_Queue.o: Sources/Priority_Queue.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Priority_Queue.o Sources/Priority_Queue.cpp

${OBJECTDIR}/Sources/Read_Model.o: Sources/Read_Model.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Read_Model.o Sources/Read_Model.cpp

${OBJECTDIR}/Sources/Results.o: Sources/Results.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Results.o Sources/Results.cpp

${OBJECTDIR}/Sources/Split_Triangle_Horizontal.o: Sources/Split_Triangle_Horizontal.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Split_Triangle_Horizontal.o Sources/Split_Triangle_Horizontal.cpp

${OBJECTDIR}/Sources/Split_Triangle_Vertical.o: Sources/Split_Triangle_Vertical.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Split_Triangle_Vertical.o Sources/Split_Triangle_Vertical.cpp

${OBJECTDIR}/Sources/Variables_Declaration.o: Sources/Variables_Declaration.cpp
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Variables_Declaration.o Sources/Variables_Declaration.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DIL_STD -IHeaders -I/opt/CPLEX/12.7/concert/include -I/opt/CPLEX/12.7/cplex/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
