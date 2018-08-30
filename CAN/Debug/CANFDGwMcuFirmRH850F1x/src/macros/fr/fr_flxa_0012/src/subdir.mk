################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_conf.c \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_data_transfer.c \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_error_status_signaling.c \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_state.c \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_test_mode.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_conf.o \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_data_transfer.o \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_error_status_signaling.o \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_state.o \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_test_mode.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_conf.d \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_data_transfer.d \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_error_status_signaling.d \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_state.d \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/FrDrv_test_mode.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/%.o: ../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


