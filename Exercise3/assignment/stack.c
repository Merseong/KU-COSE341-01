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
        int ref_str[20] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 7 };
        for (int i = 0; i < 20; ++i)
        {
            ref_arr[i] = ref_str[i];
        }
    }

    return ref_arr;
}

typedef struct DLL_node
{
    int frame;
    struct DLL_node* next;
    struct DLL_node* prev;
} Node;


int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz) {
    //int i, j;
    int page_faults = 0;
    
    // Initializing frames -> not used, use only stack with DDL
    //int* frames = (int*) malloc(sizeof(int) * frame_sz);
    //for (i=0; i<frame_sz; i++) frames[i] = -1;

    // TODO
    // Initalizing Nodes for stack
    int node_count = 0;
    Node* top = NULL;
    Node* bottom = NULL;

    // Start reference
    char is_fault = 0;
    for (int i = 0; i < ref_arr_sz; ++i)
    {
        int new_ref = ref_arr[i];
        is_fault = 0;

        // Search from top to bottom
        Node* search = top;
        while (search != NULL)
        {
            if (search->frame != new_ref)
            {
                search = search->next;
            }
            else
            {
                break;
            }
        }
        
        if (search != NULL)
        { // if exist (hit), bring it to top
            Node* s_prev = search->prev;
            Node* s_next = search->next;
            if (s_prev != NULL)
            {
                s_prev->next = s_next;
            }
            if (s_next != NULL)
            {
                s_next->prev = s_prev;
            }
            search->next = top;
            top->prev = search;
            top = search;
            bottom = top;
            while (bottom->next != NULL)
            {
                bottom = bottom->next;
            }
        }
        else
        { // else (not exist, fault), create new node / replace bottom node to new_ref, bring it to top
            is_fault = 1;
            if (node_count < frame_sz)
            {
                Node* new_node = (Node*) malloc(sizeof(Node));
                new_node->next = top;
                new_node->prev = NULL;
                new_node->frame = new_ref;
                if (top != NULL)
                {
                    top->prev = new_node;
                }
                if (bottom == NULL)
                {
                    bottom = new_node;
                }

                top = new_node;
                ++node_count;
            }
            else
            {
                Node* victim = bottom;
                bottom = victim->prev;
                bottom->next = NULL;
                victim->next = top;
                victim->prev = NULL;
                victim->frame = new_ref;
                top->prev = victim;
                top = victim;
            }
            ++page_faults;
        }

        // Print progress
        search = top;
        printf("%d | ", new_ref);
        for (int j = 0; j < frame_sz; ++j)
        {
            if (search != NULL)
            {
                printf("%d ", search->frame);
                search = search->next;
            }
            else
            {
                printf(". ");
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

    // Free used Nodes
    while (top != NULL)
    {
        Node* to_remove = top;
        top = top->next;
        free(to_remove);
    }

    return page_faults;
}

