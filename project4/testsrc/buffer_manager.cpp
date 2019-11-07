#include "buffer_manager.hpp"
#include "test.hpp"

struct BufferTest {
    static int page_test();
    static int start_end_test();
    static int init_test();
    static int load_test();
    static int new_page_test();
    static int link_neighbor_test();
    static int append_mru_test();
    static int release_test();
};

struct UbufferTest {
    static int page_test();
    static int reload_test();
    static int check_test();
    static int safe_pagenum_test();
};

struct BufferManagerTest {
    static int constructor_test();
    static int destructor_test();
    static int shutdown_test();
    static int buffering_test();
    static int new_page_test();
    static int free_page_test();
    static int alloc_test();
    static int load_test();
    static int release_block_test();
    static int release_file_test();
    static int release_test();
    static int find_test();
};

TEST_SUITE(UbufferTest::reload, {
    // TODO: impl test
})

TEST_SUITE(UbufferTest::check, {
    // struct buffer_t buf;
    // struct ubuffer_t ubuf;
    // struct file_manager_t file;
    // ubuf.buf = &buf;
    // buf.pagenum = 10;
    // buf.file = &file;

    // ubuf.pagenum = 10;
    // ubuf.file = &file;
    // TEST_SUCCESS(ubuffer_check(&ubuf));

    // ubuf.pagenum = 20;
    // TEST(ubuffer_check(&ubuf) == FAILURE);
})

TEST_SUITE(UbufferTest::page, {
    // struct buffer_t buf;
    // struct ubuffer_t ubuf;
    // ubuf.buf = &buf;
    // TEST(from_ubuffer(&ubuf) == from_buffer(&buf));
})

TEST_SUITE(UbufferTest::safe_pagenum, {
    // TODO
})

TEST_SUITE(BufferTest::page, {

})

TEST_SUITE(BufferTest::init, {
    // struct buffer_t buf;
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_init(&buf, 10, &manager));

    // TEST(buf.pagenum == INVALID_PAGENUM);
    // TEST(buf.is_dirty == FALSE);
    // TEST(buf.pin == 0);
    // TEST(buf.prev_use == -1);
    // TEST(buf.next_use == -1);
    // TEST(buf.block_idx == 10);
    // TEST(buf.file == NULL);
    // TEST(buf.manager == &manager);
})

TEST_SUITE(BufferTest::load, {
    // struct buffer_t buf;
    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));
    // TEST_SUCCESS(buffer_init(&buf, 10, NULL));

    // pagenum_t pagenum = page_create(&file);
    // TEST_SUCCESS(buffer_load(&buf, &file, pagenum));

    // TEST(buf.pagenum == pagenum);
    // TEST(buf.file == &file);

    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferTest::new_page, {
    // struct buffer_t buf;
    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));
    // TEST_SUCCESS(buffer_init(&buf, 10, NULL));
    // TEST_SUCCESS(buffer_new_page(&buf, &file));

    // TEST(buf.pagenum != INVALID_PAGENUM);
    // TEST(buf.file == &file);

    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferTest::link_neighbor, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // // case 0. only node
    // manager.lru = 0;
    // manager.mru = 0;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = -1;

    // TEST_SUCCESS(buffer_link_neighbor(&manager.buffers[0]));
    // TEST(manager.lru == -1);
    // TEST(manager.mru == -1);

    // // case 1. least recentrly used node
    // manager.lru = 0;
    // manager.mru = 2;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = 1;
    // manager.buffers[1].prev_use = 0;
    // manager.buffers[1].next_use = 2;

    // TEST_SUCCESS(buffer_link_neighbor(&manager.buffers[0]));
    // TEST(manager.lru == 1);
    // TEST(manager.mru == 2);
    // TEST(manager.buffers[1].prev_use == -1);
    // TEST(manager.buffers[1].next_use == 2);

    // // case 2. most recently used node
    // manager.lru = 2;
    // manager.mru = 0;
    // manager.buffers[0].prev_use = 1;
    // manager.buffers[0].next_use = -1;
    // manager.buffers[1].prev_use = 2;
    // manager.buffers[1].next_use = 0;

    // TEST_SUCCESS(buffer_link_neighbor(&manager.buffers[0]));
    // TEST(manager.mru == 1);
    // TEST(manager.lru == 2);
    // TEST(manager.buffers[1].next_use == -1);
    // TEST(manager.buffers[1].prev_use == 2);

    // // case 3. middle node
    // manager.lru = 0;
    // manager.mru = 2;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = 1;
    // manager.buffers[1].prev_use = 0;
    // manager.buffers[1].next_use = 2;
    // manager.buffers[2].prev_use = 1;
    // manager.buffers[2].next_use = -1;

    // TEST_SUCCESS(buffer_link_neighbor(&manager.buffers[1]));
    // TEST(manager.mru == 2);
    // TEST(manager.lru == 0);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == 2);
    // TEST(manager.buffers[2].prev_use == 0);
    // TEST(manager.buffers[2].next_use == -1);

    // // case 4. unconnected node
    // // undefined behaviour

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
})

