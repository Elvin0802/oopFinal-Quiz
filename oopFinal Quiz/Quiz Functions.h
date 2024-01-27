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

void ShuffleList(list<Question*>* QList)
{
	try
	{
		random_device AppRandomGenerator;

		mt19937 e(AppRandomGenerator());

		shuffle(QList->begin(), QList->end(), e);
	}
	catch (...)
	{
		return;
	}
}