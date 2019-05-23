#pragma once
#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode(const T& value):key(value), left(nullptr), right(nullptr), height(1)
{
}

template<typename T>
TreeNode<T>::~TreeNode()
{
}
