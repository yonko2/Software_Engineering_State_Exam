#include <iostream>
#include <queue>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T value;
        Node *left = nullptr, *right = nullptr;
        Node(const T& val, Node* l = nullptr, Node* r = nullptr) : value(val), left(l), right(r) {}
    } *root = nullptr;

    void free(Node* curr) {
        if (!curr) return;
        free(curr->left); free(curr->right);
        delete curr;
    }

    Node* deepCopy(const Node* curr) {
        return curr ? new Node(curr->value, deepCopy(curr->left), deepCopy(curr->right)) : nullptr;
    }

    Node* _insert(Node* curr, const T& val) {
        if (!curr) return new Node(val);
        if (val < curr->value) curr->left = _insert(curr->left, val);
        else if (curr->value < val) curr->right = _insert(curr->right, val);
        return curr;
    }

    bool _contains(const Node* curr, const T& val) const {
        if (!curr) return false;
        if (curr->value == val) return true;
        return val < curr->value ? _contains(curr->left, val) : _contains(curr->right, val);
    }

    Node* _remove(Node* curr, const T& val) {
        if (!curr) return nullptr;
        if (val < curr->value) curr->left = _remove(curr->left, val);
        else if (curr->value < val) curr->right = _remove(curr->right, val);
        else {
            if (!curr->left || !curr->right) {
                Node* temp = curr->left ? curr->left : curr->right;
                delete curr;
                return temp;
            }
            Node* minNode = curr->right;
            while (minNode->left) minNode = minNode->left;
            curr->value = minNode->value;
            curr->right = _remove(curr->right, curr->value);
        }
        return curr;
    }

    void _dfs(const Node* curr) const {
        if (!curr) return;
        _dfs(curr->left);
        std::cout << curr->value << " ";
        _dfs(curr->right);
    }

public:
    BinarySearchTree() = default;
    ~BinarySearchTree() { free(root); }
    BinarySearchTree(const BinarySearchTree& other) { root = deepCopy(other.root); }
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) { free(root); root = deepCopy(other.root); }
        return *this;
    }

    void insert(const T& val) { root = _insert(root, val); }
    bool contains(const T& val) const { return _contains(root, val); }
    void remove(const T& val) { root = _remove(root, val); }
    void dfs() const { _dfs(root); std::cout << "\n"; }

    void bfs() const {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            size_t size = q.size();
            while (size--) {
                Node* curr = q.front(); q.pop();
                std::cout << curr->value << " ";
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            std::cout << "\n";
        }
    }
};

int main() {
    BinarySearchTree<int> bst;
    for (int x : {7, 4, 2, 6, 5, 8, 3, 1}) bst.insert(x);

    std::cout << "BFS:\n"; bst.bfs();
    std::cout << "DFS:\n"; bst.dfs();
}