TEST_SUITE(BufferTest::append_mru, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // // case 1. first node
    // manager.lru = -1;
    // manager.mru = -1;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[1].next_use = -1;
    // TEST_SUCCESS(buffer_append_mru(&manager.buffers[0], FALSE));

    // TEST(manager.lru == 0);
    // TEST(manager.mru == 0);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == -1);

    // // case 2. append
    // manager.lru = 0;
    // manager.mru = 1;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = 1;
    // manager.buffers[1].prev_use = 0;
    // manager.buffers[1].next_use = -1;
    // TEST_SUCCESS(buffer_append_mru(&manager.buffers[2], FALSE));

    // TEST(manager.lru == 0);
    // TEST(manager.mru == 2);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == 1);
    // TEST(manager.buffers[1].prev_use == 0);
    // TEST(manager.buffers[1].next_use == 2);
    // TEST(manager.buffers[2].prev_use == 1);
    // TEST(manager.buffers[2].next_use == -1);

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
})

TEST_SUITE(BufferTest::release, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct buffer_t* target = &manager.buffers[1];

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));
    // TEST_SUCCESS(buffer_init(target, 1, &manager));
    // TEST_SUCCESS(buffer_load(target, &file, FILE_HEADER_PAGENUM));

    // // case 1. not dirty
    // manager.num_buffer = 3;
    // manager.lru = 0;
    // manager.mru = 2;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = 1;
    // manager.buffers[1].prev_use = 0;
    // manager.buffers[1].next_use = 2;
    // manager.buffers[2].prev_use = 1;
    // manager.buffers[2].next_use = -1;

    // TEST_SUCCESS(buffer_release(target));
    // // linkage
    // TEST(manager.lru == 0);
    // TEST(manager.mru == 2);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == 2);
    // TEST(manager.buffers[2].prev_use == 0);
    // TEST(manager.buffers[2].next_use == -1);
    // // block info
    // TEST(manager.buffers[1].prev_use == -1);
    // TEST(manager.buffers[1].next_use == -1);
    // TEST(manager.buffers[1].block_idx == 1);
    // TEST(manager.buffers[1].manager == &manager);
    // // file check
    // TEST_SUCCESS(buffer_load(target, &file, FILE_HEADER_PAGENUM));
    // TEST(file_header(from_buffer(target))->free_page_number == 0);
    // TEST(file_header(from_buffer(target))->root_page_number == INVALID_PAGENUM);
    // TEST(file_header(from_buffer(target))->number_of_pages == 0);

    // // case 2. dirty
    // struct ubuffer_t ubuffer;
    // ubuffer.buf = target;
    // ubuffer.pagenum = target->pagenum;
    // ubuffer.file = target->file;
    // BUFFER(ubuffer, WRITE_FLAG, {
    //     file_header(from_ubuffer(&ubuffer))->root_page_number = 1;
    //     file_header(from_ubuffer(&ubuffer))->number_of_pages = 20;
    // })

    // manager.num_buffer = 3;
    // manager.lru = 0;
    // manager.mru = 2;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = 1;
    // manager.buffers[1].prev_use = 0;
    // manager.buffers[1].next_use = 2;
    // manager.buffers[2].prev_use = 1;
    // manager.buffers[2].next_use = -1;

    // TEST_SUCCESS(buffer_release(target));
    // // linkage
    // TEST(manager.lru == 0);
    // TEST(manager.mru == 2);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == 2);
    // TEST(manager.buffers[2].prev_use == 0);
    // TEST(manager.buffers[2].next_use == -1);
    // // block info
    // TEST(manager.buffers[1].prev_use == -1);
    // TEST(manager.buffers[1].next_use == -1);
    // TEST(manager.buffers[1].block_idx == 1);
    // TEST(manager.buffers[1].manager == &manager);
    // // file check
    // TEST_SUCCESS(buffer_load(target, &file, FILE_HEADER_PAGENUM));
    // TEST(file_header(from_buffer(target))->free_page_number == 0);
    // TEST(file_header(from_buffer(target))->root_page_number == 1);
    // TEST(file_header(from_buffer(target))->number_of_pages == 20);

    // TEST_SUCCESS(file_close(&file));
    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // remove("testfile");
})

