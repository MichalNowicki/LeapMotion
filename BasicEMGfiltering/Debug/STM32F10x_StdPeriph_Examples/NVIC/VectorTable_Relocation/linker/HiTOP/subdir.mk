################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../STM32F10x_StdPeriph_Examples/NVIC/VectorTable_Relocation/linker/HiTOP/setstack.asm 

OBJS += \
./STM32F10x_StdPeriph_Examples/NVIC/VectorTable_Relocation/linker/HiTOP/setstack.o 

ASM_DEPS += \
./STM32F10x_StdPeriph_Examples/NVIC/VectorTable_Relocation/linker/HiTOP/setstack.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F10x_StdPeriph_Examples/NVIC/VectorTable_Relocation/linker/HiTOP/%.o: ../STM32F10x_StdPeriph_Examples/NVIC/VectorTable_Relocation/linker/HiTOP/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


