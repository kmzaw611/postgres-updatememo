#include "updatememo.h"
#define INITIALMEMOSIZE 1000


uint32_t curStamp = 0;
uint32_t curOID = 0;



//if update memo reaches max double its size. AddToMemo should be only function that changes curMemoEntry and curMemoSize
//
umEntry **updateMemo;
int curMemoEntry = 0;
int curMemoSize = INITIALMEMOSIZE;



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
    curMemoEntr++;
}
//This function implements the UM portion of "MemoBasedInsert" from the paper. Call onInsert() in places where postgres inserts tuples
void onInsert(uint32_t oid){
    //If we are assigning the oids ourselves, then this function doesn't really work. ignoring that for now, keep in mind for later
    umEntry * entry = findEntry(oid);
    //check if oid is there. 
    if(entry){
        //fill in
    }
    else{
        //fill in
    }
}
//TRUE = LATEST
//FALSE = OBSOLETE
bool checkStatus(IndexTuple itup){
    umEntry * entry = findEntry(itup.oid);
    if(!entry){
        return true;
    }
    if(entry->stamp == itup.stamp){
        return true;
    }
    else{
        return false;
    }

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
//call in order to update an entry. Called when update occurs, as we need to update the stampcounter to the newest one
//return true if found. Return false if not. 
bool updateEntry(uint32_t newStamp, uint32_t oid){
    umEntry * toUpdate = findEntry(oid);
    if(toUpdate == NULL){
        return false;
    }
    else{
        toUpdate->stamp = newStamp;
        return true;
    }
}