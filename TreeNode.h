#pragma once

template <typename T>
struct TreeNode
{
	TreeNode(const T& value);
	~TreeNode();

	T key;
	TreeNode* left;
	TreeNode* right;
	size_t height;
};

#include "TreeNode.hpp"

