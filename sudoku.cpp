#include "iostream"
#include "algorithm"
#include "fstream"
#include "string"
#include "cstring"
#include "cmath"
#include "cstdio"
#include "cstdlib"
using namespace std;

ofstream print_sudoku("sudoku.txt");
int origin[10] = {1,2,3,4,5,6,7,9}; //为使得第一个数字为(2 + 5)%9 + 1 我们全排列不考虑8
int count_num = 0,data_count = 0;
char output_sudoku[500000000];//为了方便我们牺牲空间,节约时间,一次输出

int sudoku_map[10][9][9];
int tempt[9] = {1,2,3,4,5,6,7,8,9};

void change_map(char *rule) //进行变换
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
	char rule3[10][5] = {"147","174","417","471","714","741"}; //变换规则
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

int judge(int s,int x,int y,int num)
{//判断填充合法

	for (int i = 0; i < 9; i++)
	{    //当前行、列合法判断
		if (sudoku_map[s][x][i] == num)
			return 0;
		if (sudoku_map[s][i][y] == num)
			return 0;
	}
	int area_x = x - x % 3, area_y = y - y % 3;    //计算所处宫格左上角坐标
	for (int i = area_x; i < area_x+3; i++)    //当前宫格合法判断
		for (int j = area_y; j < area_y+3;j++)
			if (sudoku_map[s][i][j] == num)
				return 0;

	return 1;
}

int solve(int s,int a,int b)
{
	int init,next_a,next_b;
	init = sudoku_map[s][a][b];
	next_a = a + (b + 1) / 9;
	next_b = (b + 1) % 9;

	if(a == 9)
		return 1;
	if(sudoku_map[s][a][b] != 0)
	{
		if(solve(s,next_a,next_b))
			return 1;
	}
	else
	{
		for (int i = 0; i < 9; ++i)
		{
			int trynum = tempt[i];
			if(judge(s,a,b,trynum))
			{
				sudoku_map[s][a][b] = trynum;
				if(solve(s,next_a,next_b))
					return 1;
			}
		}
	}

	sudoku_map[s][a][b] = init;

	return 0;
}
int main(int argc, char const *argv[])
{
	int N = 0;
	//scanf("%d",&N);
	//FILE *fp1 = fopen(argv[2], "r");

	if (argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		int len = strlen(argv[2]);
		
		for (int i = 0; i < len; ++i)
		{
			if (argv[2][i] >= '0' && argv[2][i] <= '9')
			{
				N += ((argv[2][i] - '0')*pow((float)10, len - i - 1));
				//printf("%d",N);
			}
			else
			{
				printf("Error!\n");
				return 0;
			}
		}
			buildMove(N);
		print1();
	}
	else if(argc == 3 && strcmp(argv[1], "-s") == 0)
	{
		//printf("****\n");
		int i = 0,j = 0;
		freopen(argv[2],"r",stdin);
		printf("%s\n",argv[2]);
		freopen("sudoku.txt", "w", stdout);
		//printf("****\n");
		while(~scanf("%d",&sudoku_map[0][i][j]))
		{
			//printf("%d\n",sudoku_map[0][i][j]);
			i += (j + 1) / 9;
			j = (j + 1) % 9;
			if (i == 9)
			{		
				solve(0,0,0);

				i = j = 0;
				for (int i = 0; i < 9; ++i)
				{
					for (int j = 0; j < 9; ++j)
					{
						if(j == 8)
							putchar('\n');
						else
						{
							putchar(sudoku_map[0][i][j] + '0');
							putchar(' ');
						}
					}
				}
				putchar('\n');
			}
		}

		fclose(stdin);
		fclose(stdout);
		return 0;
	}
	return 0;
}


/*
8 0 0 0 0 0 0 0 1
9 0 0 0 2 0 0 0 3
0 3 0 0 5 0 0 7 0
0 0 5 0 0 0 4 0 0
0 0 4 5 0 9 6 0 0
0 0 0 8 0 1 0 0 0
0 0 0 0 0 0 0 0 0
0 4 6 0 0 0 8 2 0
0 2 0 3 0 5 0 9 0
*/

