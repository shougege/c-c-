#include<stdio.h>


/*

ϵͳʱ�����ʾ
 �õİ취�� ��ʱ����ʾ�����Ծ�̬�����ֱ�洢Сʱ�����ӣ���ֻ����������
 �����仯��ʱ��Ÿ�������ʾ 
*/
extern void DisplayTime(...)
{
	static BYTE byHour,byMinute,bySecond;// ����һ�Σ���ֵ�仯���޸� 
	BYTE byNewHour,byNewMinute,byNewSecond;
	byNewHour = GetSysHour();
	byNewMinute = GetSysMinute();
	byNewSecond = GetSysSecond();
	
	if(byNewHour != byHour)
	{
		/*��ʾСʱ */
		byHour = byNewHour; 
	}
	if(byNewMinute != byMinute)
	{
		/*��ʾ���� */
		byMinute = byNewMinute;
	}
	if(byNewSecond != bySecond)
	{
		/* ��ʾ���� */
		bysecond = byNewSecond;
	}
 } 
int main()
{
	
		
	return 0;
} 
