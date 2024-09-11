#include <stdio.h>
#include <string.h>
#include "BOARD.h"
#include "LinkedList.h"

ListItem *LinkedListNew(char *data){
    ListItem *ouritem=malloc(sizeof(ListItem));
    if (ouritem==NULL){
        return ouritem;
   }else{
    ouritem->data=data;
    ouritem->nextItem=NULL;
    ouritem->previousItem=NULL;
    return ouritem;
    
   }
}


ListItem *LinkedListCreateAfter(ListItem *item, char *data){
    ListItem *ouritem=LinkedListNew(data);
    if(ouritem==NULL){
        return ouritem;
    }else if(item==NULL){
        return ouritem;
    }else if (item==NULL){
        item->nextItem=ouritem;
        ouritem->previousItem=item;
        return ouritem;  
    }else{
        ouritem->nextItem=item->nextItem;
        item->nextItem->previousItem=ouritem;
        item->nextItem=ouritem;
        ouritem->previousItem=item;
        return ouritem;
    }
   
}


char *LinkedListRemove(ListItem *item){
    ListItem *temp = item;
    if (item == NULL) {
        return NULL;
    }
    if (temp->nextItem == NULL && temp->previousItem == NULL) {
        free(item);
    }
    else {
        if (temp->nextItem == NULL) {
            temp->previousItem->nextItem = NULL;
        }
        else if (temp->previousItem == NULL) {
            temp->nextItem->previousItem = NULL;
        }
        else {
            temp->previousItem = temp->nextItem;
            temp->nextItem = temp->previousItem;
        }
        free(temp);
    }
    return temp->data;
}



int LinkedListSize(ListItem *list){
    if(list==NULL){
        return 0;
    }else{
        int scale=sizeof(list);
        return scale;
    }
}



ListItem *LinkedListGetFirst(ListItem *list){
    ListItem *value=list;
    if (value==NULL){
        return NULL;
        }else{
        while (value->previousItem != NULL){
            value=value->previousItem;
        }return value;
        }   
}

ListItem *LinkedListGetLast(ListItem *list){
    ListItem *value=list;
    if (value==NULL){
        return NULL;
    }else{
        while (value->nextItem!=NULL){
            value=value->nextItem;
        }return value;
    
        }
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem){
    char *swapdata;
    if (firstItem==NULL && secondItem==NULL){
        return STANDARD_ERROR;
        
    }else{
        swapdata=firstItem->data;
        firstItem->data= secondItem->data;
        secondItem->data=swapdata;
        return SUCCESS;
    }
}

int LinkedListPrint(ListItem *list){
    ListItem *printing=LinkedListGetFirst(list);
    if (list==NULL){
        return STANDARD_ERROR;
    }
    while (printing!=NULL){
        printf("%s", printing->data);
        printing=printing->nextItem;
    }
    return SUCCESS;
}
