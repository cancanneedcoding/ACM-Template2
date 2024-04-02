## 杂项

https://codeforces.com/contest/1921/problem/F：根号分治 + 带权前缀和  2100

https://codeforces.com/contest/1400/problem/E  分治较为模版题目 2400

## 图论

https://codeforces.com/problemset/problem/1108/F 判断 MST 唯一（trick）2100

https://codeforces.com/contest/1156/problem/D 并查集好题，根据 0 1 边权合并计算贡献，再考虑每个点作为中转站 2200

https://codeforces.com/contest/1027/problem/D 拓扑排序好题，最终从每个环取一个点，所以拓扑找出所有环 1700

## 数据结构

https://codeforces.com/contest/609/problem/E 树链 + 并查集 + RMQ 2100

https://codeforces.com/contest/1691/problem/D 单调栈+RMQ 1800

https://atcoder.jp/contests/abc343/tasks/abc343_f  入门线段树，维护最大值次大值，最大值出现次数，次大值出现次数 1370

https://codeforces.com/contest/1156/problem/E 单调栈 + 优化枚举 2200

https://codeforces.com/problemset/problem/145/E 线段树，权值仅 01 维护最长不递减子序列 2400

https://codeforces.com/contest/242/problem/E 线段树区间异或，拆成二进制位维护 2000

https://codeforces.com/contest/1436/problem/E 有关 mex 问题，使用线段树判断每个 i 是否可能成为某个子数组的 mex 2400

https://codeforces.com/contest/145/problem/E 只有 01，线段树维护最长最长非降子序列，最长非增子序列 2400

https://atcoder.jp/contests/abc331/tasks/abc331_f 线段树维护区间回文 16000

https://atcoder.jp/contests/abc223/tasks/abc223_f 线段树维护区间括号是否匹配 1641

### 动态规划

https://atcoder.jp/contests/abc207/tasks/abc207_e 类似前缀和优化DP (按余数进行桶分类) 1820

https://atcoder.jp/contests/abc339/tasks/abc339_e 线段树优化 dp 1109

## 数学

https://atcoder.jp/contests/abc146/tasks/abc146_e  1762
- 需知道等式 $(S_i-S_j)\bmod k = j-i$ 可以转换为 $(S_i-j)\bmod k=(S_j -j)\bmod k$。

## 位运算
https://codeforces.com/contest/1285/problem/D  1900
- 对于某个 bit，全为 0 选 0，全为 1 选 1，否则递归选择处理，选择较小的返回值作为答案加上当前位的值。有点在字典树上做 dp 的感觉，但事实上不需要创建出字典树
