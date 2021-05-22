#include "../Include/Loader.h"

Loader * Loader_Create(void)
{
    Loader *pSelf = (Loader*)calloc(1, sizeof(Loader));
    return pSelf;
}

void Loader_Destroy(Loader *pSelf)
{
    if (pSelf == NULL)
    {
        return;
    }

    free(pSelf);
    pSelf = NULL;
}

Status Loader_MainProcess (void) 
{
    Status status;
    uint8_t initCounter = 0;

    do 
    {
        status = SDCARD_Init();
    } while (status != OK || initCounter == 10);

    return status;
}