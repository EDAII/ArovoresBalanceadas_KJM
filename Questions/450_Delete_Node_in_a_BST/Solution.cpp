
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    unordered_map<TreeNode*, int> heightMap;

    int height(TreeNode* n) {
        return n ? heightMap[n] : 0;
    }

    void updateHeight(TreeNode* n) {
        if (n)
            heightMap[n] = 1 + max(height(n->left), height(n->right));
    }

    int balanceFactor(TreeNode* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* middleSubtree = x->right;

        x->right = y;
        y->left = middleSubtree;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* middleSubtree = y->left;

        y->left = x;
        x->right = middleSubtree;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    TreeNode* rebalance(TreeNode* node) {
        if (!node) return node;
        updateHeight(node);

        int bf = balanceFactor(node);

        // LL
        if (bf > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);
        // LR
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RR
        if (bf < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);
        // RL
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* getMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode* deleteAVL(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->val)
            root->left = deleteAVL(root->left, key);
        else if (key > root->val)
            root->right = deleteAVL(root->right, key);
        else {
            if (!root->left || !root->right) {
                TreeNode* child = root->left ? root->left : root->right;
                delete root;
                return child;
            } 
            else {
                TreeNode* succ = getMin(root->right);
                root->val = succ->val;
                root->right = deleteAVL(root->right, succ->val);
            }
        }
        return rebalance(root);
    }

public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        return deleteAVL(root, key);
    }
};