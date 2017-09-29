[TOC]



# 例题补充 - 《经典》- 第 10 章数学概念与方法

## 例题 10- 23 　 多少 块 土地（ How Many Pieces of Land?, UVa10213）

原书例题的思路是正确的，但是提供的代码无法在限定时间内解决问题，需要推导出公式并且使用大整数进行计算。
$$
V - E + F = 2 \implies F = E + 2 - V \\
$$
所求结果就是:
$$
E + 1 - V = {n \over 2} \sum_{i=1}^{n-2}(i(n-2-i)+1)-{n\over 4}\sum_{i=1}^{n-2}(i(n-2-i)+1) \\
={n(n-1)(n^2-5n+18) \over 24}
$$

具体代码请参考[这里](https://github.com/sukhoeing/aoapc-bac2nd/blob/master/ch10/UVa10213.cpp "代码")。



