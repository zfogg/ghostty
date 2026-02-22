/**
 * @file src/c/pixel.c
 * @brief Pixel extraction implementation for offscreen rendering
 */

#include "../include/ghostty/pixel.h"
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <GL/gl.h>
#endif

/**
 * Extract rendered pixels using platform-specific rendering API
 *
 * On Linux: Uses OpenGL glReadPixels to read back the framebuffer
 * On macOS: Uses Metal texture readback (handled separately)
 */
ghostty_pixel_data_t ghostty_surface_get_pixels(ghostty_surface_t surface) {
    ghostty_pixel_data_t result = {
        .pixels = NULL,
        .width = 0,
        .height = 0,
        .pitch = 0,
    };

    // Note: This function requires the surface to be in a valid rendering state
    // The actual implementation depends on the graphics backend being used

#ifdef __linux__
    // Linux: Use OpenGL pixel readback
    // Get current framebuffer size from OpenGL
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    result.width = (uint32_t)viewport[2];
    result.height = (uint32_t)viewport[3];

    if (result.width == 0 || result.height == 0) {
        return result;
    }

    // Each row must be aligned to 4 bytes in OpenGL
    result.pitch = ((result.width * 4 + 3) / 4) * 4;

    // Allocate buffer for BGRA pixel data
    size_t buffer_size = result.pitch * result.height;
    result.pixels = (uint8_t *)malloc(buffer_size);

    if (!result.pixels) {
        result.width = 0;
        result.height = 0;
        result.pitch = 0;
        return result;
    }

    // Read pixels from the currently bound framebuffer
    // GL_BGRA format matches GPU output directly (faster than RGB conversion)
    // GL_UNSIGNED_BYTE for 8-bit per channel
    glReadPixels(
        0, 0,
        result.width, result.height,
        GL_BGRA,
        GL_UNSIGNED_BYTE,
        result.pixels
    );

    // Check for GL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        free(result.pixels);
        result.pixels = NULL;
        result.width = 0;
        result.height = 0;
        result.pitch = 0;
    }
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
