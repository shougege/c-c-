#include<stdio.h>

/*
	__VA_ARGS__是一个可变参数的宏，
	实现思想就是宏定义中参数列表的最后一个参数为省略号（也就是三个点）。
	这样预定义宏__VA_ARGS__ 就可以被用于替换部分中，替换省略号所代表的字符串

	#define  PR(...) printf(__VA_ARGS__)
	int main()
	{
		int wt =1, sp =2;
		PR("hello\n");
		PR("weight = %d, shipping = %d", wt,sp);
		return 0;
		
	}
*/
/*
	##__VA_ARGS__宏前面加上##的作用在于，当可变参数的个数为0时，这里的##起到
    把前面多余的","去掉的作用，否则会编译错误
*/
/* 获取变长参数宏的参数个数,支持0-10个变长参数*/
//* #define HI_VA_NARGS_IMPL(a, b, c, d, N, ...) __VA_ARGS__

/*
#define HI_VA_NARGS_IMPL(a, b, c, d, N, ...) b
#define HI_VA_NARGS(...) HI_VA_NARGS_IMPL(_, ##__VA_ARGS__,1,20,3,40,5,6,7)
	 
int main()
{ 
	printf("%d",HI_VA_NARGS_IMPL(1,2,3,4,50,60,7,8));
	// =50      注释* 为参数固定为6， 因为 ... 替换为 __VA_ARGS__
		// 非注释的 参数至少为6个， 后面的参数给 ...
	printf("\n %d",HI_VA_NARGS());	
	// __VA_ARGS__ 替换...和之后的参数
	// ## 如果参数个数是0 就前面多余”,“   这个时候HI_VA_NARGS_IMPL 后面的复制只能是b
	//    不能是a。 HI_VA_NARGS() 替换为HI_VA_NARGS_IMPL（1,20,3,40）因为__VA_ARGS__为空,但是占一个参数个数
	return 0;
}
*/
/* 获取变长参数宏的参数个数,支持0-10个变长参数*/
/******************************************************/

/*
	这里用_0, _1这个的变量 而不能用0  1 2 3这样的常量。
*/
#define HI_VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define HI_VA_NARGS(...) HI_VA_NARGS_IMPL(_, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

int main()
{
	printf("\n %d",HI_VA_NARGS(100,100,100,1,1,1,11,11,11,11,111,11,));
	return 0;
}
/*
	分析
	1. 当参数个数为空时，HI_VA_NARGS_IMPL 传递了12个参数 N 刚好是第12 个 ... 为用到
	2. 当参数只有一个时 HI_VA_NARGS_IMPL 传递也是12个参数，但是N刚好是1
	3. 当参数个数大于1且小于10 HI_VA_NARGS_IMPL 传递的参数就会向后移动位数
	4. 当参数个数个数大于10时, 就输出第十一个参数的 数值。
*/

补充: 
	 ##运算符可以用于类函数宏的替换部分。另外，##还可以用于类对象宏的替换部分。
	 这个运算符把两个语言符号组合成当个语言符号。
	 #define XNAME(n) x##n
	 XNAME(4)
	 展开后: x4


