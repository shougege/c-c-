#include<stdio.h>


/*

系统时间的显示
 好的办法是 在时间显示器中以静态变量分别存储小时，分钟，秒只有在其内容
 发生变化的时候才更新其显示 
*/
extern void DisplayTime(...)
{
	static BYTE byHour,byMinute,bySecond;// 声明一次，有值变化才修改 
	BYTE byNewHour,byNewMinute,byNewSecond;
	byNewHour = GetSysHour();
	byNewMinute = GetSysMinute();
	byNewSecond = GetSysSecond();
	
	if(byNewHour != byHour)
	{
		/*显示小时 */
		byHour = byNewHour; 
	}
	if(byNewMinute != byMinute)
	{
		/*显示分钟 */
		byMinute = byNewMinute;
	}
	if(byNewSecond != bySecond)
	{
		/* 显示秒钟 */
		bysecond = byNewSecond;
	}
 } 
int main()
{
	
		
	return 0;
} 
