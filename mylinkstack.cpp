#include "mylinkstack.h"


myLinkStack::myLinkStack(){}

myLinkStack::LinkStack* myLinkStack::InitLkStack(void) {
    LinkStack* p = nullptr;
    p = new myLinkStack::LinkStack;
//    p = (LinkStack*)malloc(sizeof(LinkStack));
    if (p != nullptr)
    {
        //（1，0）入口
        p->data.d = 0;
        p->data.x = 6;
        p->data.y = 9;
        p->pNext = nullptr;
    }
    p->pNext = nullptr;
    return p;
}//建立一个带头节点的链表作为链栈

bool myLinkStack::IsEmptyLkMazeStack(LinkStack* top) {
    return (top->pNext == nullptr);
}

myLinkStack::LinkStack* myLinkStack::PushLkStack(LinkStack* top, DataType elem) {
    LinkStack* p;
    p = new myLinkStack::LinkStack;
    p->pNext = nullptr;
//    p = (LinkStack*)malloc(sizeof(LinkStack));
    p->data.x = elem.x;
    p->data.y = elem.y;
    p->data.d = elem.d;
    p->pNext = top; //p节点尾插入lkStack
    top = p;//top栈顶指针上移
    return top;
}

myLinkStack::LinkStack* myLinkStack::PushLkStack(LinkStack* top, int x, int y) {
    LinkStack* p;
    p = new myLinkStack::LinkStack;
    p->pNext = nullptr;
//    p = (LinkStack*)malloc(sizeof(LinkStack));
    p->data.x = x;
    p->data.y = y;
    p->data.d = -1;
    p->pNext = top; //p节点尾插入lkStack
    top = p;//top栈顶指针上移
    return top;
}

//出栈
myLinkStack::LinkStack* myLinkStack::PopLkStack(LinkStack* top, DataType *pData) {
    LinkStack* p;
    if (top != nullptr) {
        *pData = top->data;
        p = top;
        top = p->pNext;
        delete p;
    }
    return top;
}

myLinkStack::DataType myLinkStack::create_element(int x, int y, int dir)
{
    myLinkStack::DataType element;
    element.x = x;
    element.y = y;
    element.d = dir;//保证下一个节点推进方向
    return element;
}

void myLinkStack::destroyStack(myLinkStack::LinkStack *top)
{
    LinkStack* p;
    while (top != nullptr) {
        p = top;
        top = p->pNext;
        delete p;
    }

}
