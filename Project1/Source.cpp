#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
	char pBuffer[4096];
	FILE* pFile = fopen("C:/dev/1.txt", "r");

	if (pFile == NULL) 
	{
		printf("Cannot open file\n");
		return -1;
	}
	int readed = fread(pBuffer, 1, 4096, pFile);
	//if  feof(pFile)
	pBuffer[readed] = 0;
	fclose(pFile);
	printf("Content: %s", pBuffer);


	pFile = fopen("C:/dev/2.txt", "w");

	if (pFile == NULL)
	{
		printf("Cannot open file\n");
		return -1;
	}

	struct MyStruct
	{
		double x;
		double y;
	};
	MyStruct S;
	S.x = 5;
	S.y = 6;
	//fprintf(pFile, "%s", pBuffer);
	//fwrite(pBuffer, 1, readed, pFile);
	fwrite(&S, sizeof(MyStruct), 1, pFile);
	fclose(pFile);

	MyStruct R;

	pFile = fopen("C:/dev/2.txt", "r");
	fread(&R, sizeof(MyStruct), 1, pFile);
	fclose(pFile);
	return 0;
}