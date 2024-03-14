#include "updatememo.h"
#define INITIALMEMOSIZE 1000


uint32_t curStamp = 0;
uint32_t curOID = 0;



//if update memo reaches max
umEntry **updateMemo;
int curMemoEntry = 0;
int curMemoSize = 0;


void initializeMemo(){
    updateMemo = malloc(INITIALMEMOSIZE * sizeof(umEntry *));
    
}

//add a new entry to update memo
void addToMemo(uint32_t oid, uint32_t stamp, unsigned short nold){
    umEntry * newUM = malloc(sizeof(umEntry));
    newUM->oid = oid;
    newUM->stamp = stamp;
    newUM->nold = nold;
    //check if memo is full
    if(curMemoSize == curMemoEntry ){
        curMemoSize = curMemoSize * 2;
        umEntry **newUM = malloc(sizeof(umEntry *) * curMemoSize);
        for (int i = 0; i < curMemoSize; i++){
            newUM[i] = updateMemo[i];
        }
        free(updateMemo);
        updateMemo = newUM;
    }
    updateMemo[curMemoEntry] = newUM;
}
//return um entry with oid. return null if not found. 
umEntry * findEntry(uint32_t oid){
    for (int i = 0; i < curMemoEntry; i++)
    {
        if(updateMemo[i]->oid == oid){
            return updateMemo[i];
        }
    }
    return NULL;
}
//call in order to update an entry. Called when update occurs, as we need to update the stampcounter
bool updateEntry(uint32_t newStamp, uint32_t oid){
    //loop through update memo to find same one
    

}