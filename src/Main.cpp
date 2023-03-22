#include "ListRand.hpp"
#include <iostream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void MakeExampleList(ListRand& RefListRand)
{
	ListNode* LOne		= RefListRand.Add("One");
	ListNode* LTwo		= RefListRand.Add("Two");
	ListNode* LThree	= RefListRand.Add("Three");
	ListNode* LFour		= RefListRand.Add("Four");
	ListNode* LFive		= RefListRand.Add("Five");

	LTwo->Rand		= LTwo;
	LThree->Rand	= LFive;
	LFour->Rand		= LOne;
}

int main()
{
	ListRand LListInput		= {};
	ListRand LListOutput	= {};

	MakeExampleList(LListInput);
	LListInput.PrintList("Input");

	std::ofstream LOut(fs::current_path().string() + "\\example", std::ios::binary);
	if (LOut.is_open())
	{
		LListInput.Serialize(LOut);
	}
	LOut.close();

	std::ifstream LIn(fs::current_path().string() + "\\example", std::ios::binary);
	if (LIn.is_open())
	{
		LListOutput.Deserialize(LIn);
		LListInput.PrintList("Output");
	}
	LIn.close();

	system("pause");

	return EXIT_SUCCESS;
}