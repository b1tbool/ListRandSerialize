#ifndef _LIST_RAND_HPP_
#define _LIST_RAND_HPP_

#include "ListNode.hpp"
#include "Serializable.hpp"

class ListRand : public ISerializable
{
public:
	void Serialize(std::ostream& RefOS) override;

	void Deserialize(std::istream& RefIS) override;

	ListNode* Add(const std::string& InData);

	void PrintList(const std::string& InListName = "");

private:
	ListNode* Head	= nullptr;
	ListNode* Tail	= nullptr;
	int Count		= 0;
};

#endif // _LIST_RAND_HPP_