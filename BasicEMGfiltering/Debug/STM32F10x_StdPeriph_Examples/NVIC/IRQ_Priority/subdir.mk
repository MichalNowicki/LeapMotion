################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/main.c \
../STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/stm32f10x_it.c \
../STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/system_stm32f10x.c 

OBJS += \
./STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/main.o \
./STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/stm32f10x_it.o \
./STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/system_stm32f10x.o 

C_DEPS += \
./STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/main.d \
./STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/stm32f10x_it.d \
./STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/%.o: ../STM32F10x_StdPeriph_Examples/NVIC/IRQ_Priority/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_CL -DUSE_STDPERIPH_DRIVER -I"D:\ProgramowanieARM\ProjektARM\Debug/../Libraries/CMSIS/CM3" -I"D:\ProgramowanieARM\ProjektARM\Debug/../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:\ProgramowanieARM\ProjektARM\Debug/../Libraries/CMSIS/CM3/CoreSupport" -I"D:\ProgramowanieARM\ProjektARM\Debug/../" -I"D:\ProgramowanieARM\ProjektARM\Debug/../Libraries/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


