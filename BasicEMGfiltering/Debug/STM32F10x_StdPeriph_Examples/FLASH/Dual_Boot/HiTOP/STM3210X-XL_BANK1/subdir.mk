################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/cstart_thumb2.asm \
../STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/setstack.asm 

OBJS += \
./STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/cstart_thumb2.o \
./STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/setstack.o 

ASM_DEPS += \
./STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/cstart_thumb2.d \
./STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/setstack.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/%.o: ../STM32F10x_StdPeriph_Examples/FLASH/Dual_Boot/HiTOP/STM3210X-XL_BANK1/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


