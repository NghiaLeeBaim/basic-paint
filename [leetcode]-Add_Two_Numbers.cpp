/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdlib.h>

// Khai báo hàm addTwoNumbers. Hàm này nhận vào
 2 con trỏ l1, l2 trỏ tới vị trí đầu tiên của 2 danh sách trong ram. Hàm cam kết sẽ trả về một con trỏ kiểu struct ListNode* chỉ tới kết quả.
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    // Yeu cau he dieu hanh cap ram vua size cho ListNode, ta ep no thanh kieu con tro (struct ListNode*) va add cho bien head.
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));

    // Khoi tao du lieu an toan va gan gia tri 0 cho head->val, va gan NULL cho head->next. Tranh cho con tro tro den vung nho khong hop le.
    head->val = 0;
    head->next = NULL;

    // Tao mot con tro current va dat bien head vao cho no. Bien current se bang gia tri dau tien cua danh sach
    struct ListNode *current = head;

    // tao bien carry de luu tru gia tri nho khi cong 2 so.
    int carry = 0;

    // Vong lap chi dung lai khi thoa 3 dieu kien: l1 khac NULL, l2 khac NULL, hoac carry khac 0. Neu ca 3 dieu kien deu khong thoa thi vong lap se dung lai.
    while (l1 != NULL || l2 != NULL || carry != 0)
    {
        // Neu l1 khong NULL thi x se bang gia tri cua l1 con lai x se bang 0. Tuong tu cho l2 va y.
        int x;
        if (l1 != NULL)
        {
            x = l1->val;
        }
        else
        {
            x = 0;
        }

        int y;
        if (l2 != NULL)
        {
            y = l2->val;
        }
        else
        {
            y = 0;
        }

        // tinh tong = gia tri nho + x + y. Sau do ta lay sum cho 10 de lay nguyen de cap nhap bien carry (gia tri nho)
        int sum = carry + x + y;
        carry = sum / 10;

        // Xin cap phat bo nho cho con tro newMode
        struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        
        // Gan gia tri val cho newNode bang sum % 10 lay phan don vi, va gan gia tri next la null la gia tri cuoi cung cua danh sach moi.  
        newNode->val = sum % 10;
        newNode->next = NULL;

        // cap nhap gia tri next cho con tro current bang con tro newNode, va cap nhap current bang gia tri tiep theo 
        current->next = newNode;
        current = current->next;

        // Neu l1 khac NULL thi cap nhap l1 bang gia tri tiep theo, tuong tu cho l2.
        if (l1 != NULL)
        {
            l1 = l1->next;
        }
        if (l2 != NULL)
        {
            l2 = l2->next;
        }
    }

    // Vong lap ket thuc, ta dung con tro result bo qua node dau tien
    struct ListNode *result = head->next;
    // Tra lai ram
    free(head);
    // Tra ve con tro result chi toi ket qua
    return result;
}