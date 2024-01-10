#include "pgm.h"
#include <stdlib.h>
#include <string.h>

// (SPECIFICATIONS FOR FUNCTIONS ARE IN pgm.h !!)

// Physical memory is 2^24 (0x1000000 OR 16777216) bytes, with 2^12 (4096) physical pages.

static const int physical_page_count = 4096;  // Number of physical pages.
static const int physical_page_size = 4096;   // Size of each page.

static char physmem[4096*4096];  // Storage for physical memory.

// Virtual addresses are 22 bits, 10 bits for page number, 12 bits for offset in page.
// The macros PAGE(n) and OFFSET(n) extract the page number and the offset within the
// page from a virtual address.

#define PHYS_ADDR(phys_page, offset) (((phys_page) << 12) + (offset))
#define OFFSET(n) ((n) & 0xFFF)
#define PAGE(n) ( ((n) >> 12) & 0x3FF )

struct page_table {
    char* page_entries[1024];  // Array of page entries, each pointing to a physical page
};

void pgm_init() {
    // Initialize the physical memory with zeros
    for (int i = 0; i < physical_page_count * physical_page_size; i++) {
        physmem[i] = 0;
    }
}


struct page_table* pgm_create() {
    struct page_table* pgtab = (struct page_table*) malloc(sizeof(struct page_table));
    if (pgtab != NULL) {
        // Initialize the page table with NULL page entries
        for (int i = 0; i < 1024; i++) {
            pgtab->page_entries[i] = NULL;
        }
    }
    return pgtab;
}


void pgm_discard(struct page_table* pgtab) {
    if (pgtab != NULL) {
        // Free the page table and all its associated physical pages
        for (int i = 0; i < 1024; i++) {
            if (pgtab->page_entries[i] != NULL) {
                free(pgtab->page_entries[i]);
            }
        }
        free(pgtab);
    }
}


int pgm_put(struct page_table* pgtab, int start_address, void* data_source, int byte_count) {
    if (pgtab == NULL || data_source == NULL || start_address < 0 || start_address + byte_count > (1 << 22)) {
        return -1;  // Invalid arguments
    }

    int start_page = PAGE(start_address);
    int offset = OFFSET(start_address);
    int end_page = PAGE(start_address + byte_count - 1);
    int total_bytes_written = 0;

    for (int page = start_page; page <= end_page; page++) {
        if (pgtab->page_entries[page] == NULL) {
            // Allocate a new physical page if the page entry is empty
            pgtab->page_entries[page] = (char*) malloc(physical_page_size);
            if (pgtab->page_entries[page] == NULL) {
                // Failed to allocate memory
                return total_bytes_written;
            }
        }

        // Copy data from data_source to physical memory
        int bytes_to_write = physical_page_size - offset;
        if (bytes_to_write > byte_count - total_bytes_written) {
            bytes_to_write = byte_count - total_bytes_written;
        }
        memcpy(pgtab->page_entries[page] + offset, (char*) data_source + total_bytes_written,bytes_to_write);
            // Update variables for next iteration
    total_bytes_written += bytes_to_write;
    offset = 0;
}

return total_bytes_written;
}

int pgm_get(struct page_table* pgtab, int start_address, void* data_destination, int byte_count) {
if (pgtab == NULL || data_destination == NULL || start_address < 0 || start_address + byte_count > (1 << 22)) {
return -1; // Invalid arguments
}
int start_page = PAGE(start_address);
int offset = OFFSET(start_address);
int end_page = PAGE(start_address + byte_count - 1);
int total_bytes_read = 0;

for (int page = start_page; page <= end_page; page++) {
    if (pgtab->page_entries[page] == NULL) {
        // Page not found in page table, return error
        return total_bytes_read;
    }

    // Copy data from physical memory to data_destination
    int bytes_to_read = physical_page_size - offset;
    if (bytes_to_read > byte_count - total_bytes_read) {
        bytes_to_read = byte_count - total_bytes_read;
    }
    memcpy((char*) data_destination + total_bytes_read, pgtab->page_entries[page] + offset, bytes_to_read);

    // Update variables for next iteration
    total_bytes_read += bytes_to_read;
    offset = 0;
}

return total_bytes_read;

}

int pgm_put_int(struct page_table* pgtab, int address, int value) {
return pgm_put(pgtab, address, &value, sizeof(int));
}

int pgm_get_int(struct page_table* pgtab, int address, int* pvalue) {
return pgm_get(pgtab, address, pvalue, sizeof(int));
}

