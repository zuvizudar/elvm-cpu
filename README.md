## 概要

26bitCPU  
c → elvm ir → elvm-cpuの命令　　

## ELVMとは
EsoLang Virtual Machineの略で、C言語で書かれたプログラムをELVM IRという中間形式に変換した後に、それを元に多言語にトランスパイルするものです。  
https://github.com/shinh/elvm  

## ファイルの説明
src.....cpuのコード  
data.....romの遷移  
tool.....romを整えます  
pre......rs232出力を加える前のcpu本体とテストベンチが入ってます  

## こんな感じ
![s_cpu_demo](https://user-images.githubusercontent.com/21309141/34920052-f9ad2ed8-f9af-11e7-974b-79cfc5604362.jpeg)

## TODO
	elvm側で終了判定付け足す
## DONE
DONE:ELVM IR　→　CPUのオペコード  
DONE:im...8bitにする  
DONE:負数をどうするか  
DONE:jmpでまだ到達していないlabelに飛べない
DONE:rs232で画面出力とかしたい。。  

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
 |  01110   |    jeq    |
 |  01111   |   	    |
 |  10000   |           |
 |  10001   |           |
 |  10010   |           |
 |  10011   |           |
 |  10100   |    jmp    |
 |  10101   | label_memo|
 |	10110	| lebel_cnt |
 |  11111   |    exit   |
 
is_sorce_im..1bit  
op...5bit  
rd...8bit  
rs...3bit
is_negative_num...1bit  
im...8bit


