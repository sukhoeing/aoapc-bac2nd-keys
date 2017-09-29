[TOC]



# 补充题解 - 《经典》- 第 10 章数学概念与方法

## 习题10-14 标准差 Standard Deviation, UVa10886

不难想到简单的暴力解法，考虑标准差的计算公式：
$$
{1\over n}\sum_{i=1}^n (x_i - m)^2  =  {1\over n}\sum_{i=1}^n x_i^2-{2m\over n}\sum_{i=1}^n x_i+m^2\\
={1\over n}\sum_{i=1}^n x_i^2-m^2 \quad 其中 \ m = {\sum_{i=1}^nx_i \over n}
$$
但是这样时间效率并不是很高，即使AC，也是勉强通过。

思考一下有无有更好的办法，随机数生成器最容易出现重复问题。所以我们可以做个试验，使用hash判重(unordered_map)，就会发现在g = 0或者$g=2^{32}$之后就开始所有的g都一样。 g = 0之后的所有输出都是0，g = $2^{32}$的所有输出都是$2^{32}$了。实际上回到题面看的也很容易发现将这两个数字代入之后，所有的seed就永远是固定的数字了，之后就不需要继续循环，直接计算结果并返回即可。

## 习题 10-21 二项式系数 Binomial coefficients, ACM/ICPC NWERC 2011, UVa1649

对于固定的k，${n}\choose{k}$是相对于n单调递增的，不难想到使用对n使用二分来寻找所有等于m的${n}\choose{k}$。

但是这里存在一个问题，计算${n}\choose{k}$并且和二分查找中的mid比较时很容易溢出，有的同学考虑用浮点数，但是存在误差问题，并且计算速度较慢。不过可以考虑利用递推公式：${{n}\choose{k}} = {n-k+1\over n}{{n}\choose{k-1}}$，递推计算，每次先除以${{n}\choose{k-1}}$和$n$的最大公约数，之后n一定能被$n-k+1$整除，这样一旦大于mid，直接返回结果即可。

但是即使这样仍然可能会乘法时溢出，怎么办呢，使用另外一个技巧：
$$
a*b > 2^{63} \leftrightarrow a > 2^{63}/b
$$
这样在可以在乘法之前就检测溢出，而且m一定是小于$2^{63}$的，如果发现即将溢出，就可以确定要计算的值一定是大于m的，可以直接返回比较结果。

## 习题 10-24 幂之和(Sum of Powers, UVa766)

$$
(n+1)^{k+1}-n^{k+1}=\sum_{0≤i≤k}{k+1 \choose i}n^i \\
n^{k+1}-(n-1)^{k+1}=\sum_{0≤i≤k}{k+1 \choose i}(n-1)^i \\
... \\
2^{k+1}-1^{k+1}=\sum_{0≤i≤k} {k+1 \choose i} \cdot 1^i\\
$$
令 $F_k=\sum_{i=1}^ni^k$, 对上以上公式求和可得: 

$$
(n+1)^{k+1}-1 = \sum_{0\leq i \leq k}{k+1 \choose i} F_i \\
(k+1) \cdot F_k = (n+1)^{k+1}-1- \sum_{0\leq j < k} {k+1 \choose j}F_j=\sum_{1≤j≤k+1} {k+1 \choose j} \cdot n^k - \sum_{0≤i<k} {k+1 \choose i} F_i
$$

这样就可以从i = 0到k从小到大一次性全部递推计算出来。

注意本题是要求有理数结果，所以可以使用有理数类来完成四则运算:

```cpp
struct Rational {
  LL a, b;  // a/b
  Rational operator+(const Rational& r) {
    if (r.a == 0) return *this;
    LL na = a * r.b + b * r.a, nb = b * r.b;
    Rational ans = {na, nb};
    return ans.reduce();
  }
  Rational operator-(const Rational& r) {
    if (r.a == 0) return *this;
    Rational ans = {a * r.b - b * r.a, b * r.b};
    return ans.reduce();
  }
  Rational operator/(LL x) {
    assert(x);
    Rational ans = {a, b * x};
    return ans.reduce();
  }
  Rational operator*(LL x) {
    Rational ans = {a * x, b};
    return ans.reduce();
  }
  Rational& reduce() {
    LL g = gcd(a, b);
    a /= g, b /= g;
    return *this;
  }
};
```

## 习题 10-25 因子(Factors, ACM/ICPC World Finals 2013, UVa1575)

对于一个整数k来说，考虑其素数分解$k=p_1^{e_1}\cdotp_2^{e_2}\cdot\cdots p_m^{e_m}$。则$f(k)={(e_1+e_2+\cdots e_m)! \over e_1!e_2!\cdots e_m!}$。实际上与$p_1, p_2 \cdots p_m$无关。要求出最小的k, 那么就可以令$p_1, p_2 \cdots p_m$分别等于最小的素数，然后对$e_1, e_2 \cdots e_m$依次进行回溯，其中$e_i < 63$。计算f(k)时可能溢出，所以要提前算出所有可能的$e_i<63$的素因子分解，使用《经典》一书中 例题 10- 3 　 选择 与 除法（ Choose and Divide, UVa10375）中介绍的方法来计算f(k)。





