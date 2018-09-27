################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_1.c \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_2.c \
../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_common.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_1.o \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_2.o \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_common.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_1.d \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_2.d \
./CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/flexray_application_common.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/%.o: ../CANFDGwMcuFirmRH850F1x/src/macros/fr/fr_flxa_0012/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


