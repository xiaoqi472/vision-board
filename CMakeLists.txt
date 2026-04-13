CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m85)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
SET(CMAKE_ASM_COMPILER "/usr/bin/arm-none-eabi-gcc")
SET(CMAKE_C_FLAGS " -march=armv8.1-m.main+mve.fp+fp.dp -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -Wall")
SET(CMAKE_ASM_FLAGS " -c -march=armv8.1-m.main+mve.fp+fp.dp -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")
SET(CMAKE_CXX_FLAGS " -march=armv8.1-m.main+mve.fp+fp.dp -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -Wall")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "/usr/bin/arm-none-eabi-objcopy")
SET(CMAKE_SIZE "/usr/bin/arm-none-eabi-size")

SET(CMAKE_EXE_LINKER_FLAGS " -march=armv8.1-m.main+mve.fp+fp.dp -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/script/fsp.ld -L ../script/ -Wl,--gc-sections,--print-memory-usage")

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)

PROJECT(rtthread C CXX ASM)

INCLUDE_DIRECTORIES(
	.
	ra_gen
	board
	board/ports
	board/ports/wifi
	ra/arm/CMSIS_5/CMSIS/Core/Include
	ra/fsp/inc
	ra/fsp/inc/api
	ra/fsp/inc/instances
	ra/tes/dave2d/inc
	ra/tes/dave2d/inc/tes
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/include/freertos
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/include
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/portable/rt-thread
	ra_cfg/fsp_cfg
	ra_cfg/fsp_cfg/bsp
	../../../include
	../../../libcpu/arm/common
	../../../libcpu/arm/cortex-m85
	../../../components/net/utest
	../../../components/libc/compilers/newlib
	../../../components/libc/compilers/common/include
	../../../components/libc/posix/ipc
	../../../components/libc/posix/io/eventfd
	../../../components/libc/posix/io/poll
	../../../components/libc/posix/io/epoll
	../../../components/drivers/include
	../../../components/drivers/smp_call
	../../../components/drivers/phy
	../../../components/finsh
	../libraries/HAL_Drivers/drivers
	../libraries/HAL_Drivers/drivers/config
	../libraries/HAL_Drivers
)

ADD_DEFINITIONS(
	-DBSP_CFG_RTOS=2
	-D__RTTHREAD__
	-DRT_USING_NEWLIBC
	-DRT_USING_LIBC
	-D_POSIX_C_SOURCE=1
)

# Library source files
SET(RT_APPLICATIONS_SOURCES
	src/hal_entry.c
)

SET(RT_CPU_SOURCES
	../../../libcpu/arm/common/atomic_arm.c
	../../../libcpu/arm/common/div0.c
	../../../libcpu/arm/common/showmem.c
	../../../libcpu/arm/cortex-m85/context_gcc.S
	../../../libcpu/arm/cortex-m85/cpuport.c
)

SET(RT_DEVICEDRIVERS_SOURCES
	../../../components/drivers/core/device.c
	../../../components/drivers/ipc/completion_comm.c
	../../../components/drivers/ipc/completion_up.c
	../../../components/drivers/ipc/condvar.c
	../../../components/drivers/ipc/dataqueue.c
	../../../components/drivers/ipc/pipe.c
	../../../components/drivers/ipc/ringblk_buf.c
	../../../components/drivers/ipc/ringbuffer.c
	../../../components/drivers/ipc/waitqueue.c
	../../../components/drivers/ipc/workqueue.c
	../../../components/drivers/pin/dev_pin.c
	../../../components/drivers/serial/dev_serial_v2.c
)

SET(RT_DRIVERS_SOURCES
	board/ports/drv_sdram.c
	board/ra8_it.c
	../libraries/HAL_Drivers/drivers/drv_gpio.c
	../libraries/HAL_Drivers/drivers/drv_usart_v2.c
	../libraries/HAL_Drivers/drv_common.c
)

SET(RT_FINSH_SOURCES
	../../../components/finsh/shell.c
	../../../components/finsh/msh.c
	../../../components/finsh/msh_parse.c
	../../../components/finsh/cmd.c
)

SET(RT_FREERTOS_SOURCES
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/event_groups.c
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/list.c
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/queue.c
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/tasks.c
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/timers.c
	packages/FreeRTOS_Wrapper-latest/FreeRTOS/portable/rt-thread/port.c
)

SET(RT_KERNEL_SOURCES
	../../../src/clock.c
	../../../src/components.c
	../../../src/cpu_up.c
	../../../src/defunct.c
	../../../src/idle.c
	../../../src/ipc.c
	../../../src/irq.c
	../../../src/kservice.c
	../../../src/memheap.c
	../../../src/mempool.c
	../../../src/object.c
	../../../src/scheduler_comm.c
	../../../src/scheduler_up.c
	../../../src/thread.c
	../../../src/timer.c
)

