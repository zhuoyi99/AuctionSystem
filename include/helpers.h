//define struct for auctions
#include <stdio.h>
struct Auction{
    char* name;
    unsigned duration;
    unsigned buyItNow;
    unsigned auctionID;
    char* creator;
};

typedef struct Auction Auction;

struct AuctionList{
    Auction* auction;
    struct AuctionList* next;
};
typedef struct AuctionList AuctionList;

void parseAuctions(FILE* file);
void addAuction(AuctionList* item);//add one auction item into the linked list
void displayAuctions(AuctionList* head);


typedef struct UserListNodePtr
{
    char* name;
    char* pwd;
    struct UserListNodePtr *next;
}UserListNode;


UserListNode* findUser(UserListNode* user, char* name);