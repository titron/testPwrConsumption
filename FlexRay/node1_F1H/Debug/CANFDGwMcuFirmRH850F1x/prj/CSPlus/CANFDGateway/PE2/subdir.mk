################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/cstartm.asm 

C_SRCS += \
../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/main.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/cstartm.o \
./CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/main.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/main.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/%.o: ../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/%.o: ../CANFDGwMcuFirmRH850F1x/prj/CSPlus/CANFDGateway/PE2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


