################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../013_soc_soh/source/sys_link.cmd 

ASM_SRCS += \
../013_soc_soh/source/dabort.asm \
../013_soc_soh/source/os_portasm.asm \
../013_soc_soh/source/sys_core.asm \
../013_soc_soh/source/sys_intvecs.asm \
../013_soc_soh/source/sys_mpu.asm \
../013_soc_soh/source/sys_pmu.asm 

C_SRCS += \
../013_soc_soh/source/errata_SSWF021_45.c \
../013_soc_soh/source/esm.c \
../013_soc_soh/source/gio.c \
../013_soc_soh/source/het.c \
../013_soc_soh/source/notification.c \
../013_soc_soh/source/os_croutine.c \
../013_soc_soh/source/os_event_groups.c \
../013_soc_soh/source/os_heap.c \
../013_soc_soh/source/os_list.c \
../013_soc_soh/source/os_mpu_wrappers.c \
../013_soc_soh/source/os_port.c \
../013_soc_soh/source/os_queue.c \
../013_soc_soh/source/os_tasks.c \
../013_soc_soh/source/os_timer.c \
../013_soc_soh/source/pinmux.c \
../013_soc_soh/source/sci.c \
../013_soc_soh/source/spi.c \
../013_soc_soh/source/sys_dma.c \
../013_soc_soh/source/sys_main.c \
../013_soc_soh/source/sys_pcr.c \
../013_soc_soh/source/sys_phantom.c \
../013_soc_soh/source/sys_pmm.c \
../013_soc_soh/source/sys_selftest.c \
../013_soc_soh/source/sys_startup.c \
../013_soc_soh/source/sys_vim.c \
../013_soc_soh/source/system.c 

C_DEPS += \
./013_soc_soh/source/errata_SSWF021_45.d \
./013_soc_soh/source/esm.d \
./013_soc_soh/source/gio.d \
./013_soc_soh/source/het.d \
./013_soc_soh/source/notification.d \
./013_soc_soh/source/os_croutine.d \
./013_soc_soh/source/os_event_groups.d \
./013_soc_soh/source/os_heap.d \
./013_soc_soh/source/os_list.d \
./013_soc_soh/source/os_mpu_wrappers.d \
./013_soc_soh/source/os_port.d \
./013_soc_soh/source/os_queue.d \
./013_soc_soh/source/os_tasks.d \
./013_soc_soh/source/os_timer.d \
./013_soc_soh/source/pinmux.d \
./013_soc_soh/source/sci.d \
./013_soc_soh/source/spi.d \
./013_soc_soh/source/sys_dma.d \
./013_soc_soh/source/sys_main.d \
./013_soc_soh/source/sys_pcr.d \
./013_soc_soh/source/sys_phantom.d \
./013_soc_soh/source/sys_pmm.d \
./013_soc_soh/source/sys_selftest.d \
./013_soc_soh/source/sys_startup.d \
./013_soc_soh/source/sys_vim.d \
./013_soc_soh/source/system.d 

OBJS += \
./013_soc_soh/source/dabort.obj \
./013_soc_soh/source/errata_SSWF021_45.obj \
./013_soc_soh/source/esm.obj \
./013_soc_soh/source/gio.obj \
./013_soc_soh/source/het.obj \
./013_soc_soh/source/notification.obj \
./013_soc_soh/source/os_croutine.obj \
./013_soc_soh/source/os_event_groups.obj \
./013_soc_soh/source/os_heap.obj \
./013_soc_soh/source/os_list.obj \
./013_soc_soh/source/os_mpu_wrappers.obj \
./013_soc_soh/source/os_port.obj \
./013_soc_soh/source/os_portasm.obj \
./013_soc_soh/source/os_queue.obj \
./013_soc_soh/source/os_tasks.obj \
./013_soc_soh/source/os_timer.obj \
./013_soc_soh/source/pinmux.obj \
./013_soc_soh/source/sci.obj \
./013_soc_soh/source/spi.obj \
./013_soc_soh/source/sys_core.obj \
./013_soc_soh/source/sys_dma.obj \
./013_soc_soh/source/sys_intvecs.obj \
./013_soc_soh/source/sys_main.obj \
./013_soc_soh/source/sys_mpu.obj \
./013_soc_soh/source/sys_pcr.obj \
./013_soc_soh/source/sys_phantom.obj \
./013_soc_soh/source/sys_pmm.obj \
./013_soc_soh/source/sys_pmu.obj \
./013_soc_soh/source/sys_selftest.obj \
./013_soc_soh/source/sys_startup.obj \
./013_soc_soh/source/sys_vim.obj \
./013_soc_soh/source/system.obj 

ASM_DEPS += \
./013_soc_soh/source/dabort.d \
./013_soc_soh/source/os_portasm.d \
./013_soc_soh/source/sys_core.d \
./013_soc_soh/source/sys_intvecs.d \
./013_soc_soh/source/sys_mpu.d \
./013_soc_soh/source/sys_pmu.d 

