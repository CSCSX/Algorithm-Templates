#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class PreOrderTraversal 
{
public:
    std::vector<int> preorderTraversal(TreeNode* root) 
    {
        std::vector<int> ret;
        TreeNode* now = root;
        std::stack<TreeNode*> st;
        while (!st.empty() || now != nullptr)
        {
            while (now != nullptr)
            {
                ret.push_back(now->val);
                st.push(now);
                now = now->left;
            }
            now = st.top();
            st.pop();
            now = now->right;
        }
        return ret;
    }
};

class InOrderTraversal 
{
public:
    std::vector<int> inorderTraversal(TreeNode* root) 
    {
        std::vector<int> ret;
        std::stack<TreeNode*> st;
        while (root != nullptr || !st.empty())
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            ret.push_back(root->val);
            root = root -> right;
        }
        return ret;
    }
};

class PostOrderTraversal 
{
public:
    std::vector<int> postorderTraversal(TreeNode* root) 
    {
        std::vector<int> ret;
        std::stack<TreeNode*> st;
        TreeNode* prev = nullptr;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root -> left;
            }
            root = st.top();
            st.pop();
            if (root -> right == nullptr || root -> right == prev)
            {
                ret.push_back(root -> val);
                prev = root;
                root = nullptr;
            }
            else
            {
                st.push(root);
                root = root -> right;
            }
        }
        return ret;
    }
};

#endif