TEST_SUITE(BufferTest::start_end, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // manager.num_buffer = 3;
    // manager.lru = 0;
    // manager.mru = 2;
    // manager.buffers[0].prev_use = -1;
    // manager.buffers[0].next_use = 1;
    // manager.buffers[1].prev_use = 0;
    // manager.buffers[1].next_use = 2;
    // manager.buffers[2].prev_use = 1;
    // manager.buffers[2].next_use = -1;

    // struct buffer_t* target = &manager.buffers[1];

    // TEST_SUCCESS(buffer_start(target, READ_FLAG));
    // TEST(target->pin == 1);

    // TEST_SUCCESS(buffer_end(target, READ_FLAG));
    // TEST(target->pin == 0);
    // TEST(target->next_use == -1);
    // TEST(target->prev_use == 2);
    // TEST(manager.lru == 0);
    // TEST(manager.mru == 1);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == 2);
    // TEST(manager.buffers[2].prev_use == 0);
    // TEST(manager.buffers[2].next_use == 1);

    // target = &manager.buffers[2];
    // TEST_SUCCESS(buffer_start(target, WRITE_FLAG));
    // TEST(target->pin == -1);

    // TEST_SUCCESS(buffer_end(target, WRITE_FLAG));
    // TEST(target->pin == 0);
    // TEST(target->next_use == -1);
    // TEST(target->prev_use == 1);
    // TEST(manager.lru == 0);
    // TEST(manager.mru == 2);
    // TEST(manager.buffers[0].prev_use == -1);
    // TEST(manager.buffers[0].next_use == 1);
    // TEST(manager.buffers[1].prev_use == 0);
    // TEST(manager.buffers[1].next_use == 2);

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
})

TEST_SUITE(BufferManagerTest::constructor, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // TEST(manager.capacity == 5);
    // TEST(manager.num_buffer == 0);
    // TEST(manager.lru == -1);
    // TEST(manager.mru == -1);
    // TEST(manager.buffers != NULL);

    // int i;
    // for (i = 0; i < 5; ++i) {
    //     TEST(manager.buffers[i].file == NULL);
    // }

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
})

TEST_SUITE(BufferManagerTest::shutdown, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int i;
    // for (i = 0; i < 3; ++i) {
    //     buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM);
    // }

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // TEST(manager.num_buffer == 0);
    // TEST(manager.capacity == 0);
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::alloc, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;

    // int i;
    // for (i = 0; i < 13; ++i) {
    //     TEST(i % 5 == buffer_manager_alloc(&manager));
    //     manager.buffers[i % 5].file = &file;
    //     manager.buffers[i % 5].is_dirty = FALSE;
    //     TEST_SUCCESS(buffer_append_mru(&manager.buffers[i % 5], FALSE));
    // }

    // for (i = 0; i < 5; ++i) {
    //     manager.buffers[i].file = NULL;
    // }
    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
})

