#define  _CRT_SECURE_NO_WARNINGS

#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

#include <boost/optional.hpp>
#include <boost/none.hpp>
#include <boost/foreach.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap.hpp>
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


//1.Считать файл.
//2.Вычленить из произвольного буффера слово и занести в МАп
//3.Вывести Мап в файл.
// COM технология API

	/*A a;
	A::Iterator it1 = a.begin;
	*it1 = 5;*/

int main()
{
	typedef boost::bimap < std::string, boost::bimaps::multiset_of<int>> bm_type;
	bm_type biWordMap;
	typedef bm_type::value_type uniqueWord;
	

	//bm_type::const_iterator biIter;
	bm_type::left_const_iterator biLeftIter;
	bm_type::right_const_iterator biRightIter;
	bm_type::const_iterator biIter;


	//typedef std::map <std::string, int> WordMap;
	//WordMap wordMap;
	//WordMap::iterator it;
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
Первое исполнение.
---------------------------------------------------------------------------------------------------------


	1 & 1 = 1
	1 & 0 = 0
	0 & 1 = 0
	0 & 0 = 0


	typedef boost::bimap < int, std::string > bm_type;
	bm_type biWordMap;
	bm_type::const_iterator biIter;

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
			biLeftIter = biWordMap.left.find(currentWord);

			if (biLeftIter == biWordMap.left.end())
			{
				biWordMap.insert(uniqueWord(currentWord, 1));
				//(std::make_pair(currentWord, 1));
				int a = biWordMap.size();
								
			}
			else 
			{
		        biWordMap.left.equal_range(1);			
				biLeftIter->second;
			}
			currentWord = "";
		}


		//if (it == wordMap.end())

		//{

		//	wordMap.insert(std::make_pair(currentWord, 1));

		//	currentWord = "";
		//}


		if (i + 1 >= readed) // если дошли до конца буффера, считываем новый кусок
		{
			if (feof(pFile)) // если мы в конце файла и все из буффера считано
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

	pFile = fopen("C:/dev/Books/BiOutput.txt", "w");

	for (biLeftIter = biWordMap.left.begin(); biLeftIter != biWordMap.left.end(); biLeftIter++)
	{
		fprintf(pFile, "%s - %d\n", biLeftIter->first.c_str(), biLeftIter->second);
	}

	fclose(pFile);
	//отсортировать по количеству (Boost Bimap)
	//убрать пустые (Done!)
	//перевести все в нижний регистр (Done!)
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