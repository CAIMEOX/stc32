# STC 概述
## ISP 和 IAP
- 在系统编程（In system programming, ISP）：本地固化程序
- 在应用编程（In application programming, IAP）：程序更新
  - 结构上将 Flash 存储器划映射为两个存储空间
  - 其中一个存储空间的程序可以对另一个空间进行编程，随后转移控制权
  - $\text{ISP}\in\text{IAP}$

## STC32 命名规则
$$\text{STC}32\underline{Xx}\text{K}\underline{xx}$$
- STC 宏晶科技公式公司的单片机
- $32$ 表示32位单片机
- $X$ 表示32位单片机的子系列
  - $X=\text{G}$ 无硬件浮点运算单元
  - $X=\text{F}$ 有硬件浮点运算单元
- $x\text{K}$ SRAM 容量
  - 容量单位为 KiB
- $xx$ Flash 容量大小

## 封装类型
- 双列直插式封装 (Dual Inline-Pin Package, DIP)
  - 引脚逆时针排序，第一个引脚在芯片左下角
- 薄型四方扁平式封装（Low-profile Quad Flat Package LQFP）
  - 引脚逆时针排序，第一个引脚在芯片左下角
  - 引脚之间空隙较小
- 方形扁平无引脚（Quad Flat No-lead, QFN）

## 引脚驱动模式
- 准双向输出：可用作输入和输出功能，无需重新配置 IO 输出状态
- 强推挽输出
- 仅输入（高阻）
- 开漏输出