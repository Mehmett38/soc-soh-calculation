################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
SOC\ SOH/soc/soc.obj: ../SOC\ SOH/soc/soc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/SOC SOH/battery" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/SOC SOH/soc" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/Circular Buffer" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/013_soc_soh/include" --include_path="C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="SOC SOH/soc/soc.d_raw" --obj_directory="SOC SOH/soc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


