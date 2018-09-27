################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/main_pe1.c \
../CANFDGwMcuFirmRH850F1x/src/test_port.c \
../CANFDGwMcuFirmRH850F1x/src/test_tmr.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/main_pe1.o \
./CANFDGwMcuFirmRH850F1x/src/test_port.o \
./CANFDGwMcuFirmRH850F1x/src/test_tmr.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/main_pe1.d \
./CANFDGwMcuFirmRH850F1x/src/test_port.d \
./CANFDGwMcuFirmRH850F1x/src/test_tmr.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/%.o: ../CANFDGwMcuFirmRH850F1x/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


