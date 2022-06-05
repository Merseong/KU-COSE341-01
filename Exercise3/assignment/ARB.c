#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz);

// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(int argc, char** argv) {
    if (argc < 4) return -1;
    
    int ref_arr_sz = atoi(argv[1]); // 50~100
    int page_max = atoi(argv[2]);   // 5~10
    int frame_sz = atoi(argv[3]);   // 1~6

    int* ref = generate_ref_arr(ref_arr_sz, page_max);
    if (ref_arr_sz <= 0) ref_arr_sz = 20; // on case of Reference String S

    /* for check ref array
    for (int i = 0; i < 20; ++i)
    {
        printf("%d ", ref[i]);
    }
    printf("\n"); 
    */

    int page_faults = lru(ref, ref_arr_sz, frame_sz);
    printf("%d\n", page_faults);
    free(ref);

    return 0;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * (sz > 0 ? sz : 20));

    // TODO :: Generate Random Refernece String
    if (sz > 0) // Generate random
    {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < sz; ++i)
        {
            ref_arr[i] = rand() % (page_max + 1);
            if (i != 0 && ref_arr[i - 1] == ref_arr[i])
            {
                --i;
            }
        }
    }
    else // Load Reference String S
    {
        int ref_str[20] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1 };
        for (int i = 0; i < 20; ++i)
        {
            ref_arr[i] = ref_str[i];
        }
    }

    return ref_arr;
}

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz) {
    int i, j;
    int page_faults = 0;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = -1;

    // TODO
    // Init ARB queue
    unsigned char* arb_queue = malloc(sizeof(char) * frame_sz);
    for (i = 0; i < frame_sz; ++i) arb_queue[i] = 0;

    for (i = 0; i < ref_arr_sz; ++i)
    {
        char is_fault = 1;
        for (j = 0; j < frame_sz; ++j)
        {
            if (frames[j] == ref_arr[i])
            {
                is_fault = 0;
                break;
            }
        }

        if (is_fault)
        {
            int victim = 0;
            for (j = 0; j < frame_sz; ++j)
            {
                if (arb_queue[j] < arb_queue[victim])
                {
                    victim = j;
                }
            }
            frames[victim] = ref_arr[i];
            arb_queue[victim] = 1 << 7;

            ++page_faults;
        }
        else
        {
            arb_queue[j] += 1 << 7;
        }

        for (j = 0; j < frame_sz; ++j)
        {
            //printf("%u ", arb_queue[j]);
            arb_queue[j] = arb_queue[j] >> 1;
        }

        printf("%d | ", ref_arr[i]);
        for (j = 0; j < frame_sz; ++j)
        {
            if (frames[j] < 0)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", frames[j]);
            }
        }
        if (is_fault)
        {
            printf("(fault)\n");
        }
        else
        {
            printf("\n");
        }
    }

    return page_faults;
}

