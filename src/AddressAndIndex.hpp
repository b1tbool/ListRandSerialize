#ifndef _ADDRESS_AND_INDEX_HPP_
#define _ADDRESS_AND_INDEX_HPP_

// Нужно для uintptr_t.
#include <iostream>

// Хотел было работать с std::pair, но у него с операторами проблемы были, поэтому пришлось написать свсою структуру для работы.
// Суть структуры проста:
// Мне необходимо работать адресами нод, ибо только так я быстро (быстрее O(n^2)) могу получить "индекс" рандомной ноды в списке;
// Беру адрес и индекс ноды, в каком месте в массиве она сейчас находится, дабы после сортировки не потерять нужный мне индекс;
// Сортирую, нахожу нужную ноду по адресу и выдаю индекс.
struct AddressAndIndex
{
	uintptr_t Address	= 0;
	int Index			= -1;

	AddressAndIndex()
	{
		Address	= 0;
		Index	= -1;
	}

	AddressAndIndex(uintptr_t InAddress, int InIndex)
	{
		Address	= InAddress;
		Index	= InIndex;
	}

	bool operator<(const AddressAndIndex &InValue) const
	{
		return Address < InValue.Address;
	}

	bool operator>(const AddressAndIndex &InValue) const
	{
		return Address > InValue.Address;
	}

	bool operator!=(const AddressAndIndex &InValue) const
	{
		return Address != InValue.Address;
	}

	bool operator==(const AddressAndIndex &InValue) const
	{
		return Address == InValue.Address;
	}
};

#endif // _ADDRESS_AND_INDEX_HPP_