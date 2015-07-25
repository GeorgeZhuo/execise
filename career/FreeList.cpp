
struct mem_block {
    
    int index;
    bool is_avalible;
    mem_block *next;

    int block[1024];
    
    mem_block(int d) {
	index = d;
	is_avalible = true;
    }
};

class FreeList {
public:
    FreeList();
     ~FreeList();
    
    int search_valiable();
    void allocate(int size);
    void free();

private:
    mem_block *list_tail;
    mem_block *list_top;
    int size;
    int current_valiable;
};

FreeList::FreeList():size(10), current_valiable(0){
    
    mem_block *new_block = new mem_block(0);
    new_block->next = NULL;
    list_top = list_tail = new_block;
    for (int i = 1; i < 10; ++i) {
	mem_block *new_block = new mem_block(i);
	new_block->next = NULL;
	tail->next = new_block;
	tail = new_block;
    }
}

~FreeList::FreeList() {

    mem_block *top, *cur;
    
    while (top->next != NULL) {
	cur = top;
	top = top->next;
	delete cur;
    }
}
void* FreeList::allocate() {
        
    if (current_valiable != -1) {
	int temp = search_valiable();
	int count = current_valiable;
	current_valiable = temp;

	mem_block *cur;
	cur = list_top;
	while (count--) {
	    cur = cur->next;
	}
	
	return cur;
    } else {

	mem_block *new_block = new mem_block(list_tail->index + 1);
	new_block->next = NULL;
	
	tail->next = new_block;
	tail = new_block;
	tail->avaliable = false;
	
	return new_block;
	  
    }
}

void FreeList:: free(void *free_block) {

    mem_block *cur, *top;
    cur = top = list_top;
    
    while (cur->next != NULL) {
	if (cur->index == free_block->index) {
	    cur->is_avalible = true;
	}
    }
}

int FreeList::search_valiable() {

    mem_block *top = list_top;
    while (top->next != NULL) {
	if (top->avaliable == true) {
	    return top->index;
	    
	}
	top = top->next;
    }
    
    return -1;
}