OBJS__QUOTED += \
"013_soc_soh\source\dabort.obj" \
"013_soc_soh\source\errata_SSWF021_45.obj" \
"013_soc_soh\source\esm.obj" \
"013_soc_soh\source\gio.obj" \
"013_soc_soh\source\het.obj" \
"013_soc_soh\source\notification.obj" \
"013_soc_soh\source\os_croutine.obj" \
"013_soc_soh\source\os_event_groups.obj" \
"013_soc_soh\source\os_heap.obj" \
"013_soc_soh\source\os_list.obj" \
"013_soc_soh\source\os_mpu_wrappers.obj" \
"013_soc_soh\source\os_port.obj" \
"013_soc_soh\source\os_portasm.obj" \
"013_soc_soh\source\os_queue.obj" \
"013_soc_soh\source\os_tasks.obj" \
"013_soc_soh\source\os_timer.obj" \
"013_soc_soh\source\pinmux.obj" \
"013_soc_soh\source\sci.obj" \
"013_soc_soh\source\spi.obj" \
"013_soc_soh\source\sys_core.obj" \
"013_soc_soh\source\sys_dma.obj" \
"013_soc_soh\source\sys_intvecs.obj" \
"013_soc_soh\source\sys_main.obj" \
"013_soc_soh\source\sys_mpu.obj" \
"013_soc_soh\source\sys_pcr.obj" \
"013_soc_soh\source\sys_phantom.obj" \
"013_soc_soh\source\sys_pmm.obj" \
"013_soc_soh\source\sys_pmu.obj" \
"013_soc_soh\source\sys_selftest.obj" \
"013_soc_soh\source\sys_startup.obj" \
"013_soc_soh\source\sys_vim.obj" \
"013_soc_soh\source\system.obj" 

C_DEPS__QUOTED += \
"013_soc_soh\source\errata_SSWF021_45.d" \
"013_soc_soh\source\esm.d" \
"013_soc_soh\source\gio.d" \
"013_soc_soh\source\het.d" \
"013_soc_soh\source\notification.d" \
"013_soc_soh\source\os_croutine.d" \
"013_soc_soh\source\os_event_groups.d" \
"013_soc_soh\source\os_heap.d" \
"013_soc_soh\source\os_list.d" \
"013_soc_soh\source\os_mpu_wrappers.d" \
"013_soc_soh\source\os_port.d" \
"013_soc_soh\source\os_queue.d" \
"013_soc_soh\source\os_tasks.d" \
"013_soc_soh\source\os_timer.d" \
"013_soc_soh\source\pinmux.d" \
"013_soc_soh\source\sci.d" \
"013_soc_soh\source\spi.d" \
"013_soc_soh\source\sys_dma.d" \
"013_soc_soh\source\sys_main.d" \
"013_soc_soh\source\sys_pcr.d" \
"013_soc_soh\source\sys_phantom.d" \
"013_soc_soh\source\sys_pmm.d" \
"013_soc_soh\source\sys_selftest.d" \
"013_soc_soh\source\sys_startup.d" \
"013_soc_soh\source\sys_vim.d" \
"013_soc_soh\source\system.d" 

ASM_DEPS__QUOTED += \
"013_soc_soh\source\dabort.d" \
"013_soc_soh\source\os_portasm.d" \
"013_soc_soh\source\sys_core.d" \
"013_soc_soh\source\sys_intvecs.d" \
"013_soc_soh\source\sys_mpu.d" \
"013_soc_soh\source\sys_pmu.d" 

ASM_SRCS__QUOTED += \
"../013_soc_soh/source/dabort.asm" \
"../013_soc_soh/source/os_portasm.asm" \
"../013_soc_soh/source/sys_core.asm" \
"../013_soc_soh/source/sys_intvecs.asm" \
"../013_soc_soh/source/sys_mpu.asm" \
"../013_soc_soh/source/sys_pmu.asm" 

C_SRCS__QUOTED += \
"../013_soc_soh/source/errata_SSWF021_45.c" \
"../013_soc_soh/source/esm.c" \
"../013_soc_soh/source/gio.c" \
"../013_soc_soh/source/het.c" \
"../013_soc_soh/source/notification.c" \
"../013_soc_soh/source/os_croutine.c" \
"../013_soc_soh/source/os_event_groups.c" \
"../013_soc_soh/source/os_heap.c" \
"../013_soc_soh/source/os_list.c" \
"../013_soc_soh/source/os_mpu_wrappers.c" \
"../013_soc_soh/source/os_port.c" \
"../013_soc_soh/source/os_queue.c" \
"../013_soc_soh/source/os_tasks.c" \
"../013_soc_soh/source/os_timer.c" \
"../013_soc_soh/source/pinmux.c" \
"../013_soc_soh/source/sci.c" \
"../013_soc_soh/source/spi.c" \
"../013_soc_soh/source/sys_dma.c" \
"../013_soc_soh/source/sys_main.c" \
"../013_soc_soh/source/sys_pcr.c" \
"../013_soc_soh/source/sys_phantom.c" \
"../013_soc_soh/source/sys_pmm.c" \
"../013_soc_soh/source/sys_selftest.c" \
"../013_soc_soh/source/sys_startup.c" \
"../013_soc_soh/source/sys_vim.c" \
"../013_soc_soh/source/system.c" 


