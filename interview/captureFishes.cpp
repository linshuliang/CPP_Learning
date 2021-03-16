#include <stdio.h>
#include <iostream>
using namespace std;

//                           0  1   2   3   4   5   6   7   8   9   10  11  12
const int basicMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//                          0  1   2   3   4   5   6   7   8   9   10  11  12
const int leapMonth[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// 判断是否为闰年
bool isLeapYear(const int& year)
{
	if ((year % 100 != 0 && year % 4 == 0) || (year % 100 == 0) && (year % 400 == 0))
		return true;

	return false;
}

int passedDays(const int& year, const int& month, const int& day)
{
	int total = 0;

	// 过去年份天数累计
	// 年数 * 365
	total = (year - 1990) * 365;

	// 闰年的个数
	int leapYearNum = 0;
	for (int i = 1990; i < year; i++)
	{
		if (isLeapYear(i))
			leapYearNum++;
	}
	total += leapYearNum;

	// 当前年份月数累计
	int currentYearPassedDays = 0;
	for (int i = 1; i < month; i++)
	{
		currentYearPassedDays += basicMonth[i];
	}

	bool CurYearisLeap = isLeapYear(year);
	if (CurYearisLeap && month > 2)
	{
		currentYearPassedDays++;
	}

	total = total + currentYearPassedDays + day;
	return total;
}

bool isValidDay(const int& year, const int& month, const int& day)
{
	if (year < 1990)
		return false;

	if (month <= 0 || month > 12)
	{
		return false;
	}

	if (day <= 0)
		return false;

	if (isLeapYear(year))
	{
		if (day > leapMonth[month])
			return false;
	}
	else
	{
		if (day > basicMonth[month])
			return false;
	}
	return true;
}

int main()
{
	int year;
	int month;
	int day;
	while (true)
	{
		scanf("%4d-%2d-%2d", &year, &month, &day);

		if (isValidDay(year, month, day) == false)
		{
			std::cout << "Invalid input" << std::endl;
		}
		else 
		{
			int total = passedDays(year, month, day);
			if (total % 5 == 1 || total % 5 == 2 || total % 5 == 3)
				std::cout << "He is working" << std::endl;

			if (total % 5 == 0 || total % 5 == 4)
				std::cout << "He is having a rest" << std::endl;
		}
	}

	return 0;
}