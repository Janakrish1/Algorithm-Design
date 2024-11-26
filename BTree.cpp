#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool leaf) {
        isLeaf = leaf;
    }

    void inOrderTraversal() {
        for (int i = 0; i < keys.size(); i++) {
            if (!isLeaf) {
                children[i]->inOrderTraversal();
            }
            cout << keys[i] << " ";
        }
        if (!isLeaf) {
            children[keys.size()]->inOrderTraversal();
        }
    }

    BTreeNode* findKey(int key) {
        int i = 0;
        while (i < keys.size() && key > keys[i]) {
            i++;
        }

        if (i < keys.size() && keys[i] == key) {
            return this;
        }

        if (isLeaf) {
            return nullptr;
        }

        return children[i]->findKey(key);
    }

    void splitNode(int idx, BTreeNode* child) {
        BTreeNode* newNode = new BTreeNode(child->isLeaf);
        for (int j = 2; j < 4; j++) {
            newNode->keys.push_back(child->keys[j]);
        }
        if (!child->isLeaf) {
            for (int j = 2; j <= 4; j++) {
                newNode->children.push_back(child->children[j]);
            }
        }
        child->keys.resize(2);
        if (!child->isLeaf) {
            child->children.resize(2);
        }

        children.insert(children.begin() + idx + 1, newNode);
        keys.insert(keys.begin() + idx, child->keys[2]);
    }

    void insertInNonFull(int key) {
        int i = keys.size() - 1;
        if (isLeaf) {
            keys.push_back(0);
            while (i >= 0 && key < keys[i]) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
        } else {
            while (i >= 0 && key < keys[i]) {
                i--;
            }
            i++;
            if (children[i]->keys.size() == 4) {
                splitNode(i, children[i]);
                if (key > keys[i]) {
                    i++;
                }
            }
            children[i]->insertInNonFull(key);
        }
    }
};

class BTree {
public:
    BTreeNode* root;

    BTree() {
        root = nullptr;
    }

    void inOrderTraversal() {
        if (root) {
            root->inOrderTraversal();
        } else {
            cout << "Tree is empty." << endl;
        }
    }

    BTreeNode* findKey(int key) {
        return root ? root->findKey(key) : nullptr;
    }

    void insertKey(int key) {
        if (!root) {
            root = new BTreeNode(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 4) {
                BTreeNode* newRoot = new BTreeNode(false);
                newRoot->children.push_back(root);
                newRoot->splitNode(0, root);
                root = newRoot;
            }
            root->insertInNonFull(key);
        }
    }
};

int main() {
    BTree bTree;
    vector<int> keys = {4,3,6,1,4,67,74,2,3,5,4};
    for (int key : keys) {
        bTree.insertKey(key);
    }
    cout << "In Order Traversal of the B-Tree: ";
    bTree.inOrderTraversal();
    return 0;
}