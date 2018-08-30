################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/bsp_win32.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/tgmn_win_tgmnif.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/bsp_win32.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/tgmn_win_tgmnif.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/bsp_win32.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/tgmn_win_tgmnif.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/%.o: ../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/win/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


