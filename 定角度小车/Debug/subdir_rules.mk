################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hua/workspace_ccstheia/定角度小车/WIT" -I"/home/hua/workspace_ccstheia/定角度小车/PID" -I"/home/hua/workspace_ccstheia/定角度小车/CONTROL" -I"/home/hua/workspace_ccstheia/定角度小车" -I"/home/hua/workspace_ccstheia/定角度小车/Debug" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source" -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1218392262: ../empty.syscfg
	@echo 'SysConfig - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/utils/sysconfig_1.28.0/sysconfig_cli.sh" -s "/home/hua/ti/mspm0_sdk_2_11_00_07/.metadata/product.json" --script "/home/hua/workspace_ccstheia/定角度小车/empty.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1218392262 ../empty.syscfg
device.opt: build-1218392262
device.cmd.genlibs: build-1218392262
ti_msp_dl_config.c: build-1218392262
ti_msp_dl_config.h: build-1218392262
Event.dot: build-1218392262

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hua/workspace_ccstheia/定角度小车/WIT" -I"/home/hua/workspace_ccstheia/定角度小车/PID" -I"/home/hua/workspace_ccstheia/定角度小车/CONTROL" -I"/home/hua/workspace_ccstheia/定角度小车" -I"/home/hua/workspace_ccstheia/定角度小车/Debug" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source" -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: /home/hua/ti/mspm0_sdk_2_11_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hua/workspace_ccstheia/定角度小车/WIT" -I"/home/hua/workspace_ccstheia/定角度小车/PID" -I"/home/hua/workspace_ccstheia/定角度小车/CONTROL" -I"/home/hua/workspace_ccstheia/定角度小车" -I"/home/hua/workspace_ccstheia/定角度小车/Debug" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source" -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


