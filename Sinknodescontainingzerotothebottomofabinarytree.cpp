#include <iostream>
using namespace std;

// Định nghĩa cấu trúc Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

// Duyệt trung thứ tự để in cây
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Hoán đổi giá trị nếu nút con khác 0
void thuchien(Node* root) {
    if (root == nullptr) {
        return;
    }

    if (root->left && root->left->data != 0) {
        swap(root->data, root->left->data);
        thuchien(root->left);
    } else if (root->right && root->right->data != 0) {
        swap(root->data, root->right->data);
        thuchien(root->right);
    }
}

// Kiểm tra và hoán đổi giá trị nếu nút cha bằng 0
void ktr(Node*& root) {
    if (root == nullptr) {
        return;
    }

    ktr(root->left);
    ktr(root->right);

    if (root->data == 0) {
        thuchien(root);
    }
}

// Hàm tạo cây từ đầu vào của người dùng
Node* createTree(int& totalNodes, int parentValue = -1, bool isLeft = true) {
    int value;
    if (parentValue == -1) {
        cout << "Nhap gia trị goc: ";
    } else {
        cout << "Nhap gia tri con " << (isLeft ? "trai" : "phai") << " cua " << parentValue << " (hoac -1 neu khong co nut con): ";
    }

    cin >> value;
    if (value == -1) {
        return nullptr;
    }

    Node* node = new Node(value);
    totalNodes++;

    node->left = createTree(totalNodes, value, true);
    node->right = createTree(totalNodes, value, false);

    return node;
}

int main() {
    int totalNodes = 0;
    Node* root = createTree(totalNodes);

    ktr(root);
    cout << "Duyệt trung thứ tự của cây đã được sửa đổi: ";
    inorder(root);
    cout << endl;

    return 0;
}
