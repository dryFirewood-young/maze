#ifndef MYLINKSTACK_H
#define MYLINKSTACK_H


class myLinkStack
{
public:
    myLinkStack();

    typedef struct {
        int x; //表示节点的横坐标
        int y;//表示节点的纵坐标
        int d;//表示节点的方向
    }DataType;

    typedef struct linknode {
        DataType data;
        struct linknode* pNext;
    }LinkStack;

    LinkStack* InitLkStack(void);


    bool IsEmptyLkMazeStack(LinkStack* top);

    LinkStack* PushLkStack(LinkStack* top, DataType elem);

    LinkStack* PushLkStack(LinkStack* top, int x, int y);

    //出栈
    LinkStack* PopLkStack(LinkStack* top, DataType *pData) ;

    DataType create_element(int x, int y, int dir);

    void destroyStack(LinkStack* top);
};






#endif // MYLINKSTACK_H
