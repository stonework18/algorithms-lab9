#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <clocale>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;
    void preOrder(Node* node) const {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
    void postOrder(Node* node) const {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }
    int sum(Node* node) const {
        if (node == nullptr) return 0;
        return node->data + sum(node->left) + sum(node->right);
    }
    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        destroy(root);
    }
    void buildSample() {
        root = new Node(10);
        root->left = new Node(5);
        root->right = new Node(15);

        root->left->left = new Node(3);
        root->left->right = new Node(7);

        root->right->right = new Node(20);

        root->left->right->left = new Node(6);
        root->right->right->left = new Node(18);
    }
    void preOrder() const {
        preOrder(root);
        cout << endl;
    }
    void inOrder() const {
        inOrder(root);
        cout << endl;
    }
    void postOrder() const {
        postOrder(root);
        cout << endl;
    }
    void levelOrder() const {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front(); 
            q.pop();
            cout << current->data << " ";
            if (current->left != nullptr) q.push(current->left); 
            if (current->right != nullptr) q.push(current->right);
        }
        cout << endl;
    }
    int sumAll() const {
        return sum(root);
    }
};

class BST {
private:
    Node* root;
    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->data) {
            node->left = insert(node->left, key);
        }
        else if (key > node->data) {
            node->right = insert(node->right, key);
        }
        return node;
    }
    Node* search(Node* node, int key) const {
        if (node == nullptr || node->data == key) {
            return node;
        }
        if (key < node->data) {
            return search(node->left, key);
        }
        return search(node->right, key);
    }
    Node* findMin(Node* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* remove(Node* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data) {
            node->left = remove(node->left, key);
        }
        else if (key > node->data) {
            node->right = remove(node->right, key);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    int height(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
public:
    BST() : root(nullptr) {}
    ~BST() { 
        destroy(root);
    }
    void insert(int key) {
        root = insert(root, key);
    }
    bool search(int key) const {
        return search(root, key) != nullptr;
    }
    void remove(int key) {
        root = remove(root, key);
    }
    void inOrder() const {
        inOrder(root);
        cout << endl;
    }
    int height() const {
        return height(root);
    }
    bool minValue(int& result) const {
        Node* node = findMin(root);
        if (node == nullptr) return false;
        result = node->data;
        return true;
    }
    bool maxValue(int& result) const {
        if (root == nullptr) return false;
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        } result = current->data;
        return true;
    }
    bool predecessor(int key, int& pred) const {
        Node* current = root;
        bool found = false;

        while (current != nullptr) {
            if (current->data < key) {
                pred = current->data;
                found = true;
                current = current->right;
            }
            else {
                current = current->left;
            }
        }
        return found;
    }
};
void part1() {
    cout << "Part 1." << endl;

    BinaryTree tree;
    tree.buildSample();

    cout << "pre-order: ";
    tree.preOrder();

    cout << "in-order: ";
    tree.inOrder();

    cout << "post-order: ";
    tree.postOrder();

    cout << "level-order: ";
    tree.levelOrder();

    cout << "The sum of all elements: " << tree.sumAll() << endl;
    cout << endl;
}
void part2() {
    cout << "Part 2." << endl;

    BST tree;
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };

    for (int value : values) {
        tree.insert(value);
    }
    cout << "In-order BST: ";
    tree.inOrder();
    cout << "Search 40: "
        << (tree.search(40) ? "found" : "not found") << endl;
    cout << "Search 100: "
        << (tree.search(100) ? "found" : "not found") << endl;
    int pred;
    if (tree.predecessor(60, pred)) {
        cout << "Parent 60: " << pred << endl;
    }
    else {
        cout << "Parent 60: none" << endl;
    }
    if (tree.predecessor(20, pred)) {
        cout << "Parent 20: " << pred << endl;
    }
    else {
        cout << "Parent 20: none" << endl;
    }
    cout << endl;
}
void part3() {
    cout << "Part 3" << endl;
    BST tree;
    vector<int> sequence;
    set<int> used;
    srand(static_cast<unsigned>(time(nullptr)));
    while (sequence.size() < 20) {
        int value = rand() % 100 + 1;
        if (used.insert(value).second) {
            sequence.push_back(value);
            tree.insert(value);
        }
    }
    cout << "The generated sequence: ";
    for (int value : sequence) {
        cout << value << " ";
    }
    cout << endl;

    cout << "In-order (sorts): ";
    tree.inOrder();

    int minValue, maxValue;

    if (tree.minValue(minValue)) {
        cout << "Minimum element: " << minValue << endl;
    }

    if (tree.maxValue(maxValue)) {
        cout << "Maximum element: " << maxValue << endl;
    }

    cout << "Height: " << tree.height() << endl;

    int key;
    cout << "Enter the element to be deleted: ";
    cin >> key;

    tree.remove(key);

    cout << "After deletion " << key << ": ";
    tree.inOrder();

    cout << endl;
}

int main() {
    part1();
    part2();
    part3();

    return 0;
}