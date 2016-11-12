################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/msp430_4.2.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./APP/main.obj" \
"./BSP/Motor.obj" \
"./BSP/Init.obj" \
"./BSP/Frame.obj" \
"./BSP/DISPLAY.obj" \
"./BSP/AT24C64.obj" \
"./SOURCE/UART.obj" \
"./SOURCE/ScanIF.obj" \
"./SOURCE/LCD.obj" \
"./SOURCE/I2C.obj" \
"./SOURCE/Comparator_A.obj" \
"./SOURCE/BasicTimer.obj" \
"../lnk_msp430fw427.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include SOURCE/subdir_vars.mk
-include BSP/subdir_vars.mk
-include APP/subdir_vars.mk
-include subdir_rules.mk
-include SOURCE/subdir_rules.mk
-include BSP/subdir_rules.mk
-include APP/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LI_wuci.out

# Tool invocations
LI_wuci.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi --advice:power=all -g --define=__MSP430FW427__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z -m"LI_wuci.map" --heap_size=80 --stack_size=80 -i"C:/ti/ccsv5/ccs_base/msp430/include" -i"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/lib" -i"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="LI_wuci_linkInfo.xml" --rom_model -o "LI_wuci.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "LI_wuci.out"
	-$(RM) "SOURCE\BasicTimer.pp" "SOURCE\Comparator_A.pp" "SOURCE\I2C.pp" "SOURCE\LCD.pp" "SOURCE\ScanIF.pp" "SOURCE\UART.pp" "BSP\AT24C64.pp" "BSP\DISPLAY.pp" "BSP\Frame.pp" "BSP\Init.pp" "BSP\Motor.pp" "APP\main.pp" 
	-$(RM) "SOURCE\BasicTimer.obj" "SOURCE\Comparator_A.obj" "SOURCE\I2C.obj" "SOURCE\LCD.obj" "SOURCE\ScanIF.obj" "SOURCE\UART.obj" "BSP\AT24C64.obj" "BSP\DISPLAY.obj" "BSP\Frame.obj" "BSP\Init.obj" "BSP\Motor.obj" "APP\main.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

