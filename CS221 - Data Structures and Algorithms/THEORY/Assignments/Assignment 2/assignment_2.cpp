#include <iostream>
using namespace std;

struct SuperBlock {
    int Blockid;
    int startIndex;
    int sizeOfMemoryBlock;
    string data;
    SuperBlock* next; // A pointer to the next superblock in the linked list

     SuperBlock(int start, int sz) 
        : Blockid(0), startIndex(start), sizeOfMemoryBlock(sz), data(""), next(nullptr) {}

};

// Global memory pool - accessible to all functions
char memoryPool[64]; 

// Global variables for management
SuperBlock* head = NULL;  // Head of linked list
SuperBlock* tail = NULL;
int nextBlockId = 1;         // For generating unique BlockIds

 void initializeMemoryPool() {
        // Each building block represents one character.
        for (int i = 0; i < 64; i++) {
          memoryPool[i] = 'E';
        }
        // At the beginning, all blocks will be marked as 'E' for empty.
    }

    // There is a size of the memory block, and initially the size of the memory block is 64, which is initialized.

int findAvailableBlock(int size) {
    int currentStart = -1;  // Track start of current free sequence
    int currentLength = 0;  // Track length of current free sequence
    
    for (int i = 0; i < 64; i++) {
        if (memoryPool[i] == 'E') {
            // If this is the start of a new free sequence
            if (currentStart == -1) {
                currentStart = i;  // Mark the start
            }
            currentLength++;  // Increase the length of current sequence
            
            // Check if we've found a large enough block
            if (currentLength >= size) {
                return currentStart;  // Return the start of this sequence
            }
        } else {
            // Hit an occupied block - reset our search
            currentStart = -1;
            currentLength = 0;
        }
    }
    
    // If we finish the loop without finding a block
    return -1;
}

SuperBlock* Append(int startIndex, int size) {
    if (tail != 0) { // if the linked list is NOT empty;
        tail->next = new SuperBlock(startIndex, size);
        tail = tail->next;
    }
    else head = tail = new SuperBlock(startIndex, size);

    tail->Blockid = nextBlockId;  // Set the Blockid

     // INCREMENT for the next block that will be created
    nextBlockId++;

    return tail;


}

SuperBlock* allocateSuperBlockForString(const std::string &str) {
     // Step 1: Calculate how many blocks needed
    int counter = 0;
    for (int i = 0; i < str.size(); i++) {
        counter++;
    }

    // Step 2: Find available space using findAvailableBlock()
    int startIndex = findAvailableBlock(counter);
    if (startIndex == -1) {
        cout << "Error: Not enough contiguous memory!" << endl;
        return nullptr;
    }

     // Step 3: "Allocate" by writing string into memoryPool
     for (int i = 0; i < counter; i++) {
        memoryPool[startIndex + i] = str[i];
     }

      // Step 4: Create SuperBlock to track this allocation
      SuperBlock* newBlock = Append(startIndex, counter);
      newBlock->data = str;

      return newBlock;
}

// Function to display the entire memory pool;
// This shows what's actually stored in each of the 64 memory blocks:
void displayMemoryPool() {
    cout << "Memory Pool:" << endl;
    cout << "Index:   ";
    for (int i = 0; i < 64; i++) {
        if (i < 10) cout << " ";  // Alignment for single-digit numbers
        cout << i << " ";
    }
    cout << endl;
    
    cout << "Data:    ";
    for (int i = 0; i < 64; i++) {
        cout << " " << memoryPool[i] << " ";
    }
    cout << endl;
}

// Function to traverse the linked list and display all the metadata of the superblock;
void DisplayLinkedList() {
    cout << "Traversing the List: " << endl;
    if (head == NULL) {
        cout << "  No allocated blocks" << endl;
        return;
    }

     SuperBlock* current = head;
    while (current != NULL) {
        int endIndex = current->startIndex + current->sizeOfMemoryBlock - 1;
        cout << "  " << current->Blockid << ": " << current->data 
             << "    Indices: (" << current->startIndex << " -> " << endIndex 
             << "), Size: " << current->sizeOfMemoryBlock << endl;
        current = current->next;
    }

}

