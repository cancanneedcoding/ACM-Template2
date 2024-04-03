## 杂项

https://codeforces.com/contest/1921/problem/F 2100

- 根号分治 + 带权前缀和  

https://codeforces.com/contest/1400/problem/E  2400

- 分治较为模版题目， 带点贪心，每次选择整个区间最小值操作，然后递归左右两边区间做处理

https://codeforces.com/contest/1696/problem/D 1900

- 分治处理，由于是排列所以区间 $\max$ 和 $\min$ 唯一，按两者位置递归左区间和右区间处理

## 图论

https://codeforces.com/problemset/problem/1108/F  2100

- 判断 MST 唯一（trick）

https://codeforces.com/contest/1156/problem/D 2200

- 并查集好题，根据 0 1 边权合并计算贡献，再考虑每个点作为中转站 

https://codeforces.com/contest/1027/problem/D 1700

- 拓扑排序模版题，带点贪心，最终从每个环取一个点，所以拓扑找出所有环 

## 数据结构

https://codeforces.com/contest/609/problem/E 2100

- 树链 + 并查集 + RMQ 

https://codeforces.com/contest/1691/problem/D 1800

- 单调栈+RMQ 

https://atcoder.jp/contests/abc343/tasks/abc343_f  1370

- 入门线段树，维护最大值次大值，最大值出现次数，次大值出现次数 

https://codeforces.com/contest/1156/problem/E 2200

- 单调栈 + 优化枚举 

https://codeforces.com/problemset/problem/145/E 2400

- 线段树，权值仅 01 维护最长不递减子序列 

https://codeforces.com/contest/242/problem/E 2000

- 线段树区间异或，拆成二进制位维护 

https://codeforces.com/contest/1436/problem/E 2400

- 有关 mex 问题，使用线段树判断每个 $i$ 是否可能成为某个子数组的 mex 

https://codeforces.com/contest/145/problem/E 2400

- 只有 $01$，线段树维护最长最长非降子序列，最长非增子序列 

https://atcoder.jp/contests/abc331/tasks/abc331_f 1600

- 线段树维护区间回文 

https://atcoder.jp/contests/abc223/tasks/abc223_f 1641

- 线段树维护区间括号是否匹配 

https://atcoder.jp/contests/abc306/tasks/abc306_e  1268

- 对顶堆维护区间前 $k$​ 大之和模版题

https://atcoder.jp/contests/abc127/tasks/abc127_f 2000

- 对顶堆维护中位数 + 两堆之和

### 动态规划

https://atcoder.jp/contests/abc207/tasks/abc207_e 1820

- 类似前缀和优化DP (按余数进行桶分类) 

https://atcoder.jp/contests/abc339/tasks/abc339_e 1109

- 线段树优化 DP

https://atcoder.jp/contests/abc129/tasks/abc129_e 1550

- 只对二进制位进行讨论的 DP 题

https://atcoder.jp/contests/abc130/tasks/abc130_e 1676

- 求两个数组的公共子序列方案数



## 数学

https://atcoder.jp/contests/abc146/tasks/abc146_e  1762
- 需知道等式 $(S_i-S_j)\bmod k = j-i$ 可以转换为 $(S_i-j)\bmod k=(S_j -j)\bmod k$。

## 位运算
https://codeforces.com/contest/1285/problem/D  1900
- 对于某个 bit，全为 $0$ 选 $0$，全为 $1$ 选 1，否则递归选择处理，选择较小的返回值作为答案加上当前位的值。有点在字典树上做 dp 的感觉，但事实上不需要创建出字典树。
