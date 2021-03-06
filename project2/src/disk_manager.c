#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "disk_manager.h"
#include "fileio.h"
#include "utility.h"

int file_init(struct file_manager_t* manager) {
    CHECK_TRUE(fresize(manager->fp, PAGE_SIZE));
    // zero-initialization
    struct file_header_t* file_header = &manager->file_header;
    file_header->free_page_number = 0;
    file_header->root_page_number = 0;
    file_header->number_of_pages = 0;
    // write file header
    CHECK_TRUE(fpwrite(file_header, sizeof(struct file_header_t), 0, manager->fp));
    return SUCCESS;
}

int file_create(const char* filename, struct file_manager_t* manager) {
    manager->fp = fopen(filename, "w+");
    if (manager->fp == NULL) {
        return FAILURE;
    }

    manager->updated = 0;
    return file_init(manager);
}

int file_open(const char* filename, struct file_manager_t* manager) {
    // if file exist
    if (fexist(filename)) {
        manager->fp = fopen(filename, "r+");
        if (manager->fp == NULL) {
            return FAILURE;
        }
        // read file header to cache
        manager->updated = 0;
        CHECK_TRUE(
            fread(&manager->file_header,
                  sizeof(struct file_header_t),
                  1,
                  manager->fp));
    } else {
        // create file
        return file_create(filename, manager);
    }
    return SUCCESS;
}

int file_close(struct file_manager_t* manager) {
    // write update
    file_write_update(manager);
    // close
    fclose(manager->fp);
    memset(manager, 0, sizeof(struct file_manager_t));
    return SUCCESS;
}

int file_write_header(struct file_manager_t* manager) {
    CHECK_TRUE(
        fpwrite(&manager->file_header,
                sizeof(struct file_header_t),
                0,
                manager->fp));
    return SUCCESS;
}

int file_write_update(struct file_manager_t* manager) {
    // if updated flag set
    if (manager->updated > 0) {
        manager->updated = 0;
        return file_write_header(manager);
    }
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
    // if there exists no more free page
    pagenum_t pagenum = manager->file_header.free_page_number;
    if (pagenum == 0) {
        // allocate free page
        CHECK_SUCCESS(
            page_extend_free(
                manager,
                max(1, manager->file_header.number_of_pages)));
        pagenum = manager->file_header.free_page_number;
    }

    struct page_t page;
    CHECK_SUCCESS(page_read(pagenum, manager, &page));
    // fix next free page number
    manager->file_header.free_page_number = free_page(&page)->next_page_number;
    CHECK_SUCCESS(file_write_header(manager));

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
    struct file_header_t* file_header = &manager->file_header;
    fpage->next_page_number = file_header->free_page_number;
    // write free page headers
    for (i = 1; i <= num; ++i) {
        CHECK_SUCCESS(page_write(last + i, manager, &page));
        fpage->next_page_number = last + i;
    }
    // update file header
    file_header->free_page_number = last + num;
    file_header->number_of_pages += num;
    CHECK_SUCCESS(file_write_header(manager));

    return SUCCESS;
}

int page_free(pagenum_t pagenum, struct file_manager_t* manager) {
    struct page_t page;
    CHECK_SUCCESS(page_read(pagenum, manager, &page));
    // write free page header
    free_page(&page)->next_page_number =
        manager->file_header.free_page_number;
    CHECK_SUCCESS(page_write(pagenum, manager, &page));
    // append as free page
    manager->file_header.free_page_number = pagenum;
    CHECK_SUCCESS(file_write_header(manager));
    return SUCCESS;
}

int page_read(pagenum_t pagenum,
              struct file_manager_t* manager,
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

int page_write(pagenum_t pagenum,
               struct file_manager_t* manager,
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
