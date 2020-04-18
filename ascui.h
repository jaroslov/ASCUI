#ifndef ASCUI_H
#define ASCUI_H

#include <limits.h>

#ifdef  __cplusplus
extern   "C"
{
#endif//__cplusplus

// The user can define the content
// type for the Box, by defining
//      ASCUICON_TYPE=...
#ifdef  ASCUICON_TYPE
typedef ASCUICON_TYPE   ASCUICon;
#else// ASCUICON_TYPE
typedef void            ASCUICon;
#endif//ASCUICON_TYPE

typedef struct ASCUINit ASCUINit;
struct ASCUINit
{
    unsigned long long integral     : (sizeof(unsigned long long) * CHAR_BIT) / 2;
    unsigned long long fractional   : (sizeof(unsigned long long) * CHAR_BIT) / 2;
};
typedef struct ASCUILCv ASCUILCv;
struct ASCUILCv
{
    int             wide;
    int             size;
};
typedef struct ASCUILCv ASCUICnv;
struct ASCUICnv
{
    ASCUINit        wide;
    ASCUINit        size;
};
typedef struct ASCUIOff ASCUIOff;
struct ASCUIOff
{
    ASCUINit        top;
    ASCUINit        bot;
    ASCUINit        lft;
    ASCUINit        rgt;
};
typedef struct ASCUIGlu ASCUIGlu;
struct ASCUIGlu
{
    unsigned char   top : 1;
    unsigned char   bot : 1;
    unsigned char   lft : 1;
    unsigned char   rgt : 1;
};

typedef struct ASCUIBox ASCUIBox;
struct ASCUIBox
{
    const char     *ID;
    ASCUIBox       *parent;     // For the user's convenience.
    ASCUILcv        coord;      // Logical location of this box.
    ASCUIGlu        glue;       // Does this box glue to it's neighbors?
    ASCUILCv        size;       // What's the logical size of this box?
    ASCUILCv        expand;     // Does this box expand horiz. or vert.?
    ASCUILCv        resize;     // Does this box allow resizing?
    ASCUILCv        repeat;     // How many additional repeats are there?
    ASCUIOff        logicalsz;  // The logical size of the box with respect to its siblings & parent.

    // All of these fields are defined by the user.
    ASCUICnv        extent;     // Extent in nits after a layout.
    ASCUIOff        margin;
    ASCUIOff        padding;
    ASCUIOff        border;
    ASCUIOff        minsize;    // Do not compress the box any smaller than this.

    // A subtree is logically within a Box, but
    // is not layed out by the box. (Imagine a panning
    // canvas inside of a box.)
    ASCUIBox       *subtree;

    // This is a place for the user to put a
    // reference to their content in.
    ASCUICon       *content;

    // The child boxes of this box. The intention
    // is the user can define a single array, and
    // each parent can point in to a subrange of
    // that array.
    ASCUIBox       *begin;
    ASCUIBox       *end;
};

// Parses the given ASCUI declaration:
//  1. Returns the number of boxes found in `numBoxes`, if `numBoxes` is not NULL.
//  2. *FILLS OUT* (but does not allocate!) `boxes`, if `boxes` is not NULL.
int ascuiParse(const char* decl, int* numBoxes, ASCUIBox* boxes);

// Layout (size) the boxes in the given box-tree. The user
// is responsible for setting the size of the root box
// by filling out the 'extent' field of the root box. The
// styling information (margin, padding, border) will modify
// the layout.
int ascuiSizeBoxes(ASCUIBox* box);

#ifdef  __cplusplus
}//extern "C"
#endif//__cplusplus

#endif//ASCUI_H
