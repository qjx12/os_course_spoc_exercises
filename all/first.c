#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define maxium 2048

struct struct_o {
    int value;
    int size;
    struct* pre=null;
    struct* nex=null;
};
    struct struct_o *mm;
    struct struct_o *locm;
	int key_1 = 0;
	void *posi_;
	void *block_;


void *malloc(long firstbytes) {
    void *cocl;
    void *mool;
    if(! key_1)   {
        virtual();
    }
    firstbytes = firstbytes + sizeof(struct struct_o);
    mool = 0;
    cocl = posi_;
    while(cocl != block_)
    {
        locm =
            (struct struct_o *)cocl;
        if(locm->value)
        {
            if(locm->size >= firstbytes)
            {
                locm->value = 0;
                mool = cocl;
                break;
            }
        }
        cocl = (char*)cocl + locm->size;
    }

    if(mool==0)
    {
        sbrk(firstbytes);
        mool = block_;
        block_ = (char*)block_ + firstbytes;
        locm = (struct struct_o *)mool;
        locm->value = 0;
        locm->size = firstbytes;
    }

    mool = (char*)mool + sizeof(struct struct_o);
    return mool;
 }

void virtual()//虚拟地址
{
    block_ = sbrk(0);
    posi_ = block_;
    key_1 = 1;
}

void free(void *firstbyte) {
    mm = (struct struct_o *)((char*)firstbyte - sizeof(struct struct_o));
    mm->value = 1;
    return;
}

int main(){
    virtual();
    int * first = (int*)malloc(sizeof(int));
    int * second = (int*)malloc(sizeof(int)*10);
    free(first);
    free(second);
    //printf("*");
    return 0;
}
