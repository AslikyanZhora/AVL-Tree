#pragma once
#include <iostream>
#include <algorithm>
#include "TreeNode.h"

template <typename T>
class AVLTree
{
public:

	AVLTree();

	~AVLTree();

	void insert(const T& value);

	void remove(const T& value);

	void preorder() const;

	void postorder() const;

	void inorder() const;

private:

	static TreeNode<T>* insert(TreeNode<T>* node, const T& value);

	static void preorder(TreeNode<T>* node);

	static void postorder(TreeNode<T>* node);

	static void inorder(TreeNode<T>* node);

	static size_t height(TreeNode<T>* node);

	static int get_balance(TreeNode<T>* node);

	static TreeNode<T>* right_rotate(TreeNode<T>* node);

	static TreeNode<T>* left_rotate(TreeNode<T>* node);

	static TreeNode<T>* to_balace(TreeNode<T>* node, const T& value);

	static TreeNode<T>* remove(TreeNode<T>* node, const T& value);

	static TreeNode<T>* findMin(TreeNode<T>* node);

	static TreeNode<T>* rebalance(TreeNode<T>* node);

	static void clear(TreeNode<T>* node);

private:

	TreeNode<T>* m_root;
};

#include "AVLTree.hpp"

