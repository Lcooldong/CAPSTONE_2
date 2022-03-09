#pragma warning(disable:4996)

#define STUDENT_NUMBER 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

// 1. ����ü�� ����
// 2. ���� ���� ����
// 3. �߰� ���� ���

typedef struct _student {
	int studentID;	//20161110061	11��
	char name[20];
	double score;
}Student, *pStudent;

char* GetNextString(char* data, char separator, char* target)
{
	while (*data && (*data != separator))	// NULL �Ǵ� �����ڱ���
	{
		*target++ = *data++;	// ���ڸ� ��� �Ѱ��� �ֱ� char
		
	}

	// ���ڿ� ���� NULL�� �ٲ���
	if (*(target - 1) == '\n') *(target - 1) = 0;
	else *target = 0;

	if (*data == separator) data++; // ���ڰ� �������϶� ���� ĭ����
	
	return data;	// ���κ�
}	//strtok ������ ����


void selectBubbleSort(pStudent p, int target)
{
	bool flag = true;

	for (int i = 0; i < STUDENT_NUMBER; i++)	// ��ü ����
	{
		flag = false;
		for (int j = 0; j < STUDENT_NUMBER - i - 1; j++)	// �� Ƚ��
		{
			switch (target)
			{
			case 1:
				if (p[j].studentID > p[j + 1].studentID)	// ��������
				{
					Student tmp;
					tmp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = tmp;
					flag = true;
				}
				break;

			case 2:
				if (strcmp(p[j].name, p[j + 1].name) > 0)	// ������ �ڷ� ������ ŭ(1������->�ڿ� ���� ŭ)-> ��������
				{
					Student tmp;
					tmp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = tmp;
					flag = true;
				}
				break;

			case 3:
				if (p[j].score < p[j + 1].score)	// ��������
				{
					Student tmp;
					tmp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = tmp;
					flag = true;
				}
				break;

			default:
				break;
			}
		}
		if (flag == false) break;
	}
}


// �䱸���� : ����(double), �й�(int), �̸�(char*)�� ���� ����
void sortData(pStudent p)
{	
	//char* target = (char*)malloc(sizeof(char*) *10);
	//scanf_s("%s", target, sizeof(target));
	//printf("���� ��� : %s\n", target);
	//free(target);

	int target = 0;
	bool flag = true;

	printf("������ ������ ���ڸ� �����ϼ���.\n==================\n");
	printf("�й� -> 1\n�̸� -> 2\n���� -> 3\n");
	printf("==================\n");
	printf("�Է� : ");
	scanf_s("%d", &target);
	printf("���� ���� -> ");
	
	switch (target)
	{
	case 1:
		printf("�й�\n");
		printf("------------------\n");
		selectBubbleSort(p, target);
		break;
	case 2:
		printf("�̸�\n");
		printf("------------------\n");
		selectBubbleSort(p, target);
		break;
	case 3:
		printf("����\n");
		printf("------------------\n");
		selectBubbleSort(p, target);
		break;
	default:
		printf("�߸��Է��ϼ̽��ϴ�.\n");
		break;
	}
	system("cls");
}


void swapStruct(pStudent p1, pStudent p2)
{
	Student tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void printStruct(pStudent p)
{
	for (int i = 0; i < STUDENT_NUMBER; i++)
	{
		printf("%2d=%3s=%.1f\n", p[i].studentID, p[i].name, p[i].score);
	}
}

void saveText(FILE* filename, pStudent p)
{
	for (int i = 0; i < STUDENT_NUMBER; i++)
	{
		fprintf(filename, "%2d-%3s-%.1f\n", p[i].studentID, p[i].name, p[i].score);
	}
}

int main()
{	

	Student polyStudent[STUDENT_NUMBER];
	//pStudent poly = polyStudent;
	char* strData[3];
	int count = 0;

	//printf("%p %p\n", polyStudent, poly);

	FILE* p_file = NULL;
	FILE* save_file = NULL;

	if (0 == fopen_s(&p_file, "StudentData.csv", "rt")) {
	
		char one_line_string[128], str[32], * p_pos;
		const char* p_title_format_table[3] = {" %s", " %s", "  %s\n"};	// 0,1,2 ���伳��
		const char* p_data_format_table[3]  = {"  %s", "  %3s", " %3s\n" };
		int len = strlen(str) + 1;

		for (int i = 0; i < 3; i++)
		{
			strData[i] = (char*)malloc(sizeof(char) * len);
		}


		if (NULL != fgets(one_line_string, 128, p_file)) {
			p_pos = one_line_string;
			//printf(p_pos);
			for (int i = 0; *p_pos; i++)	// NULL ���� ������
			{
				p_pos = GetNextString(p_pos, ',', str);
				printf(p_title_format_table[i], str);
			}
			
		}

		printf("=================\n");
		while (NULL != fgets(one_line_string, 128, p_file)) { //��ü 3����
			p_pos = one_line_string;	// ���پ� ��Ÿ��(���ڿ�)	, �ʱ���ġ

			for (int i = 0; *p_pos; i++)	// ������ ���ڰ� NULL���� ���ư�
			{
				p_pos = GetNextString(p_pos, ',', str);	// ��ġ �ּ� ��ȯ
				strcpy(strData[i], str);
				//printf(p_data_format_table[i], str);
			}
			// ������ ������ �����س��� �� ����
			polyStudent[count].studentID = atoi(strData[0]);
			strcpy(polyStudent[count].name, strData[1]);
			polyStudent[count].score = atof(strData[2]);
		
			count++;
			//printf("==========================\n");
			//printf("%s-%s-%s\n", strData[0], strData[1], strData[2] );
			

		}

		for (int i = 0; i < 3; i++)
		{
			free(strData[i]);
		}

		fclose(p_file);
	}
	

	//swapStruct(&polyStudent[0], &polyStudent[1]);
	printStruct(&polyStudent);
	//printf("��%d\n", strcmp("��", "��"));
	printf("=================\n");
	//system("cls");
	sortData(&polyStudent);
	printStruct(&polyStudent);
	printf("=================\n");
	printf("�����͸� �����Ͻðڽ��ϱ�? (Y/N) : ");
	char comfirmButton;
	getchar();	// ���� ����
	scanf_s("%c", &comfirmButton, sizeof(comfirmButton));
	if ((comfirmButton == 'Y') || (comfirmButton == 'y')) {
		save_file = fopen("log.txt", "w");
		saveText(save_file, &polyStudent);
		printf("[����]\n");
		fclose(save_file);
	}
	else if ((comfirmButton == 'N') || (comfirmButton == 'n')) {
		printf("[���]\n");
	}

	return 0;
}