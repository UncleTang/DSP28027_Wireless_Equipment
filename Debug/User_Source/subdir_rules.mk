################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
User_Source/Main.obj: ../User_Source/Main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/Main.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_ADC.obj: ../User_Source/User_ADC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_ADC.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_Filter.obj: ../User_Source/User_Filter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_Filter.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_Initialization\ .obj: ../User_Source/User_Initialization\ .c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_Initialization .d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_PID.obj: ../User_Source/User_PID.C $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_PID.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_Protect.obj: ../User_Source/User_Protect.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_Protect.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_SCI.obj: ../User_Source/User_SCI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_SCI.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

User_Source/User_Soft_start.obj: ../User_Source/User_Soft_start.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt -Ooff --opt_for_speed=0 --include_path="E:/TI6/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_CMD" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Library" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/TI_Source" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Heads" --include_path="C:/Users/User/Documents/workspace/WPT_receiver_dc_dc/User_Source" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="User_Source/User_Soft_start.d" --obj_directory="User_Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