TEST_SUITE(BufferManagerTest::load, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int idx = buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM);
    // TEST(idx == 0);
    // TEST(manager.num_buffer == 1);
    // TEST(manager.mru == 0);
    // TEST(manager.lru == 0);

    // struct buffer_t* buffer = &manager.buffers[idx];
    // TEST(buffer->block_idx == 0);
    // TEST(buffer->prev_use == -1);
    // TEST(buffer->next_use == -1);
    // TEST(buffer->pagenum == FILE_HEADER_PAGENUM);

    // idx = buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM);
    // TEST(idx == 1);
    // TEST(manager.num_buffer == 2);
    // TEST(manager.mru == 1);
    // TEST(manager.lru == 0);
    // TEST(buffer->prev_use == -1);
    // TEST(buffer->next_use == 1);

    // buffer = &manager.buffers[idx];
    // TEST(buffer->block_idx == 1);
    // TEST(buffer->prev_use == 0);
    // TEST(buffer->next_use == -1);

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::release_block, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int idx = buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM);
    // TEST(idx == 0);

    // idx = buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM);
    // TEST(idx == 1);

    // TEST_SUCCESS(buffer_manager_release_block(&manager, 1));
    // TEST(manager.num_buffer == 1);
    // TEST(manager.lru == 0);
    // TEST(manager.mru == 0);
    // TEST(manager.buffers[0].next_use == -1);
    // TEST(manager.buffers[0].prev_use == -1);

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::release_file, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file1;
    // struct file_manager_t file2;
    // TEST_SUCCESS(file_open(&file1, "testfile"));
    // TEST_SUCCESS(file_open(&file2, "testfile2"));

    // TEST(0 == buffer_manager_load(&manager, &file1, FILE_HEADER_PAGENUM));

    // TEST(1 == buffer_manager_load(&manager, &file2, FILE_HEADER_PAGENUM));
    // TEST(2 == buffer_manager_load(&manager, &file2, FILE_HEADER_PAGENUM));

    // TEST_SUCCESS(buffer_manager_release_file(&manager, file2.id));
    // TEST(manager.num_buffer == 1);
    // TEST(manager.buffers[0].file == &file1);
    // TEST(manager.buffers[1].file == NULL);
    // TEST(manager.buffers[2].file == NULL);

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file1));
    // TEST_SUCCESS(file_close(&file2));
    // remove("testfile");
    // remove("testfile2");
})

