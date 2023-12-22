/**
 * @file gdt.h
 * @author Pradosh (pradoshgame@gmail.com)
 * @brief Headers for GDT
 * @version 0.1
 * @date 2023-12-17
 * 
 * @copyright Copyright (c) Pradosh 2023
 * 
 */
#include <basics.h>

// Define a GDT entry structure
struct gdt_entry {
    int16 limit_low;
    int16 base_low;
    int8 base_middle;
    int8 access;
    int8 granularity;
    int8 base_high;
};

// Define a GDT pointer structure
struct gdt_pointer {
    int16 limit;
    int64 base;
};