void displayEverything() {
    cout << "****************************" << endl;
    displayMemoryPool();      // Show physical memory
    cout << endl;
    DisplayLinkedList();      // Show logical organization  
    cout << "****************************" << endl;
}

void deallocateSuperBlock(int BlockId) {
    if (head == NULL) {
        cout << "Error: Empty list - no blocks to deallocate" << endl;
        return;
    }
    
    SuperBlock* current = head;
    SuperBlock* prev = NULL;
    
    // Search for the block with matching BlockId
    while (current != NULL && current->Blockid != BlockId) {
        prev = current;
        current = current->next;
    }
    
    // If block not found
    if (current == NULL) {
        cout << "Error: BlockId " << BlockId << " not found" << endl;
        return;
    }
    
    // Get startIndex BEFORE deleting the node
    int startIndex = current->startIndex;
    int size = current->sizeOfMemoryBlock;
    
    // FREE THE MEMORY in memoryPool
    for (int i = startIndex; i < startIndex + size; i++) {
        memoryPool[i] = '_';  // or 'E' - mark as free
    }
    
    // Remove from linked list
    if (prev == NULL) {
        // Deleting the head node
        head = current->next;
        if (head == NULL) tail = NULL;  // Update tail if list becomes empty
    } else {
        // Deleting a middle or tail node
        prev->next = current->next;
        if (current == tail) tail = prev;  // Update tail if deleting last node
    }
    
    delete current;
    cout << "Memory deallocated for Super-block id: " << BlockId << endl;
}

// Function 8: Deallocating PART of a superblock
void deallocatePartOfSuperBlock(int BlockId, int partSize) {
    if (head == NULL) {
        cout << "Error: Empty list - no blocks to deallocate" << endl;
        return;
    }
    
    // Find the super-block with matching BlockId
    SuperBlock* current = head;
    while (current != NULL && current->Blockid != BlockId) {
        current = current->next;
    }
    
    // If block not found
    if (current == NULL) {
        cout << "Error: BlockId " << BlockId << " not found" << endl;
        return;
    }
    
    // Check if partSize is valid
    if (partSize <= 0) {
        cout << "Error: partSize must be positive" << endl;
        return;
    }
    
    if (partSize >= current->sizeOfMemoryBlock) {
        cout << "Error: partSize exceeds or matches super-block size. Use deallocateSuperBlock instead." << endl;
        return;
    }
    
    // Free the specified portion from start in memory pool
    int startIndex = current->startIndex;
    for (int i = startIndex; i < startIndex + partSize; i++) {
        memoryPool[i] = '_';
    }
    
    // Adjust the super-block's metadata
    current->startIndex = startIndex + partSize;
    current->sizeOfMemoryBlock = current->sizeOfMemoryBlock - partSize;
    
    // Update the data string (remove the deallocated part from the beginning)
    current->data = current->data.substr(partSize);
    
    cout << "Part of super-block deallocated: " << partSize << " blocks freed starting from index " << startIndex << endl;
}

