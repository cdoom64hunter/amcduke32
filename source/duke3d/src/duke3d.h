//-------------------------------------------------------------------------
/*
Copyright (C) 2016 EDuke32 developers and contributors

This file is part of EDuke32.

EDuke32 is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

#ifndef duke3d_h_
#define duke3d_h_

// JBF
#include "a.h"
#include "baselayer.h"
#include "build.h"
#include "cache1d.h"
#include "compat.h"
#include "fx_man.h"
#include "keyboard.h"
#include "pragmas.h"

#ifdef POLYMER
    #include "polymer.h"
#else
#ifdef USE_OPENGL
    #include "polymost.h"
#endif
#endif


#define HEAD2                   APPNAME

#ifdef EDUKE32_STANDALONE
    #define VOLUMEALL           (1)
    #define PLUTOPAK            (1)
    #define WORLDTOUR           (0)
    #define VOLUMEONE           (0)
#else
    #define VOLUMEALL           (g_Shareware == 0)
    #define PLUTOPAK            (g_scriptVersion >= 14)
    #define WORLDTOUR           (DUKE && g_scriptVersion >= 16)
    #define VOLUMEONE           (g_Shareware == 1)
#endif

// increase by 3, because atomic GRP adds 1, and Shareware adds 2
#define BYTEVERSION_EDUKE32      348

//#define BYTEVERSION_13      27
//#define BYTEVERSION_14      116
//#define BYTEVERSION_15      117
#define BYTEVERSION         (BYTEVERSION_EDUKE32+(PLUTOPAK?1:(VOLUMEONE<<1)))

#define NUMPAGES            1

#define RECSYNCBUFSIZ       2520   //2520 is the (LCM of 1-8)*3
#define MOVEFIFOSIZ         2

#define MAXVOLUMES          8
#define MAXLEVELS           64
#define MAXGAMETYPES        16
#define MAX_ACTIVE_VIEWSCREENS 64

enum {
    MUS_FIRST_SPECIAL = MAXVOLUMES*MAXLEVELS,

    MUS_INTRO = MUS_FIRST_SPECIAL,
    MUS_BRIEFING = MUS_FIRST_SPECIAL + 1,
    MUS_LOADING = MUS_FIRST_SPECIAL + 2,
    MUS_USERMAP = MUS_FIRST_SPECIAL + 3,
};

////////// TIMING CONSTANTS //////////
// The number of 'totalclock' increments per second:
#define TICRATE             120
// The number of game state updates per second:
#define REALGAMETICSPERSEC  30
// The number of 'totalclock' increments per game state update:
// NOTE: calling a game state update a 'frame' is really weird.
// (This used to be TICRATE/GAMETICSPERSEC, which was 120/26 = 4.615~ truncated
// to 4 by integer division.)
#define TICSPERFRAME        (TICRATE/REALGAMETICSPERSEC)
// Used as a constant to satisfy all of the calculations written with ticrate =
// 26 in mind:
#define GAMETICSPERSEC      26


#define PACKBUF_SIZE        32768

#define TILE_SAVESHOT       (MAXTILES-1)
#define TILE_LOADSHOT       (MAXTILES-3)
#define TILE_TILT           (MAXTILES-2)
#define TILE_ANIM           (MAXTILES-4)
#define TILE_VIEWSCR        (MAXTILES-5)
// Reserved: TILE_VIEWSCR_1 (MAXTILES-6)
// Reserved: TILE_VIEWSCR_2 (MAXTILES-7)
// Reserved: (MAXTILES-8) to (MAXTILES-196) for additional Viewscreen tilespace
EDUKE32_STATIC_ASSERT(4 + (3 * MAX_ACTIVE_VIEWSCREENS) <= MAXTILES-MAXUSERTILES);

// sprites with these statnums should be considered for fixing
#define ROTFIXSPR_STATNUMP(k) ((k)==STAT_DEFAULT || (k)==STAT_STANDABLE || (k)==STAT_FX || \
                            (k)==STAT_FALLER || (k)==STAT_LIGHT)
#define ROTFIXSPR_MAGIC 0x18190000

// JBF 20040604: sync is a function on some platforms
#define sync                dsync

#define WT_WIDE(x) (WORLDTOUR ? (x ## WIDE) : (x))

// Uncomment the following to remove calls to a.nasm functions with the GL renderers
// so that debugging with valgrind --smc-check=none is possible:
//#define DEBUG_VALGRIND_NO_SMC

enum loguru_verbosities_game
{
    LOG_VM = LOG_ENGINE_MAX,
    LOG_CON,
    LOG_GAME_MAX,
};

#include "_rts.h"
#include "actors.h"
#include "common_game.h"
#include "config.h"
#include "control.h"
#include "dnames.h"
#include "function.h"
#include "game.h"
#include "gamedef.h"
#include "gamedefs.h"
#include "gameexec.h"
#include "gamevars.h"
#include "global.h"
#include "inv.h"
#include "macros.h"
#include "music.h"
#include "network.h"
#include "player.h"
#include "quotes.h"
#include "rts.h"
#include "sector.h"
#include "sounds.h"
#include "text.h"

static inline int32_t G_TileHasActor(uint16_t const tileNum)
{
    return g_tile[tileNum].execPtr!=NULL;
}

static inline int32_t G_DefaultActorHealthForTile(uint16_t const tileNum)
{
    return G_TileHasActor(tileNum) ? g_tile[tileNum].execPtr[0] : 0;
}

#endif
