################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Drivers/Circular\ Buffer/circularBuffer.obj: ../Drivers/Circular\ Buffer/circularBuffer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Drivers/Circular Buffer" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Drivers/ltc681x/crc" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Drivers/ltc681x/ltc" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Drivers/ltc681x/temperature" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Drivers/SOC SOH/battery" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Drivers/SOC SOH/soc" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/013_soc_soh/include" --include_path="C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="Drivers/Circular Buffer/circularBuffer.d_raw" --obj_directory="Drivers/Circular Buffer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


