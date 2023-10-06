# 单片机（MCU）

**单片机**是指单个集成电路（Integrated Circuit, IC）芯片上的小型计算机（Micro Computer）。也称为微控制器（Microcontroller Unit , MCU）

## 基本架构

在MCU内部存在多个中央处理器单元（CPU）、易失性和非易失性存储器，以及可编程的输入和输出设备

- OSC （Oscillator） **晶体振荡器**，提供最基本的时钟源
- **相位锁相环**（Phase Locked Loop, PLL）电路，基于时钟源可以产生不太频率和相位的时钟信号
- **CPU**是指令集架构（Instruction Set Architecture, ISA）的具体实现，它采用的 ISA 决定了 MCU 的性能和特点
- **静态随机访问存储器**（Static Random Access Memory , SPAM ），暂时存储保存在程序运行过程中所需要的数据（易失性存储器，断电丢失数据）
- **闪存**（Flash Memory），保存程序代码（非易失性）
- **通用串行收发器**（Universal Asynchronous Receiver / Transmitter , UART）以串行方式发送和接收数据的简单外部设备（外设）
- **通用输入输出**（General Purpose Input / Output，GPIO）
- **定时器**（Timer）提供定时和计数功能
- **中断控制器**（Interrupt Controller）为 MCU 提供处理内部和外部事件的能力
- **外部存储器接口**（External Memory Interface，EMIF）为 MCU 提供连接外部 SRAM 芯片的能力
- 模拟数字转换器（Analog-to-Digital Convertor, ADC）和 数字模拟转换器（Digital-to-Analog Convertor, DAC）构建数字和模拟之间的桥梁

硬件开发平台：以 MCU 为核心的多功能硬件

**STC32G12K128** 

- 真32位数据总线的32位8051，只是指令集兼容 Intel80251 CISC指令集
- **Intel80251** 是8位数据总线，分时拼出16位，分时拼出32位

### 工作模式

- 间歇工作模式
- 休眠模式
- 冬眠模式

## 嵌入式操作系统

- mu C-OS 
- Free RTOS
- RTX51-Tiny
- RT-Thread

## 常见 CPU ISA

- MIPS 
- ARM (Advanced RISC Machine)
- MCS-51 (8051)
- MCS-251 (80251)
  - STC32G系列基于 80251 的 ISA,并对 MCUI 内 CPU 的实现结构进行了改进和优化
  - 也可以把STC32G当作 80251 玩，但这浪费了能力

### MCS-51 

- ISA 包含 111 条指令，是复杂指令集计算机（Complex Instruction Set Computer , CISC ）的典型代表
- CISC 具有可变指令长度，允许在存储器上执行算术和逻辑运算
- RISC （Reduced Instruction Set Computer）精简指令集计算机主要表现为指令长度固定，并且不支持在存储器上执行算数和逻辑运算
  - ARM Cortex-M 处理器的 ISA 就是 RISC
- MCS-251 是 MCS-51 的扩展，因此 MCS-251 是向下兼容的

### C251 Keil uVersion Target (CPU Mode)

- Binary Mode : 二进制模式： MCS-51 ISA
- Source Mode : 源模式 : MCS-251 ISA
  - 此模式在STC32上工作较好

## 嵌入式的三个层次

- 面向嵌入式硬件开发软件（不利于维护，难以移植）
- 面向嵌入式应用程序接口 (API）函数开发（无需过多关系底层硬件，容易移植）
- 借助嵌入式操作系统（实时响应和多任务）

