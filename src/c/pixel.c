/**
 * @file src/c/pixel.c
 * @brief Pixel extraction implementation for offscreen rendering
 */

#include "../include/ghostty/pixel.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Forward declare the Zig implementations
// These are provided by the OpenGL renderer in Zig
typedef struct {
    uint8_t *pixels;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
} zig_pixel_data_t;

// Zig functions (implemented in OpenGL.zig)
extern zig_pixel_data_t opengl_get_pixels(void);
extern void opengl_free_pixels(zig_pixel_data_t data);

/**
 * Extract rendered pixels using platform-specific rendering API
 *
 * On Linux: Calls Zig implementation which uses OpenGL glReadPixels
 * On macOS: Uses Metal texture readback (handled separately)
 */
ghostty_pixel_data_t ghostty_surface_get_pixels(ghostty_surface_t surface) {
    ghostty_pixel_data_t result = {
        .pixels = NULL,
        .width = 0,
        .height = 0,
        .pitch = 0,
    };

    (void)surface;

#ifdef __linux__
    // Linux: Use OpenGL pixel readback via Zig implementation
    zig_pixel_data_t zig_data = opengl_get_pixels();

    result.pixels = zig_data.pixels;
    result.width = zig_data.width;
    result.height = zig_data.height;
    result.pitch = zig_data.pitch;
#else
    // Other platforms: Not implemented yet
    // macOS: Metal surfaces handled separately in Zig code
    // Windows: Would need DirectX implementation
#endif

    return result;
}

void ghostty_free_pixels(ghostty_pixel_data_t *data) {
    if (data && data->pixels) {
        free(data->pixels);
        data->pixels = NULL;
        data->width = 0;
        data->height = 0;
        data->pitch = 0;
    }
}
