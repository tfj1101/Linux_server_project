//#include<time.h>
//#include<stdio.h>
//int main()
//{
//	int m_y, m_m, m_d;
//	printf("请输入你的生日：（例如：1999，8，10）\n");
//	scanf("%d,%d,%d", &m_y, &m_m, &m_d);
//	int year = 2024;
//	int mouth = 6;
//	int day = 18;
//	int sum;
//	if (mouth>m_m)
//	{
//		if (day>m_d)
//		{
//			sum = (year - m_y) * 365 + (mouth - m_m)*31 + (day - m_d);
//		}
//		else
//		{
//			sum = (year - m_y) * 365 + (mouth-1 - m_m)*31 + (day+31 - m_d);
//		}
//
//	}
//	else
//	{
//		if (day > m_d)
//		{
//			sum = (year - m_y) * 365 + (mouth - m_m) * 31 + (day - m_d);
//		}
//		else
//		{
//			sum = (year-1 - m_y) * 365 + (mouth+11 - m_m) * 31 + (day + 31 - m_d);
//		}
//	}
//
//	printf("你已经活了 %d 天。\n", sum);
//	return 0;
//	
//
//}