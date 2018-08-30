################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/cstartm.asm 

OBJS += \
./CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/cstartm.o 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/%.o: ../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE1/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


