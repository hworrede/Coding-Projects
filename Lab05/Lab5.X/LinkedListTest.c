#include <stdio.h>
#include <string.h>
#include "BOARD.h"
#include "LinkedList.h"

int main(){
ListItem *list;
ListItem *existItem;
ListItem *finalItem;
ListItem *newItem;


list = LinkedListNew("The First");
newItem = LinkedListCreateAfter(list,"The Second");
printf("%s", newItem->data);
newItem = LinkedListCreateAfter(list,"The Third");
printf("%s",newItem->data);

existItem = LinkedListGetFirst(list);
printf("%s", existItem->data);

finalItem = LinkedListGetFirst(list);
printf("%s", finalItem->data);

if (LinkedListSwapData(existItem, newItem)){
    printf("Successful");
    
}else{
    printf("Failed");
}
printf("%s", existItem->data);
if (LinkedListPrint(list)){
    printf("Success");
}
else{
    printf("Failed");
}
}