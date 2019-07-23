################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
TI_Source/%.obj: ../TI_Source/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_CMD" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_Library" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_Source" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/User_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="TI_Source/$(basename $(<F)).d_raw" --obj_directory="TI_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TI_Source/%.obj: ../TI_Source/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_CMD" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_Library" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/TI_Source" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/User_Heads" --include_path="C:/Users/tag/Desktop/wireless_project/my_program/WPT_receiver_dc_dc_adc_pwm_git/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="TI_Source/$(basename $(<F)).d_raw" --obj_directory="TI_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


