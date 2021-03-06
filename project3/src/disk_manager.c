#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "disk_manager.h"
#include "fileio.h"
#include "utility.h"

filenum_t create_filenum(const char* filename) {
    char c;
    unsigned long hash = 0;
    while ((c = *filename++)) {
        if (c == '/' || c == '\\') {
            hash = 0;
            continue;
        }
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return (tablenum_t)hash;
}

int file_init(struct file_manager_t* manager) {
    CHECK_TRUE(fresize(manager->fp, PAGE_SIZE));
    // zero-initialization
    struct file_header_t file_header;
    file_header.free_page_number = 0;
    file_header.root_page_number = 0;
    file_header.number_of_pages = 0;
    // write file header
    CHECK_TRUE(fpwrite(&file_header, sizeof(struct file_header_t), 0, manager->fp));
    return SUCCESS;
}

int file_create(struct file_manager_t* manager, const char* filename) {
    manager->fp = fopen(filename, "w+");
    CHECK_NULL(manager->fp);

    manager->id = create_filenum(filename);
    return file_init(manager);
}

int file_open(struct file_manager_t* manager, const char* filename) {
    // if file exist
    if (fexist(filename)) {
        manager->fp = fopen(filename, "r+");
        CHECK_NULL(manager->fp);

        manager->id = create_filenum(filename);
    } else {
        // create file
        CHECK_SUCCESS(file_create(manager, filename));
    }
    return SUCCESS;
}

int file_close(struct file_manager_t* manager) {
    // close
    fclose(manager->fp);
    memset(manager, 0, sizeof(struct file_manager_t));
    return SUCCESS;
}

int file_read_header(struct file_manager_t* manager, struct file_header_t* header) {
    // read header page
    struct padded_file_header_t padded_header;
    CHECK_TRUE(
        fpread(
            header,
            sizeof(struct file_header_t),
            FILE_HEADER_PAGENUM * PAGE_SIZE,
            manager->fp));
    return SUCCESS;
}

int file_write_header(struct file_manager_t* manager, struct file_header_t* header) {
    // write header page
    CHECK_TRUE(
        fpwrite(
            header,
            sizeof(struct file_header_t),
            FILE_HEADER_PAGENUM * PAGE_SIZE,
            manager->fp));
    return SUCCESS;
}

pagenum_t last_pagenum(struct file_manager_t* manager) {
    long size = fsize(manager->fp);
    return last_pagenum_from_size(size);
}

pagenum_t last_pagenum_from_size(long size) {
    return size / PAGE_SIZE - 1;
}

pagenum_t page_create(struct file_manager_t* manager) {
    // read file header
    struct file_header_t header;
    EXIT_ON_FAILURE(file_read_header(manager, &header));

    // if there exists no more free page
    pagenum_t pagenum = header.free_page_number;
    if (pagenum == 0) {
        // allocate free page
        EXIT_ON_FAILURE(
            page_extend_free(
                manager,
                max(1, header.number_of_pages)));

        EXIT_ON_FAILURE(file_read_header(manager, &header));
        pagenum = header.free_page_number;
    }
    // read free page
    struct page_t page;
    EXIT_ON_FAILURE(page_read(manager, pagenum, &page));
    // fix next free page number
    header.free_page_number = free_page(&page)->next_page_number;
    EXIT_ON_FAILURE(file_write_header(manager, &header));

    return pagenum;
}

int page_init(struct page_t* page, uint32_t leaf) {
    // zero-initialization
    struct page_header_t* header = page_header(page);
    header->is_leaf = leaf;
    header->number_of_keys = 0;
    header->parent_page_number = INVALID_PAGENUM;
    header->special_page_number = INVALID_PAGENUM;
    return SUCCESS;
}

int page_extend_free(struct file_manager_t* manager, int num) {
    if (num < 1) {
        return FAILURE;
    }

    long size = fsize(manager->fp);
    pagenum_t last = last_pagenum_from_size(size);
    // resize file
    CHECK_TRUE(fresize(manager->fp, size + num * PAGE_SIZE));

    int i;
    struct page_t page;
    struct free_page_t* fpage = free_page(&page);

    // read file header
    struct file_header_t header;
    CHECK_SUCCESS(file_read_header(manager, &header));
    fpage->next_page_number = header.free_page_number;

    // write free page headers
    for (i = 1; i <= num; ++i) {
        CHECK_SUCCESS(page_write(manager, last + i, &page));
        fpage->next_page_number = last + i;
    }

    // update file header
    header.free_page_number = last + num;
    header.number_of_pages += num;
    CHECK_SUCCESS(file_write_header(manager, &header));

    return SUCCESS;
}

int page_free(struct file_manager_t* manager, pagenum_t pagenum) {
    // read page
    struct page_t page;
    CHECK_SUCCESS(page_read(manager, pagenum, &page));
    // read file header
    struct file_header_t header;
    CHECK_SUCCESS(file_read_header(manager, &header));
    // write free page header
    free_page(&page)->next_page_number = header.free_page_number;
    CHECK_SUCCESS(page_write(manager, pagenum, &page));
    // append as free page
    header.free_page_number = pagenum;
    CHECK_SUCCESS(file_write_header(manager, &header));
    return SUCCESS;
}

int page_read(struct file_manager_t* manager,
              pagenum_t pagenum,
              struct page_t* dst)
{
    CHECK_TRUE(
        fpread(
            dst,
            sizeof(struct page_t),
            pagenum * PAGE_SIZE,
            manager->fp));
    return SUCCESS;
}

int page_write(struct file_manager_t* manager,
               pagenum_t pagenum,
               struct page_t* src)
{
    CHECK_TRUE(
        fpwrite(
            src,
            sizeof(struct page_t),
            pagenum * PAGE_SIZE,
            manager->fp));
    return SUCCESS;
}
