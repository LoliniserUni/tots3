#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void getInfo(char**,int*,int*,int*);
void setNullVals(char**, int*, int*, int*);
void getYearGroupData(char**, int*, int*, int*);
void sortByMarks(char**, int*, int*, int*);
void sortByYears(char**, int*, int*, int*);

const int STRING_LEN = 16;
int main(int argc, char** argv)
{
	
	printf("How many stdudents would you like to record?\n");
	int amt;
	scanf_s("%d",&amt);

	char** names = new char*[amt];
	for (int k = 0; k < amt; k++)
	{
		names[k] = new char[STRING_LEN];
	}

	int* years = new int[amt];
	int* marks = new int[amt];

	setNullVals(names, years, marks, &amt);
	getInfo(names, years, marks,&amt);
	getYearGroupData(names, years, marks, &amt);

	int choice = 0;

	printf("Enter 1 to sort by years, Enter 2 to sort by marks.\n");
	scanf_s("%d",&choice);

	if (choice == 1) 
	{
		sortByYears(names, years, marks, &amt);
	}
	else if (choice == 2) 
	{
		sortByMarks(names, years, marks, &amt);
	}

	for (int k = 0; k < amt; k++)
	{
		delete [] names[k];
	}
	delete [] names;
	delete [] years;
	delete [] marks;
}

void setNullVals(char** names, int* year, int* marks, int* amt)
{
	for (int k = 0; k < *amt; k++)
	{
		marks[k] = 0;
		year[k] = 0;
	}
}

/*
Get student info from console line.
*/
void getInfo(char** names,int* year,int* marks, int* amt)
{
	for (int k = 0; k < *amt; k++)
	{
		printf("\nEnter stduents number %d's year group. Enter -1 to end\n", k + 1);
		int temp;
		scanf_s("%d", &temp);
		if (temp < 0) 
		{
			*amt = k;
			break;
		}
		else 
		{
			year[k] = temp;
		}

		printf("\nEnter stduents number %d's name\n",k+1);
		scanf_s("%s",names[k],STRING_LEN);

		printf("\nEnter stduents number %d's mark\n", k + 1);
		scanf_s("%d", &marks[k]);
	}
}

/*
Get data for a year grou[.
*/
void getYearGroupData(char** names, int* year, int* marks, int* amt)
{
	int startYear = year[0];
	int endYear = year[0];

	for (int k = 0; k < *amt; k++) {
		if (year[k] < startYear)
		{
			startYear = year[k];
		}
		if (year[k] > endYear) {
			endYear = year[k];
		}
	}

	for (int x = startYear; x <= endYear; x++)
	{
		int totalMarks = 0;
		int fails = 0;
		int pass = 0;
		int totalStudents = 0;

		for (int k = 0; k < *amt; k++) {
			if (year[k] == x) {
				totalMarks += marks[k];
				totalStudents++;

				if (marks[k] < 40) 
				{
					fails++;
				}
				else
				{
					pass++;
				}
			}
			//printf("%d", k);
		}

		bool skip = (totalStudents == 0);

		if (!skip) 
		{
			int av = totalMarks / totalStudents;

			printf("For the year group %d, the average mark was %d.\n%d students passed.\n%d students failed.", x, av, pass, fails);
		}
		
	}
}

void sortByYears(char** names, int* year, int* marks, int* amt)
{
	for (int k = 0; k < *amt-1; k++) 
	{
		int pos = k;
		for (int x = k; k < *amt; x++)
		{
			if (year[pos] > year[x])
			{
				pos = x;
			}
		}

		int tYear = year[pos];
		int tMarks = marks[pos];
		char* tName = names[pos];

		year[k] = year[pos];
		marks[k] = marks[pos];
		names[k] = names[pos];

		year[pos] = tYear;
		marks[pos] = tMarks;
		names[pos] = tName;
	}
}

void sortByMarks(char** names, int* year, int* marks, int* amt)
{
	for (int k = 0; k < *amt - 1; k++)
	{
		int pos = k;
		for (int x = k; k < *amt; x++)
		{
			if (marks[pos] > marks[x])
			{
				pos = x;
			}
		}

		int tYear = year[pos];
		int tMarks = marks[pos];
		char* tName = names[pos];

		year[k] = year[pos];
		marks[k] = marks[pos];
		names[k] = names[pos];

		year[pos] = tYear;
		marks[pos] = tMarks;
		names[pos] = tName;
	}
}