#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <map>

/*class A
{
public:
	class Iterator
	{
		double value;
	public:
		operator double* ()
		{
			return &value;
		}
	};
	double* pBuffer;
	Iterator begin;
	Iterator end;
};*/


//1.������� ����.
//2.��������� �� ������������� ������� ����� � ������� � ���
//3.������� ��� � ����.
// COM ���������� API

	/*A a;
	A::Iterator it1 = a.begin;
	*it1 = 5;*/

void SaveWord() 
{

}



int main()
{

	typedef std::map <std::string, int> WordMap;
	WordMap wordMap;
	WordMap::iterator it;
	std::string currentWord;
	currentWord = "";
	char pBuffer[750000];
	FILE* pFile = fopen("C:/dev/Books/1.txt", "r");

	if (pFile == NULL) 
	{
		printf("Cannot open file\n");
		return -1;
	}
	int readed = fread(pBuffer, 1, 750000, pFile);

	int i = 0;

/*-------------------------------------------------------------------------------------------------------
������ ����������.
---------------------------------------------------------------------------------------------------------

	while (true)
	{
		
		if(i == readed) // ���� ����� �� ����� �������, ��������� ����� �����
		{
			if (feof(pFile)) // ���� �� � ����� ����� � ��� �� ������� �������
			{

				fclose(pFile);
				break;
			}
		int readed = fread(pBuffer, 1, 4096, pFile);
		i = 0;

		if (!isalpha(pBuffer[i])) 
		{
			WordMap::iterator it = wordMap.find(currentWord);//�������� ����� �������� �� ����� �������, �� ��� ���� � �����������?

			if (it == wordMap.end())
			{
				wordMap.insert(std::make_pair(currentWord, 1));
				currentWord = "";// ��� ���������� ���� ������� ����� ����� � �����("")?
			}
			else
			{
				it->second++;
			}
		}
	    }

		for (int k = 0;k != 1000;k++)
		{
		}

		if (isalpha(pBuffer[i])) // ����� ������ ��������
		{
			currentWord = currentWord + pBuffer[i];
		}

		for (int k = 0; k != 1000; k++)
		{
		}

		if (isalpha(pBuffer[i]) && !isalpha(pBuffer[i + 1])) // ����������� ����� �����, ��� ����� ��� ������� ��������� �� ������� �������?
		{
			
			WordMap::iterator it = wordMap.find(currentWord);
			
			if (it == wordMap.end()) 
			{
				wordMap.insert(std::make_pair(currentWord, 1));
				currentWord = "";
			}
			else
			{
				it->second++;
			}
		}

		for (int k = 0; k != 1000; k++)
		{
		}

		i++;
	}

	1 & 1 = 1
	1 & 0 = 0
	0 & 1 = 0
	0 & 0 = 0
--------------------------------------------------------------------------------------------------------------
	*/

	bool end = false;

	while (!end) 
	{
		
		if (isalpha(127 & pBuffer[i]))
		{
			pBuffer[i] = (char)tolower(pBuffer[i]);
		   currentWord = currentWord + pBuffer[i];
		}

		
		else if (currentWord != "")
		{
			it = wordMap.find(currentWord);

			if (it == wordMap.end())
			{
				wordMap.insert(std::make_pair(currentWord, 1));
				
			}
			else 
			{
				it->second++;

			}
			currentWord = "";
		}

		if (i + 1 >= readed) // ���� ����� �� ����� �������, ��������� ����� �����
		{
			if (feof(pFile)) // ���� �� � ����� ����� � ��� �� ������� �������
			{
				fclose(pFile);
				end = true;
			}
			else
			{
				readed = fread(pBuffer, 1, 750000, pFile);
				i = -1;
			}
		}
		
		
		i++;
	}


	pFile = fopen("C:/dev/Books/Output.txt", "w");

	for (it = wordMap.begin(); it != wordMap.end(); it++)
	{
		fprintf(pFile, "%s - %d\n", it->first.c_str(), it->second);
	}

	fclose(pFile);
	//������������� �� ���������� (Boost Bimap)
	//������ ������ (Done!)
	//��������� ��� � ������ ������� (Done!)
	//test without debug (Done!)
	//increase Buffer size to 16Kb (Done!)
	//increase Buffer size to 750Kb (Done!)
	//no significant speed changes!!!


	/*pFile = fopen("C:/dev/Books/Output_Value.txt", "w");


	for (it = wordMap.begin(); it != wordMap.end(); it++)
	{
		fprintf(pFile, "%s - %d\n", it->first.c_str(), it->second);
	}
	*/
		//if  feof(pFile)

		//fclose(pFile);
		//printf("Content: %s", pBuffer);


		/*pFile = fopen("C:/dev/2.txt", "w");

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
		fclose(pFile);*/
		return 0;
}