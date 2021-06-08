#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

void dynamic_Lab1() {
	int num = 20;
	void* ptr = &num;

	printf("address of num: %p\n", ptr);

}

void generateRandom(int data[], int mod, int size) {
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		data[i] = rand() % mod;
	}
}

int getSum(int data[], int size) {
	int i;
	int sum = 0;
	for (i = 0; i < size; i++) {
		sum += data[i];
	}
	return sum;
}

void printArray(int data[], int size) {
	int i;

	for (i = 0; i < size; i++) {
		if ((i != 0) && !(i % 8)) {
			printf("\n");
		}
		printf("%6d", data[i]);
	}
	printf("\n");
}

void dynamic_Lab2() {
	int* p;
	int cnt;
	int sum;

	printf(" 입력할 정수의 개수는 ? ");
	scanf("%d", &cnt);

	p = (int*)malloc(sizeof(int) * cnt);
	if (p == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}

	generateRandom(p, 100, cnt);
	printArray(p, cnt);
	sum = getSum(p, cnt);

	printf("총합: %d\n", sum);
	
	if (p != NULL) {
		free(p);
	}
}

void exer2_dynamic() {
	int *p, *s;
	int i,j;

	printf("malloc() 함수 사용\n");


	p = (int*)malloc(sizeof(int) * 3);
	if (p == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}

	for (i = 0; i < 3; i++) {
		printf("할당된 곳의 초기값 p[%d] ==> %d\n", i, p[i]);
	}

	if (p != NULL) {
		free(p);
	}

	printf("\ncalloc() 함수 사용\n");

	s = (int*)calloc(sizeof(int), 3);
	if (s == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}

	for (j = 0; j < 3; j++) {
		printf("할당된 곳의 초기값 s[%d] ==> %d\n", j, s[j]);
	}

	if (s != NULL) {
		free(s);
	}

}

void exer3_dynamic() {
	int* p = NULL;
	int i, hap = 0;
	int cnt = 0;
	int data;


	p = (int*)realloc(p,sizeof(int) * 1);
	if (p == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}

	printf(" 1 번째 숫자 : ");
	scanf("%d", &p[0]);
	cnt++;


	for (i = 2; i< 12; i++) {
		printf(" %d 번째 숫자 : ", i);
		scanf("%d", &data);
		if (data != 0) {
			p = (int*)realloc(p, sizeof(int) * i);
		}
		else {
			break;
		}

		p[i - 1] = data;
		cnt++;
	}
	for (i = 0; i < cnt; i++) {
		hap = hap + p[i];
	}

	printf("입력 숫자 합 ==> %d\n", hap);

	if (p != NULL) {
		free(p);
	}
}
void dynamic_string1() {
	char greetings[3][20] = { {0x00,}, };
	int i;

	printf("[2차원 배열 이용]\n");
	for (i = 0; i < 3; i++) {
		printf("문장을 입력하세요:\n");
		gets(greetings[i]);
	}

	printf("\n입력된 문장은 다음과 같습니다.\n");
	for (i = 0; i < 3; i++) {
		printf("%s\n", greetings[i]);
	}
}

void dynamic_string2() {
	char buffer[32];
	char *greetings2[3] = { 0x00, };
	char** greetings3 = NULL;
	char temp;
	int len;
	int numOfStr;
	int i;

	printf("[동적 할당 이용1]\n");
	for (i = 0; i < 3; i++) {
		printf("문장을 입력하세요:\n");
		gets(buffer);
		len = strlen(buffer);
		greetings2[i] = (char*)calloc(len + 1, sizeof(char));
		strcpy(greetings2[i], buffer, len + 1);
	}

	printf("\n입력된 문장은 다음과 같습니다.\n");
	for (i = 0; i < 3; i++) {
		printf("%s\n", greetings2[i]);
	}

	for (i = 0; i < 3; i++) {
		free(greetings2[i]);
	}

	printf("[동적 할당 이용2]\n");
	printf("몇개의 문장을 입력할 건가요:\n");
	scanf("%d%c", &numOfStr, &temp);
	greetings3 = (char**)calloc(numOfStr, sizeof(char**));
	for (i = 0; i < 3; i++) {
		printf("문장을 입력하세요:\n");
		gets(buffer);
		len = strlen(buffer);
		greetings3[i] = (char*)calloc(len + 1, sizeof(char));
		strcpy(greetings3[i], buffer, len + 1);
	}

	printf("\n입력된 문장은 다음과 같습니다.\n");
	for (i = 0; i < numOfStr; i++) {
		printf("%s\n", greetings3[i]);
	}

	for (i = 0; i < numOfStr; i++) {
		free(greetings3[i]);
	}
	free(greetings3);

}

void dynamic_Lab3() {
	int row, col;
	int** matrix = NULL;
	int i, j;

	srand(time(NULL));

	printf("행과 열을 입력하시오.\n");
	scanf("%d%d", &row, &col);

	matrix = (int**)calloc(row, sizeof(int*));
	assert(matrix != NULL);

	for (i = 0; i < row; i++) {
		matrix[i] = (int*)calloc(col, sizeof(int));
		assert(matrix[i] != NULL);
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix[i][j] = rand() % 32;
		}
	}

	printf("[Matrix]\n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < row; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void inputMat(int* matrix[], int numRows, int numCols, int mod) {
	int i, j;

	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			matrix[i][j] = rand() % mod;
		}
	}
}

void printMat(int* matrix[], int numRows, int numCols) {
	int i, j;

	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void matrixAdd(int* addMat[], int* matA[], int* matB[], int numRows, int numCols) {
	int i, j;

	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			addMat[i][j] = matA[i][j] + matB[i][j];
		}
	}
}

