################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_fr_irq.c \
../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irq.c \
../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irqbundling.c \
../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin3_irq.c \
../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rscfd_irq.c \
../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rscfd_irqbundling.c 

OBJS += \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_fr_irq.o \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irq.o \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irqbundling.o \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin3_irq.o \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rscfd_irq.o \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rscfd_irqbundling.o 

C_DEPS += \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_fr_irq.d \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irq.d \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin2_irqbundling.d \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rlin3_irq.d \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rscfd_irq.d \
./CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/map_rscfd_irqbundling.d 


# Each subdirectory must supply rules for building sources it contributes
CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/%.o: ../CANFDGwMcuFirmRH850F1x/src/devices/rh850g3k-f1kh-d8/intvec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