SET(RT_LIBC_SOURCES
	../../../components/libc/compilers/common/cctype.c
	../../../components/libc/compilers/common/cstdlib.c
	../../../components/libc/compilers/common/cstring.c
	../../../components/libc/compilers/common/ctime.c
	../../../components/libc/compilers/common/cunistd.c
	../../../components/libc/compilers/common/cwchar.c
	../../../components/libc/compilers/newlib/syscalls.c
	../../../src/klibc/kerrno.c
	../../../src/klibc/kstdio.c
	../../../src/klibc/kstring.c
	../../../src/klibc/rt_vsnprintf_tiny.c
	../../../src/klibc/rt_vsscanf.c
)

SET(RT_RA_SOURCES
	ra/fsp/src/bsp/mcu/all/bsp_clocks.c
	ra/fsp/src/bsp/mcu/all/bsp_common.c
	ra/fsp/src/bsp/mcu/all/bsp_delay.c
	ra/fsp/src/bsp/mcu/all/bsp_group_irq.c
	ra/fsp/src/bsp/mcu/all/bsp_guard.c
	ra/fsp/src/bsp/mcu/all/bsp_io.c
	ra/fsp/src/bsp/mcu/all/bsp_irq.c
	ra/fsp/src/bsp/mcu/all/bsp_register_protection.c
	ra/fsp/src/bsp/mcu/all/bsp_rom_registers.c
	ra/fsp/src/bsp/mcu/all/bsp_sbrk.c
	ra/fsp/src/bsp/mcu/all/bsp_security.c
	ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.c
	ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c
	ra/fsp/src/r_ceu/r_ceu.c
	ra/fsp/src/r_drw/r_drw_base.c
	ra/fsp/src/r_drw/r_drw_irq.c
	ra/fsp/src/r_drw/r_drw_memory.c
	ra/fsp/src/r_glcdc/r_glcdc.c
	ra/fsp/src/r_gpt/r_gpt.c
	ra/fsp/src/r_ioport/r_ioport.c
	ra/fsp/src/r_mipi_dsi/r_mipi_dsi.c
	ra/fsp/src/r_mipi_phy/r_mipi_phy.c
	ra/fsp/src/r_sci_b_uart/r_sci_b_uart.c
)

SET(RT_RA_CFG_SOURCES
)

SET(RT_RA_GEN_SOURCES
	ra_gen/common_data.c
	ra_gen/hal_data.c
	ra_gen/main.c
	ra_gen/pin_data.c
	ra_gen/vector_data.c
)

SET(RT_UTC_UTEST_SOURCES
)

SET(RT_UTESTCASES_SOURCES
)

# Library search paths
# Library local macro definitions
SET(RT_DEVICEDRIVERS_DEFINES
	__RT_IPC_SOURCE__
)

SET(RT_KERNEL_DEFINES
	__RT_KERNEL_SOURCE__
)

# Library dependencies
SET(RT_LIBC_LIBS
	c
	m
)

# Libraries
ADD_LIBRARY(rtt_CPU OBJECT ${RT_CPU_SOURCES})
ADD_LIBRARY(rtt_DeviceDrivers OBJECT ${RT_DEVICEDRIVERS_SOURCES})
ADD_LIBRARY(rtt_Drivers OBJECT ${RT_DRIVERS_SOURCES})
ADD_LIBRARY(rtt_Finsh OBJECT ${RT_FINSH_SOURCES})
ADD_LIBRARY(rtt_FreeRTOS OBJECT ${RT_FREERTOS_SOURCES})
ADD_LIBRARY(rtt_Kernel OBJECT ${RT_KERNEL_SOURCES})
ADD_LIBRARY(rtt_Libc OBJECT ${RT_LIBC_SOURCES})
ADD_LIBRARY(rtt_ra OBJECT ${RT_RA_SOURCES})
ADD_LIBRARY(rtt_ra_gen OBJECT ${RT_RA_GEN_SOURCES})

# Interface libraries
ADD_LIBRARY(rtt_ra_cfg INTERFACE)
ADD_LIBRARY(rtt_utc_UTest INTERFACE)
ADD_LIBRARY(rtt_utestcases INTERFACE)

# Private macros
TARGET_COMPILE_DEFINITIONS(rtt_DeviceDrivers PRIVATE ${RT_DEVICEDRIVERS_DEFINES})
TARGET_COMPILE_DEFINITIONS(rtt_Kernel PRIVATE ${RT_KERNEL_DEFINES})

# Interface library search paths
TARGET_LINK_LIBRARIES(rtt_Libc INTERFACE ${RT_LIBC_LIBS})

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${RT_APPLICATIONS_SOURCES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}.elf
	rtt_CPU
	rtt_DeviceDrivers
	rtt_Drivers
	rtt_Finsh
	rtt_FreeRTOS
	rtt_Kernel
	rtt_Libc
	rtt_ra
	rtt_ra_gen
	rtt_ra_cfg
	rtt_utc_UTest
	rtt_utestcases
)

ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
	COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_PROJECT_NAME}.elf rtthread.hex
	COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf
)

# if custom.cmake is exist, add it
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
endif()
