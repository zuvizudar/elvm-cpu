## 概要

24bitCPU

## ELVMとは

EsoLang Virtual Machineの略で、C言語で書かれたプログラムをELVM IRという中間形式に変換した後に、それを元に多言語にトランスパイルするものです。

ELVM IR　の命令数は20個と、とても少ないので使用を決めました。

## TODO

ELVM IR　→　CPUのオペコード

## メモ

 | Register | name  |  num   |
 |----------|-------|--------|
 | 0        |   A   |  000   |
 | 1        |   B   |  001   |
 | 2        |   C   |  010   |
 | 3        |   D   |  011   |
 | 4        |   SP  |  100   |
 | 5        |   DP  |  101   |



## 参考

https://github.com/shinh/elvm
