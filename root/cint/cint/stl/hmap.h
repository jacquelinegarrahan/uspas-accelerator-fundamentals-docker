/* -*- C++ -*- */

/************************************************************************
 *
 * Copyright(c) 1995~2006  Masaharu Goto (cint@pcroot.cern.ch)
 *
 * For the licensing terms see the file COPYING
 *
 ************************************************************************/

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef HMAP_H
#define HMAP_H

#ifdef MAP_H
#undef MAP_H
#undef TREE_H
#define __MAP_WAS_DEFINED
#endif

#define Allocator huge_allocator
#define map huge_map
#define rb_tree huge_rb_tree
#include <hugalloc.h>
#include <map.h>

#undef MAP_H
#undef TREE_H

#ifdef __MAP_WAS_DEFINED
#define MAP_H
#define TREE_H
#undef  __MAP_WAS_DEFINED
#endif

#undef Allocator
#undef map
#undef rb_tree

#endif