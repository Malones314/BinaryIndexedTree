#include<iostream>
#include<vector>
#include<time.h>
using namespace std;
const int testSize = 10 ;	
const int number = testSize + 1;
int lowBit ( int );
void singleUpdate ( int, int, vector<int>& );
void singleUpdate ( int, int, vector<int>&, vector<int>& );
void zoonUpdate ( int, int, int, vector<int>& );
void zoonUpdate ( int, int, int, vector<int>&, vector<int>& );
int getSum ( int, vector<int>& );
int getSum ( int, vector<int>&, vector<int>& );
void showVector ( vector<int>&, vector<int>&, vector<int>&, vector<int>&, vector<int>& );
int main ( ) {
	vector<int>a ( number, 0 );			//原始数组
	vector<int>c ( number, 0 );			//树状数组 ( 单点更新、区域查询 )
	vector<int>cd ( number, 0 );			//原始数组对应的差分数组的树状数组 ( 区域更新、单点查询 ) 
	vector<int>sum1 ( number, 0 );		//树状数组1 ( 区域更新、区域查询 )sum1[i] = d[i]
	vector<int>sum2 ( number, 0 );		//树状数组2 ( 区域更新、区域查询 )sum2[i] = d[i]*(i-1);

	int i = 0;
	srand ( time ( 0 ) );
	for ( i = 1; i < number; i++ ) {
		a [i] = rand ( ) % 100;
		//普通树状数组更新
		singleUpdate ( i, a [i], c );	
		//差分数组的树状数组更新
		singleUpdate ( i, a [i] - a [i - 1], cd );
		//sum1，sum2更新
		singleUpdate ( i, a [i] - a [i - 1], sum1, sum2 );
	}

	/*------------------------------------------------------------------------------*/
	showVector ( a, c, cd, sum1, sum2 );
	/*------------------------------------------------------------------------------*/

	cout << "查询a[1]到a[index]的和，输入index：" << endl;
	int index = -1;
	cin >> index;
	cout << getSum ( index, c ) << endl;
	cout << "输入需要更新的数据的值 : " << endl;
	int upData = -1;
	cin >> upData;
	cout << "输入需要更新的起始和结束区间 : " << endl;
	int indexBegin = -1, indexEnd = -1;
	cin >> indexBegin >> indexEnd;
	zoonUpdate ( indexBegin, indexEnd, upData, cd );
	zoonUpdate ( indexBegin, indexEnd, upData, sum1, sum2 );

	cout << "查询a[index]的值，输入index：" << endl;
	cin >> index;
	cout << getSum ( index, cd ) << endl;
	cout << "查询a[indexBegin]到a[indexEnd]的和，输入indexBegin和indexEnd：" << endl;
	cin >> indexBegin >> indexEnd;
	cout << getSum ( indexEnd, sum1, sum2 ) - getSum ( indexBegin, sum1, sum2 ) << endl;
	return 0;
}

int lowBit ( int x ) {
	return ( x & ( -x ) );
}

void singleUpdate ( int index, int upNumber, vector<int>& ivector ) {
	for ( ; index < ivector.size ( ) + 1; index += lowBit ( index ) )
		ivector [index] += upNumber;
}
void singleUpdate ( int index, int upNumber, vector<int>& ivector1, vector<int>& ivector2  ) {
	int x = index;
	for ( ; index < ivector1.size ( ) + 1; index += lowBit ( index ) ) {
		ivector1 [index] += upNumber;
		ivector2 [index] += upNumber * ( x - 1 );
	}
}

void zoonUpdate ( int indexBegin, int indexEnd, int upNumber, vector<int>& ivector ) {
	//对于差分数组只需要更新两个值
	singleUpdate ( indexBegin, upNumber, ivector );
	singleUpdate ( indexEnd + 1, -upNumber, ivector );
}
void zoonUpdate ( int indexBegin, int indexEnd, int upNumber, vector<int>& ivector1, vector<int>& ivector2 ) {
	singleUpdate ( indexBegin, upNumber, ivector1, ivector2 );
	singleUpdate ( indexEnd + 1, -upNumber, ivector1, ivector2 );
}

int getSum ( int index, vector<int>& ivector ) {
	int sum = 0;
	for ( ; index > 0; index -= lowBit ( index ) )
		sum += ivector [index];
	return sum;
}
int getSum ( int index, vector<int>& ivector1, vector<int>& ivector2 ) {
	int sum = 0; 
	int x = index;
	for ( ; index > 0; index -= lowBit ( index ) )
		sum += x * ivector1 [index] - ivector2 [index];
	return sum;
}
void showVector ( vector<int>& a, vector<int>& c, vector<int>& cd, vector<int>& sum1, vector<int>& sum2 ) {
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "打印a：" << endl;
	for ( auto k : a )
		cout << k << " ";
	cout << endl;
	cout << "打印c：" << endl;
	for ( auto k : c )
		cout << k << " ";
	cout << endl;
	cout << "打印cd：" << endl;
	for ( auto k : cd )
		cout << k << " ";
	cout << endl;
	cout << "打印sum1：" << endl;
	for ( auto k : sum1 )
		cout << k << " ";
	cout << endl;
	cout << "打印sum2：" << endl;
	for ( auto k : sum2 )
		cout << k << " ";
	cout << endl;
	cout << "------------------------------------------------------------------------------" << endl;
}
