#include "ListRand.hpp"
#include "AddressAndIndex.hpp"
#include "LibHelper.hpp"
#include <functional>
#include <algorithm>

// O(n + (n * (log(n))^2) + (n * log(n))), по итогу меньше O(n^2).
// Пример:
// O(3^2) = 9;
// O(3 + (3 * (log(3))^2) + (3 * log(3))) = 5.1142978392747823;
//
// O(10^2) = 100;
// O(10 + (10 * (log(10))^2) + (10 * log(10))) = 30.
void ListRand::Serialize(std::ostream& RefOS)
{
	// Сохранениие кол-ва элементов в списке.
	Save(RefOS, &Count, sizeof(Count));

	if (!Head) return;

	ListNode* LNode = Head;
	// Адрес ноды и её индекс, т.е. когда мы заполняем массив, мы запоминаем его индекс в массиве, чтобы при сортировке не потерять эти данные.
	std::vector<AddressAndIndex> LAddressAndIndex(Count);

	// O(n)
	for (int LIndex = 0; LNode; LNode = LNode->Next, ++LIndex)
	{
		// Я не могу узнать адрес ноды и помножив на её размер узнать где находится рандомный элемент,
		// посему записываю адрес ноды и далее делаю магию.
		//LAddressAndIndex.push_back(AddressAndIndex(reinterpret_cast<uintptr_t>(LNode), LIndex));
		LAddressAndIndex[LIndex] = AddressAndIndex(reinterpret_cast<uintptr_t>(LNode), LIndex);

		// Сохранение Data.
		std::string::size_type LLength = LNode->Data.length();
		Save(RefOS, &LLength, sizeof(LLength));
		Save(RefOS, LNode->Data.data(), LLength);
	}

	// Сортировка вставкой, самый худший случай O(n * log(n) * log(n)).
	std::stable_sort(LAddressAndIndex.begin(), LAddressAndIndex.end());

	// O(n)
	for (LNode = Head; LNode; LNode = LNode->Next)
	{
		// Беру индекс рандомной ноды.
		AddressAndIndex LAddress(reinterpret_cast<uintptr_t>(LNode->Rand), -1);
		// С помощью бинарного поиска нахожу рандомную ноду по адресу, самый худший случай O(log(n)).
		int LRandomIndex = LibHelper::BinarySearch(LAddressAndIndex, LAddress);

		// Сохранение индекса случайного элемента.
		if (LRandomIndex > -1)
		{
			LRandomIndex = (LAddressAndIndex[LRandomIndex].Address == 0 ? -1 : LAddressAndIndex[LRandomIndex].Index);
			Save(RefOS, &LRandomIndex, sizeof(LRandomIndex));
		}
		else
		{
			Save(RefOS, &LRandomIndex, sizeof(LRandomIndex));
		}
	}
}

// O(n).
void ListRand::Deserialize(std::istream& RefIS)
{
	int LCount;
	// Загрузка кол-ва элементов в списке.
	Load(RefIS, &LCount, sizeof(LCount));

	// Массив элементов, необходим для быстрого доступа ко всем существующим элементам в списке.
	std::vector<ListNode*> LNodesArray(LCount);

	int LRandomIndex;
	size_t LLength;
	std::string LData;

	// O(n)
	int LIndex = 0;
	for (; LIndex < LCount; ++LIndex)
	{
		// Загрузка Data.
		Load(RefIS, &LLength, sizeof(LLength));
		LData.resize(LLength);
		Load(RefIS, (void *)LData.data(), LLength);

		ListNode* LNewNode = Add(LData);
		LNodesArray[LIndex] = LNewNode;
	}

	// Загрузка и установка индексов рандомных элементов, O(n).
	LIndex = 0;
	for (; LIndex < LCount; ++LIndex)
	{
		Load(RefIS, &LRandomIndex, sizeof(LRandomIndex));
		if (LRandomIndex > -1)
			LNodesArray[LIndex]->Rand = LNodesArray[LRandomIndex];
	}
}

ListNode* ListRand::Add(const std::string& InData)
{
	ListNode* LResult = new ListNode();
	LResult->Data = InData;

	if (Count == 0)
		Head = LResult;
	else
	{
		Tail->Next = LResult;
		LResult->Prev = Tail;
	}

	Tail = LResult;
	++Count;

	return LResult;
}

void ListRand::PrintList(const std::string &InListName)
{
	if (InListName.length() > 0)
		std::cout << InListName << '\n';

	std::cout << "List count: " << Count << '\n';
	std::string LRandData = "nullptr";
	ListNode* LNode = Head;

	for (int LIndex = 1; LNode; LNode = LNode->Next, ++LIndex)
	{
		std::cout << LIndex << ") " << LNode->Data << '\n';

		LRandData = (LNode->Rand ? LNode->Rand->Data : "nullptr");

		std::cout << "Rand: " << LRandData << '\n';
	}
}