void deallocatePartOfSuperBlockAnywhere(int BlockId, int StartIndex, int partSize) {
    if (head == NULL) {
        cout << "Error: Empty list - no blocks to deallocate" << endl;
        return;
    }
    
    // Find the super-block with matching BlockId
    SuperBlock* current = head;
    while (current != NULL && current->Blockid != BlockId) {
        current = current->next;
    }
    
    // If block not found
    if (current == NULL) {
        cout << "Error: BlockId " << BlockId << " not found" << endl;
        return;
    }
    
    // Validate deallocation bounds
    int blockStart = current->startIndex;
    int blockEnd = blockStart + current->sizeOfMemoryBlock - 1;
    int deallocStart = StartIndex;
    int deallocEnd = StartIndex + partSize - 1;
    
    // Check if deallocation is within block bounds
    if (deallocStart < blockStart || deallocEnd > blockEnd) {
        cout << "Error: Deallocation exceeds the bounds of the super-block" << endl;
        return;
    }
    
    if (partSize <= 0) {
        cout << "Error: partSize must be positive" << endl;
        return;
    }
    
    // Free the specified portion in memory pool
    for (int i = deallocStart; i <= deallocEnd; i++) {
        memoryPool[i] = '_';
    }
    
    // Handle three cases based on deallocation position
    if (deallocStart == blockStart) {
        // Case 1: Deallocation from start
        if (partSize == current->sizeOfMemoryBlock) {
            // Entire block is deallocated - remove from linked list
            deallocateSuperBlock(BlockId);
        } else {
            // Partial deallocation from start - adjust current block
            current->startIndex = deallocEnd + 1;
            current->sizeOfMemoryBlock = current->sizeOfMemoryBlock - partSize;
            current->data = current->data.substr(partSize);
        }
    } else if (deallocEnd == blockEnd) {
        // Case 2: Deallocation from end - just shrink current block
        current->sizeOfMemoryBlock = current->sizeOfMemoryBlock - partSize;
        current->data = current->data.substr(0, current->data.length() - partSize);
    } else {
        // Case 3: Deallocation from middle - split into two blocks
        int firstPartSize = deallocStart - blockStart;
        int secondPartSize = blockEnd - deallocEnd;
        
        string secondPartData = current->data.substr(deallocStart - blockStart + partSize);
        
        // Adjust current block to be the first part
        current->sizeOfMemoryBlock = firstPartSize;
        current->data = current->data.substr(0, firstPartSize);
        
        // Create new block for the second part
        int newBlockStart = deallocEnd + 1;
        
        SuperBlock* newBlock = new SuperBlock(newBlockStart, secondPartSize);
        newBlock->data = secondPartData;
        newBlock->Blockid = nextBlockId++;
        
        // Insert new block after current block in linked list
        newBlock->next = current->next;
        current->next = newBlock;
        if (tail == current) tail = newBlock;  // Update tail if needed
    }
    
    cout << "Part of super-block deallocated: " << partSize << " blocks freed starting from index " << StartIndex << endl;
}

void userMemoryManagementInterface() {
    int choice;
    string inputString;
    int blockId, partSize, startIndex;

    initializeMemoryPool();  // Initialize memory pool at start
    
    do {
        // Display menu
        cout << "\n=== Memory Management System ===" << endl;
        cout << "1. Allocate memory for a string" << endl;
        cout << "2. Deallocate entire super-block" << endl;
        cout << "3. Deallocate part from start of super-block" << endl;
        cout << "4. Deallocate part from anywhere in super-block" << endl;
        cout << "5. Display current status" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                // Allocate memory for string
                cout << "Enter string to allocate: ";
                cin.ignore(); // Clear input buffer
                getline(cin, inputString);
                allocateSuperBlockForString(inputString);
                displayEverything(); // Show updated state
                break;
                
            case 2:
                // Deallocate entire block
                cout << "Enter BlockId to deallocate entirely: ";
                cin >> blockId;
                deallocateSuperBlock(blockId);
                displayEverything(); // Show updated state
                break;
                
            case 3:
                // Deallocate part from start
                cout << "Enter BlockId: ";
                cin >> blockId;
                cout << "Enter number of blocks to deallocate from start: ";
                cin >> partSize;
                deallocatePartOfSuperBlock(blockId, partSize);
                displayEverything(); // Show updated state
                break;
                
            case 4:
                // Deallocate part from anywhere
                cout << "Enter BlockId: ";
                cin >> blockId;
                cout << "Enter start index for deallocation: ";
                cin >> startIndex;
                cout << "Enter number of blocks to deallocate: ";
                cin >> partSize;
                deallocatePartOfSuperBlockAnywhere(blockId, startIndex, partSize);
                displayEverything(); // Show updated state
                break;
                
            case 5:
                // Display current status
                displayEverything();
                break;
                
            case 6:
                cout << "Exiting Memory Management System..." << endl;
                break;
                
            default:
                cout << "Invalid choice! Please enter 1-6." << endl;
        }
        
    } while (choice != 6);
}

int main() {
    userMemoryManagementInterface();
    return 0;
}