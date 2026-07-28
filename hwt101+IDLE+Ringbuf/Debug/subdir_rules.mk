################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/WIT" -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf" -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/Debug" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source" -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-494916275: ../empty.syscfg
	@echo 'SysConfig - building file: "$<"'
	"/home/hua/ti/sysconfig_1.26.2/sysconfig_cli.sh" -s "/home/hua/ti/mspm0_sdk_2_11_00_07/.metadata/product.json" --script "/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/empty.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-494916275 ../empty.syscfg
device.opt: build-494916275
device.cmd.genlibs: build-494916275
ti_msp_dl_config.c: build-494916275
ti_msp_dl_config.h: build-494916275
Event.dot: build-494916275

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/WIT" -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf" -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/Debug" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source" -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: /home/hua/ti/mspm0_sdk_2_11_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"/home/hua/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/WIT" -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf" -I"/home/hua/workspace_ccstheia/hwt101+IDLE+Ringbuf/Debug" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/hua/ti/mspm0_sdk_2_11_00_07/source" -gdwarf-3 -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


