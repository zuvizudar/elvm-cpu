## 概要

24bitCPU→37bitCPU(現在)

## ELVMとは

EsoLang Virtual Machineの略で、C言語で書かれたプログラムをELVM IRという中間形式に変換した後に、それを元に多言語にトランスパイルするものです。  
ELVM IR　の命令数は20個と、とても少ないので使用を決めました。

## ファイルの説明
cpu.v,decode.v,rom.v ----- cpu本体  
cpu_tb.v ----------------- テストベンチ  
ecpu.c ------------------- ELVMのバックエンド  
rom.ecpu ----------------- ROM(ecpu.cとchange.cで手に入る)  
change.cpp --------------- ROMファイルを整える.  



## TODO
今はjmp命令とか対応していないのでループとかはできない。putcharで一文字出力できる事は確認済み  
メモリの添字は24bit使いたいので、store dst,imにしよう。→メモリの添字8bitまで。dst8bitに拡張。  
data_mem[256]にカウンタ？  
store data_mem[rd_p]<=register[rs_p]
load register[rs_p]<=data_mem[data_mem[rd_p]](rd_pは1111111)



## DONE
DONE:ELVM IR　→　CPUのオペコード  
DONE:im...24bitにする  
DONE:負数をどうするか

## メモ

 |Register[]| name  |  num   |
 |----------|-------|--------|
 | 0        |   A   |  000   |
 | 1        |   B   |  001   |
 | 2        |   C   |  010   |
 | 3        |   D   |  011   |
 | 4        |   BP  |  100   |
 | 5        |   SP  |  101   |
 
 |  opcode  |description|
 |----------|-----------|
 |  00000   |    mov    |
 |  00001   |    add    |
 |  00010   |    sub    |
 |  00011   |    load   |
 |  00100   |    store  |
 |  00101   |    putc   |
 |  01000   |           |
 |  01001   |           |
 |  01010   |           |
 |  01011   |           |
 |  01100   |           |
 |  01101   |           |
 |  01110   |           |
 |  01111   |           |
 |  10000   |           |
 |  10001   |           |
 |  10010   |           |
 |  10011   |           |
 |  10100   |           |
 
is_sorce_im..1bit  
op...5bit  
rs...3bit  
rd...3bit  
im...24bitは必要  

## 参考

https://github.com/shinh/elvm
