/**
 * @file glbackend.h
 * @author GAMINGNOOBdev (https://github.com/GAMINGNOOBdev)
 * @brief Contains all backend hardware pixel drawing functions
 * @version 0.1
 * @date 2023-10-24
 * 
 * @copyright Copyright (c) Pradosh 2023
 */
#ifndef __OPENGL__GLBACKEND_H_
#define __OPENGL__GLBACKEND_H_ 1

#include "gl.h"
#include "glvec.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * @brief Pixel drawing function
 * 
 * @author Pradosh (pradoshgame@gmail.com) & (partially edited) GAMINGNOOBdev (https://github.com/GAMINGNOOBdev)
 * 
 * @param pixel Pixel position in screen space
 * @param color 8-bit color
 */
GLAPI void glWritePixel(uvec2 pixel, uint32_t color);

/**
 * @brief  Line drawing function
 * 
 * @author GAMINGNOOBdev (https://github.com/GAMINGNOOBdev)
 * 
 * @param p1 Line start position
 * @param p2 Line end position
 * @param col Color of the line
*/
GLAPI void glDrawLine(uvec2 p1, uvec2 p2, uint32_t col);

/**
 * @brief Triangle drawing function
 * 
 * @author GAMINGNOOBdev (https://github.com/GAMINGNOOBdev)
 * 
 * @param t0 First vertex of the triangle
 * @param t1 Second vertex of the triangle
 * @param t2 Third vertex of the triangle
 * @param col Color of the contents
 * @param fill Whether or not to fill the triangle
 */
GLAPI void glDrawTriangle(uvec2 t0, uvec2 t1, uvec2 t2, uint32_t col, bool fill);

#endif