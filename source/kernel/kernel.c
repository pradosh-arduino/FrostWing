/**
 * @file kernel.c
 * @author Pradosh (pradoshgame@gmail.com)
 * @brief The Main kernel file, everything starts from here
 * @version 0.1
 * @date 2023-10-21
 * 
 * @copyright Copyright (c) Pradosh 2023
 * 
 */
#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <memory.h>
#include <strings.h>
#include <kernel.h>
#include <flanterm/flanterm.h>
#include <fb.h>
#include <hal.h>
#include <acpi.h>
#include <graphics.h>

// #define assert(expression) if(!(expression))error("")

extern int typescript_main(void);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

static volatile struct limine_hhdm_request hhdm_req = {
    LIMINE_HHDM_REQUEST, 0, NULL
};

struct flanterm_context *ft_ctx = NULL;
struct limine_framebuffer *framebuffer = NULL;

/**
 * @brief The main kernel function
 * renaming main() to something else, make sure to change the linker script accordingly.
 */
void main(void) {
     if (framebuffer_request.response == NULL) {
        hcf();
    }
    // Fetch the first framebuffer.
    framebuffer = framebuffer_request.response->framebuffers[0];

    ft_ctx = flanterm_fb_simple_init(
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch
    );

    if(framebuffer_request.response->framebuffer_count < 1){
        warn("Multiple framebuffers detected! Using Framebuffer[0] (You probably have 2 monitors)");
    }
    gdt_init();
    acpi_init();
    for (size_t i = 0; i < 10000000; i++) inb(0x80);
    load_typescript();
    probe_pci();
    initialize_heap();

    int* data = (int*)allocate(sizeof(int));
    if (data) {
        *data = 42;
    }

    // line, empty triangle and filled triangle testing (leaving it here to demonstrate how to use these functions)
    // draw_line((ivec2){0, 0}, (ivec2){10, 30}, 0xffbaddad);
    // draw_triangle((ivec2){10, 10}, (ivec2){100, 100}, (ivec2){100, 10}, 0xffdadbad, false);
    // draw_triangle((ivec2){110, 110}, (ivec2){200, 200}, (ivec2){200, 110}, 0xffdadbad, true);

    // Free memory
    deallocate(data);
    get_cpu_name();
    print_cpu();
    L1_cache_size();
    L2_cache_size();
    L3_cache_size();
    init_rtc();
    display_time();
    // We have no more process to handle.
    hcf(); // Doing this to avoid Reboot
}

/**
 * @brief The basic print function.
 * 
 * @param msg The message to be printed
 */
void print(const char* msg){
    flanterm_write(ft_ctx, msg, strlen_(msg));
}

/**
 * @brief ACPI Shutdown code.
 * 
 */
void shutdown(){
    acpi_shutdown_hack(hhdm_req.response->offset, acpi_find_sdt, inb, inw, outb, outw);
}