TEST_SUITE(BufferManagerTest::release, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int i;
    // for (i = 0; i < 4; ++i) {
    //     TEST(-1 != buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM));
    // }
    // TEST(manager.lru == 0);

    // // case 1. lru
    // // 0 -> 1 -> 2 -> 3
    // TEST(0 == buffer_manager_release(&manager, &RELEASE_LRU));
    // TEST(manager.lru == 1);
    // TEST(manager.buffers[1].next_use == 2);

    // // case 2. lru is pinned
    // // 1 -> 2 -> 3
    // manager.buffers[1].pin++;
    // TEST(2 == buffer_manager_release(&manager, &RELEASE_LRU));
    // TEST(manager.lru == 1);

    // // case 3. mru
    // // 1 -> 3 -> 0 
    // manager.buffers[3].pin++;
    // TEST(0 == buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM));
    // TEST(0 == buffer_manager_release(&manager, &RELEASE_LRU));
    // TEST(manager.lru == 1);

    // // case 1. mru
    // // 1 -> 3 -> 0
    // manager.buffers[1].pin = 0;
    // manager.buffers[3].pin = 0;
    // TEST(0 == buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM));
    // TEST(0 == buffer_manager_release(&manager, &RELEASE_MRU));

    // // case 2. mru is pinned
    // // 1 -> 3 -> 0
    // TEST(0 == buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM));
    // manager.buffers[0].pin++;

    // TEST(3 == buffer_manager_release(&manager, &RELEASE_MRU));

    // // case 3. lru
    // // 1 -> 0 -> 2
    // TEST(2 == buffer_manager_load(&manager, &file, FILE_HEADER_PAGENUM));
    // manager.buffers[2].pin++;

    // TEST(1 == buffer_manager_release(&manager, &RELEASE_MRU));

    // manager.buffers[0].pin = 0;
    // manager.buffers[2].pin = 0;

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::find, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int i;
    // pagenum_t pagenum[3];
    // for (i = 0; i < 3; ++i) {
    //     pagenum[i] = page_create(&file);
    //     TEST(pagenum != INVALID_PAGENUM);
    //     TEST(i == buffer_manager_load(&manager, &file, pagenum[i]));
    // }

    // for (i = 0; i < 3; ++i) {
    //     TEST(i == buffer_manager_find(&manager, file.id, pagenum[i]));
    // }

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::buffering, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int i;
    // pagenum_t pagenum[10];
    // struct ubuffer_t ubuf;
    // for (i = 0; i < 10; ++i) {
    //     pagenum[i] = page_create(&file);
    //     TEST(pagenum != INVALID_PAGENUM);

    //     ubuf = buffer_manager_buffering(&manager, &file, pagenum[i]);
    //     TEST(ubuf.pagenum == ubuf.buf->pagenum);
    //     TEST(ubuf.file == ubuf.buf->file);
    //     TEST(pagenum[i] == ubuf.buf->pagenum);
    //     TEST(&manager.buffers[i % 5] == ubuf.buf);
    // }

    // for (i = 9; i >= 5; --i) {
    //     ubuf = buffer_manager_buffering(&manager, &file, pagenum[i]);
    //     TEST(ubuf.pagenum == ubuf.buf->pagenum);
    //     TEST(ubuf.file == ubuf.buf->file);
    //     TEST(pagenum[i] == ubuf.buf->pagenum);
    //     TEST(&manager.buffers[i % 5] == ubuf.buf);
    // }

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::new_page, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // int i;
    // struct ubuffer_t ubuf;
    // for (i = 0; i < 13; ++i) {
    //     ubuf = buffer_manager_new_page(&manager, &file);
    //     TEST(&manager.buffers[i % 5] == ubuf.buf);
    // }
    
    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

TEST_SUITE(BufferManagerTest::free_page, {
    // struct buffer_manager_t manager;
    // TEST_SUCCESS(buffer_manager_init(&manager, 5));

    // struct file_manager_t file;
    // TEST_SUCCESS(file_open(&file, "testfile"));

    // struct ubuffer_t ubuf = buffer_manager_new_page(&manager, &file);
    // TEST_SUCCESS(buffer_manager_free_page(&manager, &file, ubuf.buf->pagenum));

    // TEST_SUCCESS(buffer_manager_shutdown(&manager));
    // TEST_SUCCESS(file_close(&file));
    // remove("testfile");
})

int buffer_manager_test() {
    return UbufferTest::reload_test()
        && UbufferTest::check_test()
        && UbufferTest::page_test()
        && UbufferTest::safe_pagenum_test()
        && BufferTest::page_test()
        && BufferTest::init_test()
        && BufferTest::load_test()
        && BufferTest::new_page_test()
        && BufferTest::link_neighbor_test()
        && BufferTest::append_mru_test()
        && BufferTest::release_test()
        && BufferTest::start_end_test()
        && BufferManagerTest::constructor_test()
        && BufferManagerTest::shutdown_test()
        && BufferManagerTest::alloc_test()
        && BufferManagerTest::load_test()
        && BufferManagerTest::release_block_test()
        && BufferManagerTest::release_file_test()
        && BufferManagerTest::release_test()
        && BufferManagerTest::find_test()
        && BufferManagerTest::buffering_test()
        && BufferManagerTest::new_page_test()
        && BufferManagerTest::free_page_test();
}
