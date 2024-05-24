################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ORKA/System/%.obj: ../ORKA/System/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/UserDefinedApis/Sox" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/UserDefinedApis/CellLookUpTable" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/UserDefinedApis/CircularBuffer" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/System" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/System/Tasks" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/UserDefinedApis" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/ORKA/UserDefinedApis/CircularBuffer" --include_path="C:/Users/mehmet.dincer/Desktop/MehDin/codeComposer/013_soc_soh/013_soc_soh/include" --include_path="C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="ORKA/System/$(basename $(<F)).d_raw" --obj_directory="ORKA/System" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


