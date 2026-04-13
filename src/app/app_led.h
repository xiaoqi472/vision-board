#ifndef APP_LED_H_
#define APP_LED_H_

#include <sys/time.h>
#include <ctime>
using std::clock_t;
using std::time_t;
#include <rtthread.h>
#include <rtdevice.h>

// C++ 类：用于 LED 控制
/**
 * @brief 用于控制 LED 的 C++ 类
 *
 * 该类封装了 LED 的硬件操作和 RT-Thread 线程管理，
 * 允许用户通过简单的 API 控制 LED 的闪烁行为。
 */
class AppLED {
private:
    rt_base_t pin;
    rt_uint32_t delay_ms;

    // 分配在静态内存区的 RT-Thread 线程控制块及栈内存（严禁动态分配！）
    struct rt_thread thread_obj;
    rt_uint8_t thread_stack[1024] __attribute__((aligned(RT_ALIGN_SIZE)));

    // 静态跳板函数，供 RT-Thread C API 回调进入 C++ 类的成员函数
    static void thread_entry(void* parameter);

    // 实际的 C++ 线程执行例程
    void run();

public:
    // 第 1 阶段：安全的构造函数（绝不能包含针对硬件的外设操作！）
    AppLED();
    ~AppLED();

    // 第 2 阶段：硬件及软件资源初始化
    rt_err_t Init(rt_base_t pin_number);

    // 启动闪烁线程
    void start(rt_uint32_t blink_delay_ms);
};

#endif /* APP_LED_H_ */
