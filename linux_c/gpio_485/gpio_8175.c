#include "gpio.h"
#include "common_hdr.h"
#include "aciga/log.h"

//MTK平台的gpio控制方式，通过sysfs pinctrl
// echo mode 132 0 >/sys/devices/platform/soc/1000b000.pinctrl/mt_gpio
// echo dir 132 1 >/sys/devices/platform/soc/1000b000.pinctrl/mt_gpio
// echo out 132 1 >/sys/devices/platform/soc/1000b000.pinctrl/mt_gpio

#ifdef MT8175

/**
 * @brief : gpio 导出
 * @param : pin
 * @retval: 0 成功; -1失败
 */
int gpio_export(const int pin)
{
    int fd, len;
    char buffer[200];
    char cmd[128];

    sprintf(cmd, "/sys/devices/platform/soc/1000b000.pinctrl/mt_gpio");
    open_gpio_file(cmd, O_WRONLY, fd);

    //TODO: cat /sys/devices/platform/soc/1000b000.pinctrl/mt_gpio 查看gpio状态

    //mode mux: 0 gpio
    len = snprintf(cmd, sizeof(cmd), "mode %d 0 ", pin);
    aciga_log_info("cmd len=%d cmd=%s", len, cmd);

    if (write(fd, cmd, len) < 0)
    {
        err_out("write failed to export gpio!\n");
        return -1;
    }

    close(fd);

    return 0;
}
/**
 * @brief : gpio 卸载
 * @param : pin
 * @retval: 0 成功; -1失败
 */
int gpio_unexport(const int pin)
{
    err_out("this platform not support gpio_unexport !\n");
    return 0;
}

/**
 * @brief : gpio 方向控制
 * @param : dir 方向(in/out)
 * @retval: 0 成功; -1失败
 */
int gpio_direction(const int pin, const char *dir)
{
    int fd;
    char path[128];
    char cmd[200];
    int len;

    int dir_value = (!strcmp(dir, "out")) ? 1 : 0;

    snprintf(path, sizeof(path), "/sys/devices/platform/soc/1000b000.pinctrl/mt_gpio");
    open_gpio_file(path, O_WRONLY, fd);

    len = snprintf(cmd, sizeof(cmd), "dir %d %d ", pin, dir_value);
    aciga_log_info("cmd len=%d cmd=%s", len, cmd);

    if (write(fd, cmd, len) < 0)
    {
        err_out("Failed to set direction!\n");
        return -1;
    }

    close(fd);
    return 0;
}

/**
 * @brief : gpio 写
 * @param : 0 / 1
 * @retval: 0 成功; -1失败
 */
int gpio_write(const int pin, const int value)
{
    int fd;
    char path[64];
    char cmd[128];
    int len;

    snprintf(path, sizeof(path), "/sys/devices/platform/soc/1000b000.pinctrl/mt_gpio");
    open_gpio_file(path, O_WRONLY, fd);

    len = snprintf(cmd, sizeof(cmd), "out %d %d", pin, !!value);

    aciga_log_info("cmd len=%d cmd=%s", len, cmd);
    if (write(fd, cmd, len) < 0)
    {
        err_out("Failed to write value!\n");
        return -1;
    }

    close(fd);
    return 0;
}

/**
 * @brief : gpio 读
 * @param : 读取的引脚值
 * @retval: 返回引脚的值 0 / 1
 */
int gpio_read(const int pin)
{
   err_out("Not support yet, gpio_read");
   return -1;
}

/**
 * @brief : gpio 中断控制
 * @param : 0 none 表示引脚为输入，不是中断引脚
 *   @arg : 1 rising 表示引脚为中断输入，上升沿触发
 *   @arg : 2 falling 表示引脚为中断输入，下降沿触发
 *   @arg : 3 both 表示引脚为中断输入，边沿触发
 * @retval:
 */
int gpio_edge(const int pin, int edge)
{
    err_out("Not support yet, gpio_edge");
    return 0;
}

#endif