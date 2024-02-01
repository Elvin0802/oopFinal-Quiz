#pragma once


// Get Question in List with index. For Show and To Answer Question.
Question* GetQuestionByIndex(const list<Question*>* QList, int index = -1)
{
	if (index == -1 || (index >= QList->size()))
	{
		return nullptr;
	}
	else
	{
		int iter = 0;
		for (auto quest : *QList)
		{
			if (iter == index)
			{
				return (quest);
			}
			iter++;
		}
	}
	return nullptr;
}

void FillWithEmpty(vector<string>& _Vector, size_t _count)
{
	for (size_t emp = 0; emp < _count; emp++)
	{
		_Vector.push_back("_empty_");
	}
}

void DeleteItemsInList()
{


}

// Shuffle with random engine ( only work with Collection )
//template<typename T>
//void Shuffle(T Collection)
//{
//	try
//	{
//		random_device AppRandomGenerator;
//
//		mt19937 e(AppRandomGenerator());
//
//		shuffle(Collection->begin(), Collection->end(), e);
//	}
//	catch (...)
//	{
//		return;
//	}
//}
