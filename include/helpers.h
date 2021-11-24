//define struct for auctions
#include <stdio.h>
struct Auction{
    char* name;
    unsigned duration;
    unsigned buyItNow;
    unsigned auctionID;
    char* username;
};

typedef struct Auction Auction;

struct AuctionList{
    Auction* auction;
    struct AuctionList* next;
};

typedef struct AuctionList AuctionList;

void parseAuctions(FILE* file);
void addAuction(AuctionList* item);
void displayAuctions(AuctionList* head);