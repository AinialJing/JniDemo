#ifndef JNIDEMO_SERIALPORT_H
#define JNIDEMO_SERIALPORT_H

#include <sys/ioctl.h>
#include "SerialPortLog.h"

#define TRUE 1
#define FALSE 0
typedef unsigned char BYTE;
struct SerialPortConfig {
    int baudrate; //波特率
    int dataBits;//数据位
    int stopBits;//结束位
    char parity;//校验位
};

class SerialPort {
private:
       const char *path;
       int fd;
       bool isClose;
    /**
  * @brief set serial port speed(baudrate) 设置波特率
  * @param fd device file
  * @param speed 串口的波特率 串口通讯速率：2400bps、4800bps、9600bps、19200bps、38400bps、115200bps。现在最常用的应该是115200bps的速率，不快不慢正合适-
  * @return
  */
    int setSpeed(int fd, int speed);

    /**
     * @brief
     * @param fd   device file
     * @param databits  数据位：可以是5bit、6Bit、7Bit、8Bit，其中最常用是8Bit
     * @param stopbits  结束位
     * @param parity    校验位：奇校验、偶校验、无校验，占用1bit，无校验位时不占用
     *                  偶校验（even parity）：校验原则是，数据位和校验位中1的个数为偶数
     *                  奇校验（odd parity）：校验原则是，数据位和校验位中1的个数为奇数
     *                  无校验：即时序图中没有校验位
     * @return
     */
    int setParity(int fd, int databits, int stopbits, char parity);

public:
    SerialPort();

    SerialPort(const char *path);

    //打开串口
    int openSerialPort(SerialPortConfig config);

    //读取数据
    int readData(BYTE *data, int size);

    //写入数据
    int writeData(BYTE *data, int size);

    //设置模式
    int setMode(int mode);

    //关闭串口
    int closePort();

    speed_t getBaudRate(int baudrate);
};


#endif //JNIDEMO_SERIALPORT_H
