## change 

2進数で扱っているため、バックエンドだけでは桁溢れの問題があり、対処出来なかったのでromを整える為にあります。  
g++ change.cpp -o change   
change >hello.rom  

## rm_underbar

readmembはアンダーバーを無視してくれるはずなんですが、無視してくれないので使います(TT)  
g++ rm_underbar.cpp -o rm_underbar  
rm_underbar >hello.rom
