/*-------------------------- FILE PROLOGUE --------------------------*/
/******************************************************************
 * COPYRIGHT:
 *   2022
 *   SAVIC
 *   All Rights Reserved
 *
 * FILE NAME:
 *   color.h
 *
 * DESCRIPTION:
 *   Graphics used color
 *
 * Create Date:
 *   2022-02-21
 *
 ******************************************************************/
#ifndef _COLOR_H_
#define _COLOR_H_

/*------------------------- FILE INCLUSION --------------------------*/
/* ----------------------- MACRO DEFINITIONS ------------------------*/
#define COLORTABLENUM 45

/* ----------------------- TYPE DECLARATIONS ------------------------*/
typedef enum
{
    BLACK = 0,
    WHITE = 1,
    LIGHT_GREY = 2,
    MEDIUM_GREY = 3,
    DARK_GREY = 4,
    MAGENTA = 7,
    BLUE = 9,
    CYAN = 11,
    GREEN = 14,
    YELLOW = 16,
    BROWN = 18,
    EMPTY_COLOR = 19,
    RED = 20,
    DARKGREYSEMI_TRANSPARENT = 25,
    CYANSEMI_TRANSPARENT = 32,
    LIGHT_DARK = 44,
} COLORS;

/*------------------------- VARIABLE DECLARATIONS --------------------*/

extern float colorTable[COLORTABLENUM][4];
/* ---------------------- FUNCTION DECLARATIONS -----------------------*/

#endif /* _COLOR_H_ */
