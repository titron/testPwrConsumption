################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/Gr_Lib_v2.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/QVGA-2.8-8_16B_v2.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/QVGA-2.8-SPI.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/VC_Debug.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/VirtualDisplay_v2.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/WVGA-7Inch-8_16B_v2.c \
../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/WinLib.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/Gr_Lib_v2.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/QVGA-2.8-8_16B_v2.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/QVGA-2.8-SPI.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/VC_Debug.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/VirtualDisplay_v2.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/WVGA-7Inch-8_16B_v2.o \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/WinLib.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/Gr_Lib_v2.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/QVGA-2.8-8_16B_v2.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/QVGA-2.8-SPI.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/VC_Debug.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/VirtualDisplay_v2.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/WVGA-7Inch-8_16B_v2.d \
./CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/WinLib.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/%.o: ../CANFDGwMcuFirmRH850F1x/src/test_app/tgmn/gfxlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


