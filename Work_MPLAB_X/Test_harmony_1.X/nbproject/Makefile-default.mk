#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=D:/Work_MPLAB_X/Test_harmony_1.X/main.c D:/Work_MPLAB_X/Test_harmony_1.X/app.c D:/Work_MPLAB_X/Test_harmony_1.X/system_config.c D:/Work_MPLAB_X/Test_harmony_1.X/system_init.c D:/Work_MPLAB_X/Test_harmony_1.X/system_interrupt.c D:/Work_MPLAB_X/Test_harmony_1.X/system_tasks.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/490314204/main.o ${OBJECTDIR}/_ext/490314204/app.o ${OBJECTDIR}/_ext/490314204/system_config.o ${OBJECTDIR}/_ext/490314204/system_init.o ${OBJECTDIR}/_ext/490314204/system_interrupt.o ${OBJECTDIR}/_ext/490314204/system_tasks.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/490314204/main.o.d ${OBJECTDIR}/_ext/490314204/app.o.d ${OBJECTDIR}/_ext/490314204/system_config.o.d ${OBJECTDIR}/_ext/490314204/system_init.o.d ${OBJECTDIR}/_ext/490314204/system_interrupt.o.d ${OBJECTDIR}/_ext/490314204/system_tasks.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/490314204/main.o ${OBJECTDIR}/_ext/490314204/app.o ${OBJECTDIR}/_ext/490314204/system_config.o ${OBJECTDIR}/_ext/490314204/system_init.o ${OBJECTDIR}/_ext/490314204/system_interrupt.o ${OBJECTDIR}/_ext/490314204/system_tasks.o

# Source Files
SOURCEFILES=D:/Work_MPLAB_X/Test_harmony_1.X/main.c D:/Work_MPLAB_X/Test_harmony_1.X/app.c D:/Work_MPLAB_X/Test_harmony_1.X/system_config.c D:/Work_MPLAB_X/Test_harmony_1.X/system_init.c D:/Work_MPLAB_X/Test_harmony_1.X/system_interrupt.c D:/Work_MPLAB_X/Test_harmony_1.X/system_tasks.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/490314204/main.o: D:/Work_MPLAB_X/Test_harmony_1.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/main.o.d" -o ${OBJECTDIR}/_ext/490314204/main.o D:/Work_MPLAB_X/Test_harmony_1.X/main.c   
	
${OBJECTDIR}/_ext/490314204/app.o: D:/Work_MPLAB_X/Test_harmony_1.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/app.o.d" -o ${OBJECTDIR}/_ext/490314204/app.o D:/Work_MPLAB_X/Test_harmony_1.X/app.c   
	
${OBJECTDIR}/_ext/490314204/system_config.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_config.o.d" -o ${OBJECTDIR}/_ext/490314204/system_config.o D:/Work_MPLAB_X/Test_harmony_1.X/system_config.c   
	
${OBJECTDIR}/_ext/490314204/system_init.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_init.o.d" -o ${OBJECTDIR}/_ext/490314204/system_init.o D:/Work_MPLAB_X/Test_harmony_1.X/system_init.c   
	
${OBJECTDIR}/_ext/490314204/system_interrupt.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/490314204/system_interrupt.o D:/Work_MPLAB_X/Test_harmony_1.X/system_interrupt.c   
	
${OBJECTDIR}/_ext/490314204/system_tasks.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_tasks.o.d" -o ${OBJECTDIR}/_ext/490314204/system_tasks.o D:/Work_MPLAB_X/Test_harmony_1.X/system_tasks.c   
	
else
${OBJECTDIR}/_ext/490314204/main.o: D:/Work_MPLAB_X/Test_harmony_1.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/main.o.d" -o ${OBJECTDIR}/_ext/490314204/main.o D:/Work_MPLAB_X/Test_harmony_1.X/main.c   
	
${OBJECTDIR}/_ext/490314204/app.o: D:/Work_MPLAB_X/Test_harmony_1.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/app.o.d" -o ${OBJECTDIR}/_ext/490314204/app.o D:/Work_MPLAB_X/Test_harmony_1.X/app.c   
	
${OBJECTDIR}/_ext/490314204/system_config.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_config.o.d" -o ${OBJECTDIR}/_ext/490314204/system_config.o D:/Work_MPLAB_X/Test_harmony_1.X/system_config.c   
	
${OBJECTDIR}/_ext/490314204/system_init.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_init.o.d" -o ${OBJECTDIR}/_ext/490314204/system_init.o D:/Work_MPLAB_X/Test_harmony_1.X/system_init.c   
	
${OBJECTDIR}/_ext/490314204/system_interrupt.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/490314204/system_interrupt.o D:/Work_MPLAB_X/Test_harmony_1.X/system_interrupt.c   
	
${OBJECTDIR}/_ext/490314204/system_tasks.o: D:/Work_MPLAB_X/Test_harmony_1.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/490314204 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/490314204/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/490314204/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/microchip/harmony/v0_80_02b/framework/peripheral" -I"C:/microchip/harmony/v0_80_02b/framework/driver" -I"C:/microchip/harmony/v0_80_02b/bsp" -I"C:/microchip/harmony/v0_80_02b/framework" -I"C:/microchip/harmony/v0_80_02b/framework/system" -MMD -MF "${OBJECTDIR}/_ext/490314204/system_tasks.o.d" -o ${OBJECTDIR}/_ext/490314204/system_tasks.o D:/Work_MPLAB_X/Test_harmony_1.X/system_tasks.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:\\microchip\\harmony\\v0_80_02b\\bin\\framework\\peripheral\\PIC32MX320F128H_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\microchip\harmony\v0_80_02b\bin\framework\peripheral\PIC32MX320F128H_peripherals.a       -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:\\microchip\\harmony\\v0_80_02b\\bin\\framework\\peripheral\\PIC32MX320F128H_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\microchip\harmony\v0_80_02b\bin\framework\peripheral\PIC32MX320F128H_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Test_harmony_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
