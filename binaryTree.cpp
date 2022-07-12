#include <iostream>
using namespace std;

struct Price {
    float value = 0;
    Price* parent=nullptr;
    Price* left = nullptr;
    Price* right = nullptr;
};

class BinaryTree {
    Price* root = nullptr;
    int size = 0;
public:
    BinaryTree(){}
    BinaryTree(float value) {
        Price* node = new Price{ value };
        root = node;
        size++;
    }

    void print(Price* node = nullptr) {
        if (node == nullptr) node = root;
        cout << node->value << " ";
        if (node->left != nullptr) print(node->left);
        if (node->right != nullptr) print(node->right);
    }

    void add(float data) {
        if (size == 0) BinaryTree(data);
        else {
            Price* iter = root;
            Price* node = new Price{ data };
            while (true) {
                if (node->value > iter->value) {
                    if (iter->right == nullptr) {
                        node->parent = iter;
                        iter->right = node;
                        break;
                    }
                    else iter = iter->right;
                }
                else {
                    if (iter->left == nullptr) {
                        node->parent = iter;
                        iter->left = node;
                        break;
                    }
                    else iter = iter->left;
                }
            }
            size++;
        }
    }

    Price* search(float data) {
        Price* iter = root;
        while (true) {
            if (data == iter->value) return iter;
            else if (data > iter->value) {
                if (iter->right == nullptr) return nullptr;
                else iter = iter->right;
            }
            else if (data < iter->value) {
                if (iter->left == nullptr) return nullptr;
                else iter = iter->left;
            }
        }
    }

    void remove(float data) {
        Price* node = search(data);
        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent->left == node) node->parent->left = nullptr;
            else node->parent->right = nullptr;
            delete node;
        }
        else if (node->left == nullptr) {
            if (node->parent->left == node) node->parent->left = node->right;
            else node->parent->right = node->right;
            delete node;
        }
        else if (node->right == nullptr) {
            if (node->parent->left == node) node->parent->left = node->left;
            else node->parent->right = node->left;
            delete node;
        }
        else {
            if (node == root) {
                Price* iter = node->right;
                while (iter->left != nullptr) iter = iter->left;
                Price* buf = node;
                node = iter;
                if (node->left == nullptr && node->right == nullptr) node->parent->left = nullptr;
                else node->parent->left = node->right;
                node->left = buf->left;
                node->right = buf->right;
                node->left->parent = node;
                node->right->parent = node;
                node->parent = nullptr;
                delete buf;
                root = node;
            }
            else if(node->value<node->parent->value) {
                Price* iter = node->right;
                while (iter->left != nullptr) iter = iter->left;
                Price* buf = node;
                node = iter;
                if (node->left == nullptr && node->right == nullptr) node->parent->left = nullptr;
                else node->parent->left = node->right;
                node->parent = buf->parent;
                node->left = buf->left;
                node->right = buf->right;
                node->parent->left = node;
                node->left->parent = node;
                node->right->parent = node;
                delete buf;
            }
            else {
                Price* iter = node->left;
                while (iter->right != nullptr) iter = iter->right;
                Price* buf = node;
                node = iter;
                if (node->left == nullptr && node->right == nullptr) node->parent->right = nullptr;
                else node->parent->right = node->left;
                node->parent = buf->parent;
                node->left = buf->left;
                node->right = buf->right;
                node->parent->right = node;
                node->left->parent = node;
                node->right->parent = node;
                delete buf;
            }
        }
        size--;
    }
};

int main()
{
    BinaryTree prices(45.6);
    prices.print();
    cout << endl;
    prices.add(90.8);
    prices.add(1.4);
    prices.add(70.0);
    prices.add(27.1);
    prices.print();
    cout << endl;
    prices.add(100.0);
    prices.add(0.3);
    prices.add(45.5);
    prices.add(19.9);
    prices.print();
    cout << endl;

    cout << prices.search(27.1) << endl;
    cout << prices.search(77) << endl;

    prices.remove(1.4);
    prices.print();
    cout << endl;
    prices.remove(45.6);
    prices.print();
    cout << endl;
}


