# BinaryIndexedTree
参考博文：https://www.cnblogs.com/xenny/p/9739600.html

//其初衷是解决数据压缩里的累积频率（Cumulative Frequency）的计算问题，
//现多用于高效计算数列的前缀和， 区间和。它可以 以 O(logn) 的时间得到任意前缀和（区间和）。
//树状数组是动态维护前缀和的工具

//lowbit(x)表示x在二进制下最低位1和后面的0构成的数值

//把t[x]中x转换为二进制数发现每一层的末尾0的个数是相同的,而且0的个数与其覆盖的长度有关
//eg：总共有8个数(下标从1开始)，
//t[1]t[3]t[5]t[7]为第一层，index分别为：0001, 0011, 0101, 0111
//t[2]t[6]为第二层，index分别为0010, 0110
//t[4]为第三层，index为0100
//t[8]为第四层，index为1000
//t[x]节点覆盖的长度为lowbit(x)
//t[x]节点的父节点为t[x+lowbit(x)]
//整棵树的深度为logn+1
//for( i = 1; i <= x&(-x); i++)
//      c[x] += t[ x - ( x & (-x) ) + i]

//int lowbit(int x){
//    return x&(-x);
//}

//void updata(int i,int k){    //在i位置加上k
//    for( ; i <= n; i += lowbit(i) )
//        c[i] += k;
//}

//int getsum(int i){        //求t[1 ] 到 t[ i]的和
//    int res = 0;
//    for( ; i > 0; i -= lowbit(i) )
//        res += c[i];
//    return res;
//}

//单点更新、单点查询----传统数组可做

//单点更新、区域查询----上述普通树状数组可做

//区域更新、单点查询----用差分数组建立树状数组可做(原来要更新一个区间的值变成了只需要更新两个点, 查询的值就是前缀和)

//区域更新、区域查询----依旧利用差分数组建立树状数组
//A为原始数组，D为差分数组
//A[1]+A[2]+...+A[n]
//= (D[1]) + (D[1]+D[2]) + ... + (D[1]+D[2]+...+D[n]) 
//= n*D[1] + (n-1)*D[2] +... +D[n]
//=> ∑A[i] =  n *∑D[i] -  ∑( D[i]*(i-1) );      (均为i从1到n)
//维护两个树状数组: sum1[i] = D[i]，sum2[i] = D[i]*(i-1);