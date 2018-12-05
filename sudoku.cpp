#include "iostream"
#include "algorithm"
#include "fstream"
#include "string"
using namespace std;

ofstream print_sudoku("sudoku.txt");
int origin[10] = {1,2,3,4,5,6,7,9}; 
int count_num = 0,data_count = 0;
char output_sudoku[500000000];
void change_map(char *rule)
{
	for (int i = 0; i < 3; ++i)
	{
		output_sudoku[data_count++] = origin[(8 + rule[i] - '0') %9] + '0';
		for (int j = 1; j < 17; ++j)
		{
			output_sudoku[data_count++] = ' ';
			j++;
			output_sudoku[data_count++] = origin[((16 -j)/2 + rule[i] - '0') % 9] + '0';
		}
		output_sudoku[data_count++] = '\n';
	}
}

void BuildSudoku(char *rule1,char *rule2, char*rule3)
{
	change_map(rule1);
	change_map(rule2);
	change_map(rule3);
	output_sudoku[data_count++] = '\n';
}

void buildMove(int N)
{
	char rule1[10][5] = {"036","063"};
	char rule2[10][5] = {"258","285","528","582","825","852"};
	char rule3[10][5] = {"147","174","417","471","714","741"};
	while(1)
	{
		if(next_permutation(origin,origin + 8))
		{
			origin[8] = 8;
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 6; ++j)
				{
					for (int t = 0; t < 6; ++t)
					{
						BuildSudoku(rule1[i],rule2[j],rule3[t]);
						count_num++;
						if(count_num == N)
							return;
					}
				}
			}
		}
		else
			break;
		
	}
} 
void print1()
{
	print_sudoku << output_sudoku;
}
int main(int argc, char const *argv[])
{
	int N,i;
	scanf("%d",&N);
	if (N > 0)
	{
		buildMove(N);
		print1();
	}
	else
	{
		printf("hhhhh\n");
	}
	return 0;
}
