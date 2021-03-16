#include <iostream>
#include <queue>

template<class T>
struct TreeNode
{
	T data;
	TreeNode<T> *left;
	TreeNode<T> *right;

	TreeNode(const T& x) : data(x), left(nullptr), right(nullptr) {}
};

template<class T>
bool IsComplete(TreeNode<T>* root)
{
	// 如果树为空，返回 false
	if (root == nullptr) return false;

	// 如果树不为空，层序遍历二叉树
	std::queue<TreeNode<T>*> q;
	q.push(root);

	while (!q.empty())
	{
		TreeNode<T>* top = q.front();
	
		// 如果左/右子节点都存在，则 pop 出该节点，并 push 左右子节点
		if (top->left && top->right)
		{
			q.pop();
			q.push(top->left);
			q.push(top->right);
		}
		// 如果该节点的左孩子为空，右孩子不为空，则不是完全二叉树
		if (top->left == nullptr && top->right)
		{
			return false;
		}

		// 如果该节点左孩子不为空，右孩子为空或者该节点为叶子节点，则该节点之后的所有结点都是叶子节点
		if ((top->left && top->right == nullptr) || (top->left == nullptr && top->right == nullptr))
		{
			if (top->left) q.push(top->left);

			q.pop();  // 则该节点之后的所有结点都是叶子节点

			while (!q.empty())
			{
				top = q.front();
				if (top->left == nullptr && top->right == nullptr)
					q.pop();
				else
					return false;
			}
		}
	}

	return true;
}
