/*哈夫曼树：带权路径长度WPL最小的二叉树*/
/*建立方法：首先将所有元素建立一个完全二叉树，采用顺序存储，Elements每个元素采用哈夫曼结点的结构，一个Element包含权值Weight，左右哈夫曼子树默认为NULL*/
/*将完全二叉树建立为最小堆;每次删除两个最小堆堆顶元素，设计一个新哈夫曼结点指向这两个堆顶元素，并计算新哈夫曼结点的权重，将新哈弗曼结点插入最小堆中*/
/*一共要做H->Size-1次合并，最后最小堆只剩一个堆顶元素，删除最小堆操作返回一个哈夫曼树的根节点指针*/
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#define ElementType HuffmanTree /*最小堆元素采用哈夫曼结点指针的结构*/
#define MaxData 1000 //哨兵元素应大于或小于堆中所有可能的元素
#define MinData -10  //哨兵元素应大于或小于堆中所有可能的元素
#define ERROR -1     /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */
// 01堆的存储表示:因为堆为完全二叉树结构，故可以使用顺序存储结构来表示。
typedef struct HeapStruct *HeapTree;
typedef HeapTree MaxHeap; /* 最大堆 */
typedef HeapTree MinHeap; /* 最小堆 */
struct HeapStruct
{
    ElementType *Elements; /*Elements每个元素采用哈夫曼结点的结构，一个Element包含权值Weight，左右哈夫曼子树默认为NULL*/
    int Size;              //堆当前元素的个数
    int Capacity;          //堆的最大容量
};

/*哈夫曼树存储定义*/
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int Weight;
    HuffmanTree Left, Right;
};

/*堆的函数声明*/
int IsFull(HeapTree H); //判断堆是否满，满堆返回1
int IsEmpty(HeapTree H); //判断堆是否空，空堆返回1
HeapTree CreateHeapMin(int Maxsize) ;//02创建最小堆,容量为Maxsize的空堆
void InsertMin(HeapTree H, ElementType item); // 03最小堆的插入:将元素item插入到最大堆H中，其中哨兵为H->ElementType[0]
ElementType DeleteMin(HeapTree H); //04最小堆的删除:从最小堆H中取出键值最小的元素，并删除该结点
void PercDownMin(HeapTree H, int p);/*建造最小堆-下滤*/
void BuildHeapMin(HeapTree H);/*建造最小堆*/

/*哈夫曼树函数声明*/
HuffmanTree Huffman(MinHeap H);/*根据输入的最小堆H,建立一个哈夫曼树,并返回哈夫曼树根结点T*/

HuffmanTree Huffman(MinHeap H)
{ /*H是一个完全二叉树，假设H->size个权值已经存放在H->Elements[]->Weight里*/
    int i;
    HuffmanTree T;
    BuildMinHeap(H); /*将H->Elements[]按权值调整为最小堆*/
    for(i=1;i<H->Size;i++)
    {/*做H->Size-1次合并*/
        T=(HuffmanTree)malloc(sizeof(struct TreeNode));
        T->Left=DeleteMin(H);
        /*从最小堆中删除一个结点，作为新T的右子结点*/
        T->Right=DeleteMin(H);
        /*从最小堆中删除一个结点，作为新T的右子结点*/
        T->Weight=T->Left->Weight+T->Right->Weight;
        /*计算新权值*/
        Insert(H,T);/*将新T插入到最小堆*/
    }
    T=DeletMin(H);
    return T;
}

/*堆的实现函数*/
int IsFull(HeapTree H) //判断堆是否满，满堆返回1
{
    return (H->Size == H->Capacity);
}
int IsEmpty(HeapTree H) //判断堆是否空，空堆返回1
{
    return (H->Size == 0);
}
// 02创建最小堆
HeapTree CreateHeapMin(int Maxsize) //创建容量为Maxsize的空堆
{
    HeapTree H = (HeapTree)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType )malloc(sizeof(ElementType) * (Maxsize + 1));
    H->Size = 0;
    H->Capacity = Maxsize;
    H->Elements[0]->Weight = MinData; //定义哨兵
    return H;
}
// 03最小堆的插入
void InsertMin(HeapTree H, ElementType item) //将元素item插入到最大堆H中，其中哨兵为H->ElementType[0]
{
    int i;
    if (IsFull(H))
    {
        printf("堆已满\n");
        return;
    }
    i = ++H->Size;
    for (; H->Elements[i / 2]->Weight > item; i = i / 2)
    {
        H->Elements[i] = H->Elements[i / 2]; //向下过滤比插入值小的结点
    }
    H->Elements[i] = item; // item的插入位置
}
// 04最小堆的删除
ElementType DeleteMin(HeapTree H) //从最小堆H中取出键值最小的元素，并删除该结点
{                                 //方法：用最小堆中的最后一个元素，从根结点从上到下过滤元素
    int Parent, Child;
    ElementType Minitem, temp;
    if (IsEmpty(H))
    {
        printf("最小堆为空\n");
        return ERROR;
    }
    Minitem = H->Elements[1];
    /* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
    temp = H->Elements[H->Size--];                          /* 注意当前堆的规模要减小 */
    for (Parent = 1; 2 * Parent <= H->Size; Parent = Child) // 2*Parent<=Size是为了确保它有孩子结点，以继续进行比较。
    {
        Child = 2 * Parent;
        if ((Child != H->Size) && (H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight)) //找出左右孩子中较小那个
        {
            Child++; /* Child指向左右子结点的较小者 */
        }
        if (temp <= H->Elements[Child]->Weight) //不用继续往下比较了，可能到了末尾结点或者该子树的元素都比item要大。
            break;
        else /* 下滤X */
        {
            H->Elements[Parent] = H->Elements[Child];
        }
    }
    H->Elements[Parent] = temp;
    return Minitem;
}
//05建立最小堆：建立一个完全二叉树，从最后一个有儿子的父结点开始逐个往前建堆，将每一个子堆都调整为最小堆，调的方法与删除堆顶元素的方法类似
//此方法相较于逐个元素插入的方法，可以降低时间复杂度，NlogN->N
/*----------- 建造最小堆 -----------*/
void PercDownMin(HeapTree H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最小堆 */
    int Parent, Child;
    ElementType X;

    X = H->Elements[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight))
            Child++; /* Child指向左右子结点的较小者 */
        if (X->Weight <= H->Elements[Child]->Weight)/* 找到了合适位置 */
            break; 
        else       /* 下滤X */
            H->Elements[Parent] = H->Elements[Child];
    }
    H->Elements[Parent] = X;
}
void BuildHeapMin(HeapTree H)
{ /* 调整H->Elements[]中的元素，使满足最小堆的有序性  */
    /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
    int i;
    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->Size / 2; i > 0; i--)
        PercDownMin(H, i);
}