#include "../include/helpers.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

Auction* auction = NULL;
AuctionList* next = NULL;

void parseAuctions(FILE* file){
    
    AuctionList* auctionList = (AuctionList*)malloc(sizeof(AuctionList));//create a link
    auctionList->auction = NULL;
    auctionList->next = NULL;

   
    auctionList->auction = (Auction*)malloc(sizeof(Auction));

    char *buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    int counter = 0;
    while(fgets(buffer,BUFFER_SIZE,file)){
        if(strcmp(buffer,"\n")==0){
            counter =0;
            auction = (Auction*)malloc(sizeof(Auction));
            
            continue;
        }
        
        counter +=1;
        if(counter == 1){
            auction->name = buffer;
            printf("name of the aunctio is %s\n", auction->name);
        }
        if(counter == 2){
            auction->duration = atoi(buffer);
            printf("duration of the aunctio is %s\n", auction->name);
        }
        if(counter == 3){
            auction->buyItNow = atoi(buffer);
            printf("buyitnow of the aunctio is %s\n", auction->name);
        }
    }
}