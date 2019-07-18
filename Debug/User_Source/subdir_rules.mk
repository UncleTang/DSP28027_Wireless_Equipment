################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
User_Source/%.obj: ../User_Source/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/$(basename $(<F)).d_raw" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

User_Source/User_Initialization\ .obj: ../User_Source/User_Initialization\ .c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_Initialization .d_raw" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

User_Source/%.obj: ../User_Source/%.C $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/$(basename $(<F)).d_raw" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


