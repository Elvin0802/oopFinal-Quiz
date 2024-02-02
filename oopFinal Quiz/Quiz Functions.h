#pragma once


// Get Question in List with index. For Show and To Answer Question.
Question* GetQuestionByIndex(list<Question*>*& QList, int index = -1)
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

// Fill Vector by ' empty '
void FillWithEmpty(vector<string>& _Vector, size_t _count)
{
	for (size_t emp = 0; emp < _count; emp++)
	{
		_Vector.push_back("_empty_");
	}
}

// Delete All Items In List (Heap).
void DeleteAllItemsInList(list<Question*>*& _list)
{
	if (_list == nullptr)
		return;

	for (auto elem : *_list)
	{
		if (elem != nullptr)
		{
			delete elem;
			elem = nullptr;
		}
	}
	_list->clear();
}

// Predicator For Leader Board. (sort and show)
// Compared By High to Low.
bool ComparePlayersBySuccessRate(const Player* first, const Player* second)
{
	return first->Get_SuccessRate() > second->Get_SuccessRate();
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
