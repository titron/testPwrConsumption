################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/test_app/asmn/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/macros/rscanfd/rscanfd_uciaprcn_v3/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/macros/rlin3/rlin3_uciaprln/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/macros/ports/standardports/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/subdir.mk
-include CANFDGwMcuFirmRH850F1x/src/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/GHS\ MULTI/CAN\ Gateway/shared/src/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/GHS\ MULTI/CAN\ Gateway/pe2_project/src/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/GHS\ MULTI/CAN\ Gateway/output/obj/shared/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/GHS\ MULTI/CAN\ Gateway/output/obj/pe2/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/GHS\ MULTI/CAN\ Gateway/output/obj/pe1/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/DefaultBuild/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/DefaultBuild/1st/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/DefaultBuild/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/DefaultBuild/subdir.mk
-include CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: node2_f1k

# Tool invocations
node2_f1k: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc  -o "node2_f1k" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) node2_f1k
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
