#ifndef _LIST_NODE_HPP_
#define _LIST_NODE_HPP_

#include <string>

class ListNode
{
public:
	ListNode* Prev		= nullptr;
	ListNode* Next		= nullptr;
	ListNode* Rand		= nullptr;
	std::string Data	= {};
};

#endif // _LIST_NODE_HPP_