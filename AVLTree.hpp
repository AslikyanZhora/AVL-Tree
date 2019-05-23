#include "AVLTree.h"
#pragma once

template <typename T>
AVLTree<T>::AVLTree():m_root(nullptr)
{
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	clear(m_root);
}

template<typename T>
inline void AVLTree<T>::insert(const T& value)
{
	m_root = insert(m_root, value);
	m_root = to_balace(m_root, value);
}

template<typename T>
inline void AVLTree<T>::remove(const T& value)
{
	if (nullptr == m_root)
	{
		return;
	}

	m_root = remove(m_root, value);
	m_root = rebalance(m_root);
}

template<typename T>
inline void AVLTree<T>::preorder() const
{
	if (nullptr == m_root)
	{
		return;
	}

	preorder(m_root);

	std::cout << std::endl;
}

template<typename T>
inline void AVLTree<T>::postorder() const
{
	if (nullptr == m_root)
	{
		return;
	}

	postorder(m_root);

	std::cout << std::endl;
}

template<typename T>
inline void AVLTree<T>::inorder() const
{
	if (nullptr == m_root)
	{
		return;
	}

	inorder(m_root);

	std::cout << std::endl;

}

template<typename T>
inline TreeNode<T>* AVLTree<T>::insert(TreeNode<T>* node, const T& value)
{
	if (nullptr == node)
	{
		return new TreeNode<T>(value);
	}

	if (value < node->key)
	{
		node->left = insert(node->left, value);
	}

	else 
	{
		node->right = insert(node->right, value);
	}

	node->height = 1 + std::max(height(node->left), height(node->right));
	
	return node;

}

template<typename T>
inline void AVLTree<T>::preorder(TreeNode<T>* node)
{
	std::cout << node->key << "  ";
	if (nullptr != node->left)
	{
		preorder(node->left);
	}

	if (nullptr != node->right)
	{
		preorder(node->right);
	}
}

template<typename T>
inline void AVLTree<T>::postorder(TreeNode<T>* node)
{
	if (nullptr != node->left)
	{
		postorder(node->left);
	}

	if (nullptr != node->right)
	{
		postorder(node->right);
	}

	std::cout << node->key << "  ";
}

template<typename T>
inline void AVLTree<T>::inorder(TreeNode<T>* node)
{
	if (nullptr != node->left)
	{
		inorder(node->left);
	}

	std::cout << node->key << "  ";

	if (nullptr != node->right)
	{
		inorder(node->right);
	}
}

template<typename T>
inline size_t AVLTree<T>::height(TreeNode<T>* node)
{
	if (nullptr == node)
	{
		return 0u;
	}
	return node->height;
}

template<typename T>
inline int AVLTree<T>::get_balance(TreeNode<T>* node)
{
	if (nullptr == node)
	{
		return 0;
	}
	return (height(node->left) - height(node->right));
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::right_rotate(TreeNode<T>* node)
{
	TreeNode<T>* temp = node->left;
	TreeNode<T>* left = temp->right;

	temp->right = node;
	node->left = left;

	node->height = std::max(height(node->left), height(node->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;

	return temp;
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::left_rotate(TreeNode<T>* node)
{
	TreeNode<T>* temp = node->right;
	TreeNode<T>* right = temp->left;

	temp->left = node;
	node->right = right;

	node->height = std::max(height(node->left), height(node->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;

	return temp;
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::to_balace(TreeNode<T>* node, const T& value)
{
	int balance = get_balance(node);

	if (balance > 1 && value < node->left->key)
	{
		return right_rotate(node);
	}

	if (balance < -1 && value > node->right->key)
	{
		return left_rotate(node);
	}

	if (balance > 1 && value > node->left->key)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}

	if (balance < -1 && value < node->right->key)
	{
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::remove(TreeNode<T>* node, const T& value)
{
	if (nullptr == node)
	{
		return node;
	}

	if (value < node->key)
	{
		node->left = remove(node->left, value);
	}

	else if (value > node->key)
	{
		node->right = remove(node->right, value);
	}

	else
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			delete node;
			node = nullptr;
		}

		else if (node->left == nullptr)
		{
			TreeNode<T>* temp = node;
			node = node->right;

			delete temp;
			temp = nullptr;
		}

		else if (node->right == nullptr)
		{
			TreeNode<T>* temp = node;
			node = node->left;

			delete temp;
			temp = nullptr;
		}

		else
		{
			node->key = findMin(node->right)->key;
			node->right = remove(node->right, findMin(node->right)->key);
		}
	}

	return node;
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::findMin(TreeNode<T>* node)
{
	if (nullptr == node || nullptr == node->left)
	{
		return node;
	}
	return findMin(node->left);
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::rebalance(TreeNode<T>* node)
{
	node->height = 1 + std::max(height(node->left), height(node->right));

	int balance = get_balance(node);

	if (balance > 1 && get_balance(node->left) >= 0)
	{
		return right_rotate(node);
	}

	if (balance < -1 && get_balance(node->right) <= 0)
	{
		return left_rotate(node);
	}

	if (balance > 1 && get_balance(node->left) < 0)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}

	if (balance < -1 && get_balance(node->right) > 0)
	{
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

template<typename T>
inline void AVLTree<T>::clear(TreeNode<T>* node)
{
	if (nullptr != node)
	{
		clear(node->left);
		clear(node->right);
	}

	delete node;
	node = nullptr;
}
