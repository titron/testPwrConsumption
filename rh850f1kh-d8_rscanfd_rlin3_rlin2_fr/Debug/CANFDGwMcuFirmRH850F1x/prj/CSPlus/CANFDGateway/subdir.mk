################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/boot.asm \
../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/vecttbl.asm 

OBJS += \
./CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/boot.o \
./CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/vecttbl.o 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/%.o: ../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


