/**
 * @file ghostty/pixel.h
 * @brief Pixel extraction API for offscreen rendering
 * 
 * This API provides functions to extract rendered pixel data from ghostty surfaces
 * for use in applications that need offscreen rendering (e.g., ASCII chat).
 */

#ifndef GHOSTTY_PIXEL_H
#define GHOSTTY_PIXEL_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pixel data returned from ghostty_surface_get_pixels
 * Pixels are in BGRA format (Blue, Green, Red, Alpha) for GPU compatibility
 */
typedef struct {
    /** BGRA pixel data, allocated by ghostty - must be freed with ghostty_free_pixels */
    uint8_t *pixels;
    /** Width in pixels */
    uint32_t width;
    /** Height in pixels */
    uint32_t height;
    /** Pitch (bytes per row) - may be larger than width*4 due to alignment */
    uint32_t pitch;
} ghostty_pixel_data_t;

/**
 * Get rendered pixel data from a surface
 * 
 * This reads back the current rendered frame as BGRA pixels.
 * Only works on Linux/offscreen surfaces; macOS Metal surfaces not supported.
 * 
 * @param surface The ghostty surface
 * @return Pixel data, or data with pixels=NULL on error
 */
ghostty_pixel_data_t ghostty_surface_get_pixels(ghostty_surface_t surface);

/**
 * Free pixel data allocated by ghostty_surface_get_pixels
 */
void ghostty_free_pixels(ghostty_pixel_data_t *data);

#ifdef __cplusplus
}
#endif

#endif /* GHOSTTY_PIXEL_H */
