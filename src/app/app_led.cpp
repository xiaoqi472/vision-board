#include "app_led.h"

/**
 * @brief 构造函数，初始化 AppLED 实例。
 *
 * 在此阶段仅进行成员变量的纯粹赋值操作，严禁调用任何硬件相关的 API。
 */
AppLED::AppLED() : pin(-1), delay_ms(500) {
    // 第 1 阶段：纯粹的赋值操作，严禁在此调用任何硬件 API！
}

/**
 * @brief 析构函数，清理 AppLED 实例。
 *
 * 在此阶段，它会分离 RT-Thread 线程对象。
 */
AppLED::~AppLED() {
    rt_thread_detach(&thread_obj);
}

/**
 * @brief 初始化 LED 硬件（GPIO 引脚）。
 *
 * 此函数负责设置 LED 的 GPIO 引脚模式为输出，并将其初始状态设置为低电平。
 *
 * @param pin_number LED 连接的 GPIO 引脚号。
 * @return RT_EOK 表示初始化成功。
 */
rt_err_t AppLED::Init(rt_base_t pin_number) {
    // 第 2 阶段：硬件初始化
    this->pin = pin_number;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, PIN_LOW);
    
    return RT_EOK;
}

/**
 * @brief RT-Thread 线程的静态入口函数。
 *
 * 此函数作为 RT-Thread 线程的入口点，负责将传入的参数转换为 AppLED 实例指针，
 * 并调用该实例的 run() 方法来执行 LED 闪烁逻辑。
 *
 * @param parameter 指向 AppLED 实例的 void 指针。
 */
void AppLED::thread_entry(void* parameter) {
    AppLED* instance = static_cast<AppLED*>(parameter);
    if (instance) {
        instance->run();
    }
}

/**
 * @brief LED 闪烁的主循环逻辑。
 *
 * 此方法包含一个无限循环，用于周期性地切换 LED 引脚的高低电平，
 * 从而实现 LED 的闪烁效果，闪烁间隔由 delay_ms 控制。
 */
void AppLED::run() {
    while (1) {
        rt_pin_write(pin, PIN_HIGH);
        rt_thread_mdelay(delay_ms);
        rt_pin_write(pin, PIN_LOW);
        rt_thread_mdelay(delay_ms);
    }
}

/**
 * @brief 启动 LED 闪烁线程。
 *
 * 此函数设置 LED 的闪烁延迟，并初始化一个 RT-Thread 静态线程来执行 LED 闪烁任务。
 * 线程初始化成功后，会启动该线程。
 *
 * @param blink_delay_ms LED 闪烁的延迟时间（毫秒）。
 */
void AppLED::start(rt_uint32_t blink_delay_ms) {
    this->delay_ms = blink_delay_ms;
    
    // 静态初始化 RT-Thread 线程（不使用堆内存分配或 'new'）
    rt_err_t result = rt_thread_init(&thread_obj,
                                     "led_blink",
                                     AppLED::thread_entry,
                                     this,
                                     &thread_stack[0],
                                     sizeof(thread_stack),
                                     25,
                                     5);
                               
    if (result == RT_EOK) {
        rt_thread_startup(&thread_obj);
        rt_kprintf("C++ LED static thread initialized.\n");
    } else {
        rt_kprintf("Failed to init C++ LED thread!\n");
    }
}
