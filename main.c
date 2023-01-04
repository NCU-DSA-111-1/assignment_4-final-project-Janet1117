#include "function.h"

int main()
{
    int testdraw;
    int i = 0;
    node *test;
    node *testinput;
    test = (node *)malloc(sizeof(node));
    testinput = (node *)malloc(sizeof(node));
    test->color = red;
    test->name = seven;
    test->next = NULL;
    node *tmp;
    tmp = test;

    while(i < 10)
    {
        printf("enter color and number:");
        scanf("%d %d", &testinput->color, &testinput->name);
        test = ruleandrenewpokerpile(test, testinput, &testdraw);
        printf("%d %d %d\n\n", test->color, test->name, testdraw);
        i++;
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d %d \n", tmp->color, tmp->name);
        tmp = tmp->next;
    }


    return 0;
}