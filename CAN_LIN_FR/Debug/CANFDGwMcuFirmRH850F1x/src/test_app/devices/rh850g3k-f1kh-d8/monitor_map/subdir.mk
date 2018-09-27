################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/bsp_asmn.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/lowinit.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/bsp_asmn.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/lowinit.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/bsp_asmn.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/lowinit.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/%.o: ../CANFDGwMcuFirmRH850F1x/src/test_app/devices/rh850g3k-f1kh-d8/monitor_map/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


