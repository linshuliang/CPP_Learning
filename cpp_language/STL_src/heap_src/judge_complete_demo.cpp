#include "judge_complete_bt.h"
using namespace std;

// 1. 满二叉树
void test1()
{
    //       1
    //   2       3
    // 4    5  6   7
    TreeNode<int>* node1 = new TreeNode<int>(1);
    TreeNode<int>* node2 = new TreeNode<int>(2);
    TreeNode<int>* node3 = new TreeNode<int>(3);
    TreeNode<int>* node4 = new TreeNode<int>(4);
    TreeNode<int>* node5 = new TreeNode<int>(5);
    TreeNode<int>* node6 = new TreeNode<int>(6);
    TreeNode<int>* node7 = new TreeNode<int>(7);
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    cout << IsComplete<int>(node1) << endl;
}

// 2. 二叉树为空
void test2()
{
    cout << IsComplete<int>(NULL) << endl;
}

// 3.二叉树不为空，也不是满二叉树，遇到一个结点左孩子为空，右孩子不为空
void test3()
{
    //       1
    //   2       3
    // 4    5      7
    TreeNode<int>* node1 = new TreeNode<int>(1);
    TreeNode<int>* node2 = new TreeNode<int>(2);
    TreeNode<int>* node3 = new TreeNode<int>(3);
    TreeNode<int>* node4 = new TreeNode<int>(4);
    TreeNode<int>* node5 = new TreeNode<int>(5);
    TreeNode<int>* node7 = new TreeNode<int>(7);
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->right = node7;
    cout << IsComplete<int>(node1) << endl;
}

// 4.二叉树不为空，也不是满二叉树，遇到叶子节点, 则该叶子节点之后的所有结点都为叶子节点
void test4()
{
    //        1
    //    2       3
    // 4    5
    TreeNode<int>* node1 = new TreeNode<int>(1);
    TreeNode<int>* node2 = new TreeNode<int>(2);
    TreeNode<int>* node3 = new TreeNode<int>(3);
    TreeNode<int>* node4 = new TreeNode<int>(4);
    TreeNode<int>* node5 = new TreeNode<int>(5);
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    cout << IsComplete<int>(node1) << endl;
}

//5.二叉树不为空，也不是满二叉树，遇到左孩子不为空，右孩子为空的结点，则该节点之后的所有结点都为叶子节点
void test5()
{
    //        1
    //    2       3
    // 4    5   6
    TreeNode<int>* node1 = new TreeNode<int>(1);
    TreeNode<int>* node2 = new TreeNode<int>(2);
    TreeNode<int>* node3 = new TreeNode<int>(3);
    TreeNode<int>* node4 = new TreeNode<int>(4);
    TreeNode<int>* node5 = new TreeNode<int>(5);
    TreeNode<int>* node6 = new TreeNode<int>(6);
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    cout << IsComplete<int>(node1) << endl;
}

int main()
{
    test1();  // 1
    test2();  // 0
    test3();  // 0
    test4();  // 1
    test5();  // 1
    return 0;
}