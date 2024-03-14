
#include "access/nbtree.h"
#include "access/itup.h"
#include "stdint.h"



//We insert OIDs into indextupledata 
//Do extern curOID, curStamp to share variables on other files


struct umEntry{
    uint32_t oid;
    uint32_t stampLatest;
    unsigned short nold;
}
//This is an array for now as we're not sure how to do a hash table

