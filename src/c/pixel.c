/**
 * @file src/c/pixel.c
 * @brief Pixel extraction implementation for offscreen rendering
 */

#include "../include/ghostty/pixel.h"
#include <stdlib.h>
#include <string.h>

/**
 * Stub implementation for pixel extraction
 * TODO: Implement actual pixel readback based on rendering backend
 */
ghostty_pixel_data_t ghostty_surface_get_pixels(ghostty_surface_t surface) {
    ghostty_pixel_data_t result = {
        .pixels = NULL,
        .width = 0,
        .height = 0,
        .pitch = 0,
    };
    
    // TODO: Implement platform-specific pixel extraction:
    // - On Linux/OpenGL: Use glReadPixels or glGetTexImage
    // - On Linux/Vulkan: Use vkCmdCopyImageToBuffer
    // - On macOS/Metal: Use synchronizeTexture + getBytes (already available)
    //
    // For now, return NULL to indicate not implemented
    
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
