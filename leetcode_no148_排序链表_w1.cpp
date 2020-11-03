/* ------------------------------------------------------------------|
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

进阶：

你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 

示例 1：


输入：head = [4,2,1,3]
输出：[1,2,3,4]
示例 2：


输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]
示例 3：

输入：head = []
输出：[]
 

提示：

链表中节点的数目在范围 [0, 5 * 104] 内
-105 <= Node.val <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	归并排序法
*
*	执行用时：152 ms, 在所有 C++ 提交中击败了20.12%的用户
*	内存消耗：28.7 MB, 在所有 C++ 提交中击败了36.19%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* cut(ListNode* head, int size) {
    ListNode* node = head;
    //size先减再用
    while (node && --size) {
        node = node->next;
    }
    if (!node) {
        return nullptr;
    }

    //记录要返回的节点地址
    ListNode* next = node->next;
    //断开节点
    node->next = nullptr;
    //返回记录好的值
    return next;
}

ListNode* merge(ListNode* l1, ListNode* l2, ListNode* head) {
    ListNode* node = head;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            node->next = l1;
            l1 = l1->next;
        }
        else {
            node->next = l2;
            l2 = l2->next;
        }
        node = node->next;  
    }
    node->next = l1 ? l1 : l2;
    while (node->next) {
        node = node->next;
    }
    return node;
}

ListNode* sortList(ListNode* head) {
    if (!head) {
        return head;
    }
    ListNode preHead(0);
    preHead.next = head;

    ListNode* node = head;
    int len = 1;
    while (node->next) {
        len++;
        node = node->next;
    }

    for (int size = 1; size < len; size *= 2) {
        ListNode* current = preHead.next;
        ListNode* tail = &preHead;
        while (current) {
            ListNode* left = current;
            ListNode* right = cut(left, size);
            current = cut(right, size);
            tail = merge(left, right, tail);
        } 
    }
    return preHead.next;
}

int main() {
    ListNode* qnode = new ListNode(-1);
    ListNode* head = qnode;
    qnode->next = new ListNode(5);
    qnode = qnode->next;
    qnode->next = new ListNode(3);
    qnode = qnode->next;
    qnode->next = new ListNode(4);
    qnode = qnode->next;
    qnode->next = new ListNode(0);
    qnode = qnode->next;

}