#include <malloc.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#define NULL 0




template< typename T> class List
{
private:
	struct Atom
	{
		T value;
		Atom* pNext;
	};

	Atom *m_pRoot;
	Atom *m_pLast;  
	int   m_Size;

public:
	List()
	{
		m_pRoot = NULL;
		m_pLast = m_pRoot;  
		m_Size = 0;
	}
	int Size() 
	{
		return m_Size;
	}

	void Add(T value)
	{
		m_Size++;      //  !!
		Atom *pTemp; //Создали указатель(локальный, исчезнет после выхода из функции))
		pTemp = (Atom*)malloc(sizeof(Atom));// Дать память командой malloc
		pTemp->value = value;//Записали на выданном участке памяти значение value
		pTemp->pNext = NULL;//Записали что этот элемент последний

		if (m_pRoot == NULL)
		{
			m_pRoot = pTemp;
			
		}
		else
		{
			m_pLast->pNext = pTemp;	
		}
		m_pLast = pTemp;
	}

	bool Delete(int index, T* pValue = NULL)
	{
		int current = 1;
		Atom* pCurrent = m_pRoot;
		Atom* pDeleted = 0;

		if (index <= m_Size && index > 0)   // проверка на допустимость значения индекса
		{
			while (current <= index)
			{
								
			if (current == index - 1)
				{ 

					if (index == m_Size)  // если удаляем последний элемент списка (Готово)
					{
						pDeleted = pCurrent->pNext;
						free(pDeleted);
						pCurrent->pNext = NULL;
						m_pLast = pCurrent;
						m_Size--;
						return true;
					}
					pDeleted = pCurrent->pNext;
					pCurrent->pNext = pCurrent->pNext->pNext;
					free(pDeleted);  // надо память освободить Какой именно указатель удалять? 
					m_Size--;
					return true;
				}

			if (index == 1) 
			{

				if (1 == m_Size) //если элемент единственный
				{
					pDeleted = pCurrent;
					m_pRoot = NULL;
					m_pLast = NULL;
				}

				else 
				{
					pDeleted = m_pRoot;
					m_pRoot = m_pRoot->pNext;
				}

				free(pDeleted);
				m_Size--;
				return true;

			}
		     	pCurrent = pCurrent->pNext;
				current++;

			}

		}
		
		return false;
	}

	bool Insert(int indexAfter, T value)
	{
		int current = 1;
		Atom* pCurrent = m_pRoot;
		Atom* pInsert = 0;

		if (indexAfter <= m_Size)
		{
			pInsert = (Atom*)malloc(sizeof(Atom));
			pInsert->value = value;


			if (indexAfter == 0) // готово, вставка в начало
			{
				pInsert->pNext = m_pRoot;
				m_pRoot = pInsert;
				m_Size++;
				return true;
			}

			while (current <= m_Size)
			{



				if (current == indexAfter)  // готово, вставка в середину (ординарная)
				{

					if (indexAfter == m_Size) // готово, вставка в конец
					{
						pCurrent->pNext = pInsert;
						pInsert->pNext = NULL;
						m_pLast = pInsert;
						m_Size++;
						return true;
					}

					pInsert->pNext = pCurrent->pNext;
					pCurrent->pNext = pInsert;
					m_Size++;
					return true;

					
				
				}
				pCurrent = pCurrent->pNext;
				current++;
			}
		}
		return false;
	}

	bool Get( unsigned int index, T* pValue)
	{

		if (m_pRoot != NULL)
		{
			int current = 1;
			Atom* pCurrent = m_pRoot;

			while (pCurrent->pNext != NULL)
			{
				
				if (current == index)
				{
					*pValue = pCurrent->value;
					return true;
				}

				pCurrent = pCurrent->pNext;
				current++;

			}
		}
		return false;
	}
	int Test(int NumberOfElements) 
	{
	
	}
};

template<typename S>
class Array
{

private:
	S* m_pRoot;
	int m_Size;
	int m_MemSize;

public:

