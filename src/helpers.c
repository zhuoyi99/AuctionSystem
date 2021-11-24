#include "../include/helpers.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

AuctionList* p = NULL;
AuctionList* head = NULL;

/*
This function prefills the server with auction items.

*/
void parseAuctions(FILE* file){
    AuctionList* temp = (AuctionList*)malloc(sizeof(AuctionList));//create a node
    temp->auction = NULL;
    temp->next = NULL;

    Auction* auction = (Auction*)malloc(sizeof(Auction));

    //char *buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    char buffer[BUFFER_SIZE];
    int counter = 0;
    while(fgets(buffer,BUFFER_SIZE,file)){
        if(strcmp(buffer,"\n")==0){
            counter =0;           
            temp = (AuctionList*)malloc(sizeof(AuctionList));//create a node in linked list
            temp->auction = NULL;
            temp->next = NULL;
            auction = (Auction*)malloc(sizeof(Auction));
            continue;
        }
        
        
        counter +=1;
        if(counter == 1){                       
            //char nameBuffer[BUFFER_SIZE];
            //strcpy(nameBuffer,buffer);

            char* myName = malloc(sizeof(strlen(buffer)));//item name is diffrent so it has its own space on the heap
            strcpy(myName,buffer);
            auction->name = myName;
            //strcpy(auction->name, buffer)                                          ;
            //printf("name of the aunctio is %s\n", auction->name);
        }
        if(counter == 2){
            auction->duration = atoi(buffer);
            //printf("duration of the aunctio is %d\n", auction->duration);
        }
        if(counter == 3){
            auction->buyItNow = atoi(buffer);
            //printf("buyitnow of the aunctio is %d\n", auction->buyItNow);
            
            temp->auction = auction;
            addAuction(temp);
            //displayAuctions(head);
            
        }
        
    }
   
}

void addAuction(AuctionList* item){
    if(head == NULL){
        head = item;
    }
    else{
        p = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = item;

    }

    //printf("name is %s", item->auction->name);
    return;
}

void displayAuctions(AuctionList* head){
    AuctionList* p = head;

    printf("The name of the item is %s\n",p->auction->name);
    printf("The duration of the item is %d\n",p->auction->duration);
    printf("The buyitnow of the item is %d\n",p->auction->buyItNow);
    while(p->next != NULL){
    
        p = p->next;
        printf("The name of the item is %s\n",p->auction->name);
        printf("The duration of the item is %d\n",p->auction->duration);
        printf("The buyitnow of the item is %d\n",p->auction->buyItNow);
        
    }
   
}