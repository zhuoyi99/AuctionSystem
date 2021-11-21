//define struct for auctions

typedef struct{
    char* name;
    unsigned duration;
    unsigned buyItNow;
    unsigned auctionID;
    char* username;
} Auction;

typedef struct{
    Auction* auction;
    Node* next;
} Node;