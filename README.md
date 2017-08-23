## 概要

24bitCPU

## ELVMとは

EsoLang Virtual Machineの略で、C言語で書かれたプログラムをELVM IRという中間形式に変換した後に、それを元に多言語にトランスパイルするものです。

ELVM IR　の命令数は20個と、とても少ないので使用を決めました。

## TODO

ELVM IR　→　CPUのオペコード

## メモ

 | Register | Size  |  num   |
-|----------|-------|--------|
0| A        | 24bit |  000   |
1| B        | 24bit |  001   |
2| C        | 24bit |  010   |
3| D        | 24bit |  011   |
4| BP       | 24bit |  100   |
5| SP       | 24bit |  101   |



## 参考

https://github.com/shinh/elvm
