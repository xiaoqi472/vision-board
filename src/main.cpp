#include <sys/time.h>
#include <ctime>
using std::clock_t;
using std::time_t;
#include <rtthread.h>
#include "hal_data.h" // IWYU pragma: keep
#include "app_led.h"

#define LED_PIN BSP_IO_PORT_01_PIN_02 // RA8D1 Vision Board 板载 LED

// 全局静态实例（分配在 .bss/.data 段，不使用堆内存！）
AppLED sys_led;

extern "C" {

/**
 * @brief HAL 层入口函数
 *
 * 此函数是 HAL 层的入口点。它负责初始化系统，包括打印欢迎信息、初始化板载 LED
 * 并启动其闪烁线程。之后，主线程将进入一个无限循环，以防止程序退出。
 */
void hal_entry(void) {
    rt_kprintf("\n[C++] Welcome to the Object-Oriented RT-Thread Layer!\n");

    // 第 2 阶段：硬件资源初始化
    rt_err_t err = sys_led.Init(LED_PIN);
    if (err != RT_EOK) {
        rt_kprintf("LED initialization failed!\n");
        return;
    }
    
    // 启动静态闪烁线程
    sys_led.start(500);

    // 挂起主线程使其永远不退出，防止资源清理工作撑爆空闲线程（tidle0）的极小堆栈
    while (1) {
        rt_thread_mdelay(1000); 
    }
}

} // extern "C"
