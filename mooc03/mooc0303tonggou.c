//树的同构练习题：给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换，就变成T2，则我们称两棵树是“同构”的。
//现给定两棵树，请你判断它们是否是同构的。
//解题思路：1，二叉树表示2，建立二叉树3，同构判断
// 1,二叉树表示：首先输入二叉树结点个数，依次输入第i个结点，包括结点数据，左右孩子结点编号，输入-表示孩子结点不存在
// 2，建立二叉树：采用静态链表结构，由结点组成数组，每个结点存储数据和左右孩子结点的编号。若某个序号均不与左右孩子序号相符，则该节点为根节点。
//  若想调用该二叉树，需要知道其根结点序号Root1，Root2。
// 3,判别同构，分为以下几种情况：
//  结点为空：1，两个结点都为空，同构；2，一个结点为空，一个结点非空，不同构；
//  结点都不空：3，两个结点值不相同，不同构；4，结点值相同，左孩子都为空，递归判断右孩子；
//      5，结点值相同，左孩子都不空，且左孩子的值相等，递归判断其左孩子同构，其右孩子同构；6，情况5的补充，递归判断其左右孩子与对应右左孩子是否同构。

#include <stdio.h>
#include <stdlib.h>
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode
{
    ElementType Data;
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree];
int BuildTree(struct TreeNode T[MaxTree]); //获取输入数据，并建立二叉树
int Isomorphic(int Root1, int Root2);      //判断二叉树是否同构，是则返回1，否则返回0.
int main(void)
{
    Tree Root1, Root2;
    Root1 = BuildTree(T1);
    Root2 = BuildTree(T2);
    if (Isomorphic(Root1, Root2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
int BuildTree(struct TreeNode T[MaxTree])
{
    int N, i, Root, check[MaxTree];
    char cl, cr;
    scanf("%d", &N);
    printf("N=%d\n", N);
    // getchar();
    if (N)
    {
        for (i = 0; i < N; i++)
        {
            check[i] = 0;
        }
        for (i = 0; i < N; i++)
        {
            scanf(" %c %c %c", &T[i].Data, &cl, &cr); //在格式字符串中，将空格放到%c前面，scanf()便会跳过空格，从第一个非空白字符开始读取。

            if (cl != '-') //若左子树存在，记录左子树序号，并将对应位置check值记为1；
            {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else //若左子树不存在，将左子树序号记为Null=-1；
                T[i].Left = Null;
            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else
                T[i].Right = Null;
            printf("Data=%c,cl=%d,cr=%d\n", T[i].Data, T[i].Left, T[i].Right);
        }
        for (i = 0; i < N; i++)
        {
            if (!check[i])
            {
                Root = i;
                break;
            }
        }
    }
    else
        Root = Null; //根节点为空
    printf("Root:%d\n", Root);
    return Root;
}
int Isomorphic(int Root1, int Root2)
{ //判别同构，分为以下几种情况：
    //结点为空：1，两个结点都为空，同构；2，一个结点为空，一个结点非空，不同构；
    //结点都不空：3，两个结点值不相同，不同构；4，结点值相同，左孩子都为空，递归判断右孩子；
    // 5，结点值相同，左孩子都不空，且左孩子的值相等，递归判断其左孩子同构，其右孩子同构；
    // 6，情况5的补充，递归判断其左右孩子与对应右左孩子是否同构。
    if ((Root1 == Null) && (Root2 == Null))
        return 1;
    if (((Root1 == Null) && (Root2 != Null)) || ((Root1 != Null) && (Root2 == Null)))
        return 0;
    if (T1[Root1].Data != T2[Root2].Data)
        return 0;
    if ((T1[Root1].Left == Null) && (T2[Root2].Left == Null))
        return Isomorphic(T1[Root1].Right, T2[Root2].Right);
    if ((T1[Root1].Right == Null) && (T2[Root2].Right == Null))
        return Isomorphic(T1[Root1].Left, T2[Root2].Left);
    if (((T1[Root1].Left != Null) && (T2[Root2].Left != Null)) && ((T1[T1[Root1].Left].Data) == (T2[T2[Root2].Left].Data)))
        return (Isomorphic(T1[Root1].Left, T2[Root2].Left) && Isomorphic(T1[Root1].Right, T2[Root2].Right));
    else
        return (Isomorphic(T1[Root1].Left, T2[Root2].Right) && Isomorphic(T1[Root1].Right, T2[Root2].Left));
}
//测试用例：
// 8
// A 1 2
// B 3 4
// C 5 -
// D - -
// E 6 -
// G 7 -
// F - -
// H - -
// 8
// G - 4
// B 7 6
// F - -
// A 5 1
// H - -
// C 0 -
// D - -
// E 2 -
// 结果：Yes