void matrixMul(int* mulMat[], int* matA[], int* matB[], int numRows, int numCols) {
	int i, j,k;

	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			for (k = 0; k < numRows; k++) {
				mulMat[i][j] += (matA[i][k] * matB[k][j]);
			}
		}
	}
}

void dynamic_Lab3_1() {
	int row, col;
	int** matrixA = NULL, ** matrixB = NULL;
	int** addMat = NULL, ** mulMat = NULL;
	int i, j;

	srand(time(NULL));

	printf("행과 열을 입력하시오.\n");
	scanf("%d%d", &row, &col);

	matrixA = (int**)calloc(row, sizeof(int*));
	assert(matrixA != NULL);

	matrixB = (int**)calloc(row, sizeof(int*));
	assert(matrixB != NULL);

	addMat = (int**)calloc(row, sizeof(int*));
	assert(addMat != NULL);

	mulMat = (int**)calloc(row, sizeof(int*));
	assert(mulMat != NULL);

	for (i = 0; i < row; i++) {
		matrixA[i] = (int*)calloc(col, sizeof(int));
		assert(matrixA[i] != NULL);
		matrixB[i] = (int*)calloc(col, sizeof(int));
		assert(matrixB[i] != NULL);
		addMat[i] = (int*)calloc(col, sizeof(int));
		assert(addMat[i] != NULL);
		mulMat[i] = (int*)calloc(col, sizeof(int));
		assert(mulMat[i] != NULL);
	}

	inputMat(matrixA, row, col, 16);
	inputMat(matrixB, row, col, 16);

	printf("[Matrix A]\n");
	printMat(matrixA, row, col);

	printf("[Matrix B]\n");
	printMat(matrixB, row, col);

	matrixAdd(addMat, matrixA, matrixB, row, col);
	matrixMul(mulMat, matrixA, matrixB, row, col);

	printf("[Matrix addition]\n");
	printMat(addMat, row, col);

	printf("[Matrix multiplication]\n");
	printMat(mulMat, row, col);

	for (i = 0; i < row; i++) {
		free(matrixA[i]);
		free(matrixB[i]);
		free(addMat[i]);
		free(mulMat[i]);

	}
	free(matrixA);
	free(matrixB);
	free(addMat);
	free(mulMat);

}

int** allocMatrix(int row, int clo) {
	int** matrix = NULL;
	int i;

	matrix = (int**)calloc(row, sizeof(int*));
	assert(matrix != NULL);
	for (i = 0; i < row; i++) {
		matrix[i] = (int*)calloc(clo, sizeof(int));
		assert(matrix[i] != NULL);
	}
	return matrix;
}

void freeMatrix(int** matrix, int row) {
	int i;

	for (i = 0; i < row; i++) {
		free(matrix[i]);

	}
	free(matrix);
}

void dynamic_Lab3_2() {
	int row, col;
	int** matrixA = NULL, ** matrixB = NULL;
	int** addMat = NULL, ** mulMat = NULL;
	int i, j;

	srand(time(NULL));

	printf("행과 열을 입력하시오.\n");
	scanf("%d%d", &row, &col);

	matrixA = allocMatrix(row, col);
	matrixB = allocMatrix(row, col);
	addMat = allocMatrix(row, col);
	mulMat = allocMatrix(row, col);

	inputMat(matrixA, row, col, 16);
	inputMat(matrixB, row, col, 16);

	printf("[Matrix A]\n");
	printMat(matrixA, row, col);

	printf("[Matrix B]\n");
	printMat(matrixB, row, col);

	matrixAdd(addMat, matrixA, matrixB, row, col);
	matrixMul(mulMat, matrixA, matrixB, row, col);

	printf("[Matrix addition]\n");
	printMat(addMat, row, col);

	printf("[Matrix multiplication]\n");
	printMat(mulMat, row, col);

	freeMatrix(matrixA, row);
	freeMatrix(matrixB, row);
	freeMatrix(addMat, row);
	freeMatrix(mulMat, row);

}

typedef struct _STUDENT_ {
	char name[32];
	char major[32];
	int age;
}STUDENT;

void inputStudent(STUDENT stu[], int size) {
	char buf;
	int i;

	printf("[Input Student]\n");
	for (i = 0; i < size; i++) {
		printf("\n* %d student\n", i + 1);
		printf("Name:\n");
		fgets(stu[i].name, 32, stdin);

		printf("Major:\n");
		fgets(stu[i].major, 32, stdin);

		printf("Age:\n");
		scanf("%d%c", &((stu + i)->age), &buf);
	}
}

void printStudent(STUDENT stu[], int size) {
	int i;

	for (i = 0; i < size; i++) {
		printf("\n* %d student\n", i + 1);
		printf("Name: %s\n", (stu + i)->name);
		printf("Major: %s\n", (*(stu + i)).major);
		printf("Age: %d\n", stu[i].age);
	}
}
void dynamic_Lab4() {
	int i = 0x00;
	int limit = 0x00;
	char buf = 0x00;
	STUDENT* stuList = NULL;

	printf("[Input the number of students]\n");
	scanf("%d%c", &limit, &buf);

	stuList = (STUDENT*)calloc(limit, sizeof(STUDENT));
	assert(stuList != NULL);

	inputStudent(stuList, limit);
	printStudent(stuList, limit);

	if (stuList != NULL) {
		free(stuList);
	}
}

int main() {
	//dynamic_Lab1();
	//dynamic_Lab2();
	//exer2_dynamic();
	//exer3_dynamic();
	//dynamic_string1();
	//dynamic_string2();
	//dynamic_Lab3();
	//dynamic_Lab3_1();
	//dynamic_Lab3_2();
	dynamic_Lab4();

	getchar();
	return 0;
}