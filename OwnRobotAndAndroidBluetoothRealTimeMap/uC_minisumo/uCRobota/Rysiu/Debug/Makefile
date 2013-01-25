################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
LIB_AS_ARGS :=
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
HEX_FLASH_FILE_PATH :=
HEX_FLASH_FILE_PATH_AS_ARGS :=
HEX_EEPROM_FILE_PATH :=
HEX_EEPROM_FILE_PATH_AS_ARGS :=
LSS_FILE_PATH :=
LSS_FILE_PATH_AS_ARGS :=
MAP_FILE_PATH :=
MAP_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=D:/ProgramowanieAVR/AVR Studio 5.0/AVR ToolChain/bin/
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Includes \
../Usefull


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Rysiu.c \
../Usefull/Enkoders.c \
../Usefull/I2C.c \
../Usefull/Sharp.c \
../Usefull/Silniki.c \
../Usefull/USART.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Rysiu.o \
Usefull/Enkoders.o \
Usefull/I2C.o \
Usefull/Sharp.o \
Usefull/Silniki.o \
Usefull/USART.o


OBJS_AS_ARGS +=  \
Rysiu.o \
Usefull/Enkoders.o \
Usefull/I2C.o \
Usefull/Sharp.o \
Usefull/Silniki.o \
Usefull/USART.o


C_DEPS +=  \
Rysiu.d \
Usefull/Enkoders.d \
Usefull/I2C.d \
Usefull/Sharp.d \
Usefull/Silniki.d \
Usefull/USART.d


C_DEPS_AS_ARGS +=  \
Rysiu.d \
Usefull/Enkoders.d \
Usefull/I2C.d \
Usefull/Sharp.d \
Usefull/Silniki.d \
Usefull/USART.d


OUTPUT_FILE_PATH +=Rysiu.elf

OUTPUT_FILE_PATH_AS_ARGS +=Rysiu.elf

HEX_FLASH_FILE_PATH +=Rysiu.hex

HEX_FLASH_FILE_PATH_AS_ARGS +=Rysiu.hex

HEX_EEPROM_FILE_PATH +=Rysiu.eep

HEX_EEPROM_FILE_PATH_AS_ARGS +=Rysiu.eep

LSS_FILE_PATH +=Rysiu.lss

LSS_FILE_PATH_AS_ARGS +=Rysiu.lss

MAP_FILE_PATH =Rysiu.map

MAP_FILE_PATH_AS_ARGS =Rysiu.map

LIB_AS_ARGS +=libRysiu.a

ADDITIONAL_DEPENDENCIES:= $(HEX_FLASH_FILE_PATH) $(LSS_FILE_PATH) $(HEX_EEPROM_FILE_PATH) size

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR/GNU C Compiler













./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O3 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99  -mmcu=atmega8   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

Usefull/%.o: ../Usefull/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O3 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99  -mmcu=atmega8   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<



# AVR/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

# AVR/GNU C/C++ Linker
$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C/C++ Linker
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE)  -mmcu=atmega8  -Wl,-Map=$(MAP_FILE_PATH_AS_ARGS) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@



$(HEX_FLASH_FILE_PATH): $(OUTPUT_FILE_PATH)
	$(QUOTE)$(AVR_APP_PATH)avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature  $(QUOTE)$<$(QUOTE) $(QUOTE)$@$(QUOTE)

$(HEX_EEPROM_FILE_PATH): $(OUTPUT_FILE_PATH)
	-$(QUOTE)$(AVR_APP_PATH)avr-objcopy.exe$(QUOTE) -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex $(QUOTE)$<$(QUOTE) $(QUOTE)$@$(QUOTE) || exit 0

$(LSS_FILE_PATH): $(OUTPUT_FILE_PATH)
	$(QUOTE)$(AVR_APP_PATH)avr-objdump.exe$(QUOTE) -h -S $(QUOTE)$<$(QUOTE) > $(QUOTE)$@$(QUOTE)

size: $(OUTPUT_FILE_PATH)
	@$(QUOTE)$(AVR_APP_PATH)avr-size.exe$(QUOTE) -C --mcu=atmega8 $(OUTPUT_FILE_PATH_AS_ARGS)

# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) $(LIB_AS_ARGS) $(HEX_FLASH_FILE_PATH_AS_ARGS) $(HEX_EEPROM_FILE_PATH_AS_ARGS) $(LSS_FILE_PATH_AS_ARGS) $(MAP_FILE_PATH_AS_ARGS)