	Array()
	{
		
		m_pRoot = NULL;
		m_Size = 0;
		m_MemSize = 0;
	}
	bool AddFirstElem(S value)
	{
		int* pTemp;
		int i = 0;

		if (m_Size == 0) //Если это первый элемент вектора(готово)
		{
			m_MemSize = m_Size + 5;
			m_pRoot = (int*)malloc(sizeof(int) * m_MemSize);
			


			if (m_pRoot != NULL)
			{
				*m_pRoot = value;
				m_pEnd = m_pRoot[m_Size + 4];
				*m_pEnd = -1;
				m_Size++;
				return true;
			}
		}

		if (m_Size > 0) // Если добавляем не первый элемент вектора(готово)
		{

			if (*m_pEnd != -1)
			{
				m_MemSize = m_Size * 2;
				pTemp = (int*)malloc((sizeof(int)) * (m_MemSize));
				

				if (pTemp != NULL)
				{

					while (i < m_Size)
					{
						pTemp[i + 1] = m_pRoot[i];
						i++;
					}
					pTemp[0] = value;
					m_pEnd = &pTemp[(m_Size * 2) - 1];
					*m_pEnd = -1;
					//		free(m_pRoot);
					m_pRoot = pTemp;
					m_Size++;
					return true;
				}

			}
		}
		return false;
	}
	/*bool AddLastElem(S value)    // Надо реализовать выделение бОльших кусков памяти, проверку влезаем ли мы в эту память, изменить признак конца массива на признак конца памяти.
	{
		int* pTemp;
		int i = 0;

		if (m_Size == 0) //Если это первый элемент вектора(готово)
		{
			m_pRoot = (int*)malloc(sizeof(int) * (m_Size));

			if (m_pRoot != NULL)
			{
				*m_pRoot = value;
				m_pEnd = m_pRoot + 1;
				*m_pEnd = NULL;
				m_Size++;
				return true;
			}
		}

		if (m_Size > 0) // Если добавляем не первый элемент вектора(готово)
		{
			pTemp = (int*)malloc((sizeof(int)) * (m_Size + 1));

			if (pTemp != NULL)
			{

				while (i < m_Size)
				{
					pTemp[i] = m_pRoot[i];
					i++;
				}
				pTemp[m_Size] = value;
				m_pEnd = &pTemp[m_Size + 1];
				*m_pEnd = NULL;
//				free(m_pRoot);
				m_pRoot = pTemp;
				m_Size++;
				return true;
			}
		}
		return false;
	}
	*/
	bool AddLastElem(S value)    // Надо реализовать выделение бОльших кусков памяти, проверку влезаем ли мы в эту память, изменить признак конца массива на признак конца памяти.
	{
		int* pTemp;
		int i = 0;
		if (m_MemSize < m_Size + m_Start + 1)
		{
			int newSize = m_MemSize ? m_MemSize * 2 : 5;	
			pTemp = (int*)malloc(sizeof(int) * newSize);

			if (pTemp == NULL) 
			{
				return false;
			}
		}
		if (m_Size == 0) //Если это первый элемент вектора(готово)
		{
			m_MemSize = m_Size + 5;
			m_pRoot = (int*)malloc(sizeof(int) * m_MemSize);

			if (m_pRoot != NULL)
			{
				*m_pRoot = value;
				m_Size++;
				return true;
			}
		}

		if (m_Size > 0) // Если добавляем не первый элемент вектора( Как освободить память!!)
		{
			if (*m_pEnd != -1)
			{
				m_MemSize = m_Size * 2;
				pTemp = (int*)malloc((sizeof(int)) * (m_MemSize));
			
				if (pTemp != NULL)
				{
					memcpy(pTemp, m_pRoot, sizeof(int)*(m_Size - 1));
					pTemp[m_Size] = value;
					m_pEnd = &pTemp[(m_Size * 2) - 1];
					*m_pEnd = -1;
					//				free(m_pRoot);
					m_pRoot = pTemp;
					m_Size++;
					return true;
				}
			}
			if (*m_pEnd == -1) 
			{
				m_pRoot[m_Size] = value;
				m_Size++;
				return true;
			}
		}
		return false;
	}
	int DeleteFirstElem() // готово
	{
	//int* pTemp;
	int value;
	//int* pDeleted;

	if (m_Size > 0) 
	{
		m_pRoot = m_pRoot + 1;
		value = m_pRoot[-1];
	//pDeleted = &m_pRoot[0];
	 //pDeleted = m_pRoot;
	//	m_pRoot = pTemp;
    //	free(pDeleted);
		m_Size--;
		return value;

	}
	return -1;
	}
	/*int DeleteLastElem() // Освобождение памяти нужно сделать
	{
		int* pTemp;
		int value;
		int* pDeleted;

		if (m_Size > 0) 
		{
			pTemp = m_pEnd - 1;
			value = m_pEnd[-1];
			m_pEnd = pTemp;
			*m_pEnd = NULL;
			m_Size--;
			return value;
		}
		return -1;
	}*/
	int DeleteLastElem() // готово
	{
	int value;
	int* pDeleted;

	if (m_Size > 0)
	{
	value = m_pRoot[m_Size - 1];
	m_pRoot[m_Size - 1] = NULL; //для m_pEnd
	m_Size--;
	return value;
	}
	return -1;
	}
	int GetElem(unsigned int index) 
	{
		
		if (m_Size > 0 && index < m_Size) 
		{
			return m_pRoot[index];
		}
		return -1;
	}
	bool FitIt() // как освобождать память?
	{
		int* pMemFat;
		int memFat;

		if (m_MemSize > m_Size)
		{
		memFat = m_MemSize - m_Size;

		pMemFat = m_pRoot[m_Size]
		}
		return false;
	}
};

#include <list>
int main()
{
	
	std::list<int> stdList;
	unsigned int STDstartTime = clock();

	int i = 0;

	while (i < 10000) 
	{
	stdList.push_back(785);
	i++;
	}
	unsigned int STDruntime = (clock() - STDstartTime);

	List<double> list;
	unsigned int startTime = clock();

	i = 0;

	while (i < 10000) 
	{
		list.Add(785);
		i++;
	}
	
	unsigned int runtime = (clock() - startTime );
	struct Point 
	{
		int x;
		int y;
	};
	Point Zero;
	Zero.x = 0;
	Zero.y = 0;
	Array<Point> array;

	i = 0;
	unsigned int ArrayStartTime = clock();

	while (i < 10000)
	{
		array.AddLastElem(Zero);
		i++;
	}
	unsigned int ArrayRuntime = (clock() - ArrayStartTime);

	std::vector<int> myVector;

	i = 0;
	unsigned int STDarrayStartTime = clock();

	while (i < 10000)
	{
		myVector.push_back(785);
		i++;
	}
	unsigned int STDarrayRuntime = (clock() - STDarrayStartTime);
	//array.AddLastElem(980);
//	array.AddFirstElem(12);
//	array.AddFirstElem(47);
//	array.AddLastElem(77);
//	array.DeleteLastElem();
//	array.GetElem(2);
	
	double value;
	if (list.Get(2, &value) == true)
	{
		printf("%f", value);
		
	}
		return 0;
}