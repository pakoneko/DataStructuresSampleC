#include <stdio.h>
#include <stdlib.h>

struct DynArrayStack
{
    int top;
    int capacity;
    int *array;
};

struct DynArrayStack *CreateStack(){
    struct DynArrayStack *S = (struct DynArrayStack*)malloc(sizeof(struct DynArrayStack));
    if(!S)
        return NULL;
    S->capacity = 1;
    S->top = -1;
    S->array = (int*)malloc(S->capacity *sizeof(int)); //初始时数组大小为1
    if(!S->array)
        return NULL;
    return S;
}

int IsEmptyStack(struct DynArrayStack *S) {
    return (S->top == -1); //如果条件成立，则返回1，否则返回0
}

int IsFullStack(struct DynArrayStack *S) {
    //如果条件成立，则返回1，否则返回0
    return (S->top == S->capacity -1);
}

//过多的翻倍操作可能会导致内存上溢异常。
void DoubleStack(struct DynArrayStack *S){
    S->capacity *=2;
    S->array = (int*)realloc(S->array,S->capacity*sizeof(int));
}

void Push(struct DynArrayStack *S, int x){
    /*S->top == capacity -1 用来判断栈是否已满 */
    if(IsFullStack(S))
        DoubleStack(S);    
    S->array[++S->top]=x;
}

int Top(struct DynArrayStack *S){
    /*S->top == -1 用来判断栈是否为空*/
    if(IsEmptyStack(S)){
        return INT_MIN;
    }
    return S->array[S->top];
}

int Pop(struct DynArrayStack *S){
    /*S->top == -1 用来判断栈是否为空*/
    if(IsEmptyStack(S)){
        return INT_MIN;
    }
    return S->array[S->top--];
}

void DeleteStack(struct DynArrayStack *S){
    if(S){
        if(S->array)
            free(S->array);
        free(S);
    }
}