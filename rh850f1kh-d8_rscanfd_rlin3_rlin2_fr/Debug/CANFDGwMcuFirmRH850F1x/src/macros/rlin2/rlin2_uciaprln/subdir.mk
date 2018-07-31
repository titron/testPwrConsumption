################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_a.c \
../CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_as.c \
../CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_p.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_a.o \
./CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_as.o \
./CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_p.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_a.d \
./CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_as.d \
./CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/rlin2_p.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/%.o: ../CANFDGwMcuFirmRH850F1x/src/macros/rlin2/rlin2_uciaprln/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


