#include <iostream>
#include <time.h>
#include <windows.h>
#include <psapi.h>
using namespace std;
 
// Cấu trúc dữ liệu để lưu trữ nút cây nhị phân
struct Node
{
    int data;
    Node *left, *right;
 
    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

// Hàm thực hiện duyệt theo thứ tự trên cây
void inorder(Node* root)
{
    if (root == nullptr) {
        return;
    }
 
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Hàm kiểm tra xem một nút đã cho có phải là nút lá hay không
bool isLeaf(Node* node) {
    return (node->left == nullptr && node->right == nullptr);
}

// Hàm chính cắt ngắn cây nhị phân đã cho để loại bỏ các nút 
// nằm trên đường dẫn có tổng nhỏ hơn 'k'
void trunc(Node* &curr, int k, int target)
{
    // trường hợp cơ sở: cây rỗng
    if (curr == nullptr) {
        return;
    }
    // cập nhật tổng số nút trong đường dẫn từ nút gốc đến nút hiện tại
    target = target + (curr->data);
 
    // Cắt đệ quy các cây con trái và phải
    trunc(curr->left, k, target);
    trunc(curr->right, k, target);

    // Vì chúng ta đang thực hiện duyệt theo thứ tự sau, cây con gốc tại nút hiện tại 
    // có thể đã bị cắt bớt và nút hiện tại là lá 
    
    // nếu nút hiện tại là nút lá và đường dẫn của nó từ nút gốc có tổng 
    // nhỏ hơn số tiền yêu cầu, xóa nó
    if (target < k && isLeaf(curr))
    {
        // giải phóng bộ nhớ được phân bổ cho nút hiện tại
        delete(curr);
        // đặt nút hiện tại thành null (nút được truyền bằng tham chiếu)
        curr = nullptr;
    }
};
 
// Hàm cắt bớt cây nhị phân đã cho để loại bỏ các nút nằm trên 
// đường dẫn có tổng nhỏ hơn 'k'
void truncate(Node* &root, int k)
{
    int target = 0;
    trunc(root, k, target);
}
 
int main()
{
    /* Xây dựng cây sau
             6
           /   \
          /     \
         3       8
               /   \
              /     \
             4       2
           /   \      \
          /     \      \
         1       7      3
    */

    // Biến đo thời gian
    clock_t start_time, end_time;
    start_time = clock();

    // Biến đo RAM
    PROCESS_MEMORY_COUNTERS mem_counters;
    DWORD process_id = GetCurrentProcessId();
    HANDLE process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
    start_time = clock();
    Node* root = new Node(6);
    root->left = new Node(3);
    root->right = new Node(8);
    root->right->left = new Node(4);
    root->right->right = new Node(2);
    root->right->left->left = new Node(1);
    root->right->left->right = new Node(7);
    root->right->right->right = new Node(3);
 
    int k = 20;
    truncate(root, k);
    inorder(root);
    end_time = clock();
    
    printf("\n");
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Thoi gian thuc hien: %f giây\n", elapsed_time);

    // Lấy thông tin RAM sử dụng
    if (GetProcessMemoryInfo(process_handle, &mem_counters, sizeof(mem_counters))) {
        printf("Bo nho su dung: %zu KB\n", mem_counters.WorkingSetSize / 1024);
    } else {
        perror("Không thể lấy thông tin RAM");
    }

    CloseHandle(process_handle);
    return 0;
}

