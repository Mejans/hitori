/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * Hitori
 * Copyright (C) Philip Withnall 2007 <philip@tecnocode.co.uk>
 * 
 * Hitori is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * 
 * Hitori is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Hitori.  If not, write to:
 * 	The Free Software Foundation, Inc.,
 * 	51 Franklin Street, Fifth Floor
 * 	Boston, MA  02110-1301, USA.
 */

#include <gtk/gtk.h>
#include <glib.h>

#ifndef HITORI_MAIN_H
#define HITORI_MAIN_H

G_BEGIN_DECLS

/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#	include <libintl.h>
#	undef _
#	define _(String) dgettext (PACKAGE, String)
#	ifdef gettext_noop
#		define N_(String) gettext_noop (String)
# 	else
#		define N_(String) (String)
#	endif
#else
#	define textdomain(String) (String)
#	define gettext(String) (String)
#	define dgettext(Domain,Message) (Message)
#	define dcgettext(Domain,Message,Type) (Message)
#	define bindtextdomain(Domain,Directory) (Domain)
#	define _(String) (String)
#	define N_(String) (String)
#endif

#define BOARD_SIZE 8

typedef enum {
	UNDO_NEW_GAME,
	UNDO_PAINT,
	UNDO_TAG1,
	UNDO_TAG2
} HitoriUndoType;

typedef struct _HitoriUndo HitoriUndo;
struct _HitoriUndo {
	HitoriUndoType type;
	guint x;
	guint y;
	HitoriUndo *undo;
	HitoriUndo *redo;
};

typedef struct {
	guint num;
	gboolean painted;
	gboolean tag1;
	gboolean tag2;
	gboolean should_be_painted;
} HitoriCell;

typedef struct {
	GtkWidget *window;
	GtkWidget *drawing_area;
	GtkAction *undo_action;
	GtkAction *redo_action;
	GtkAction *hint_action;

	gdouble drawing_area_width;
	gdouble drawing_area_height;

	guint drawing_area_x_offset;
	guint drawing_area_y_offset;

	HitoriCell board[BOARD_SIZE][BOARD_SIZE];

	gboolean debug;
	gboolean processing_events;
	HitoriUndo *undo_stack;

	guint hint_status;
	guint hint_x;
	guint hint_y;
} Hitori;

void hitori_new_game (Hitori *hitori);
void hitori_clear_undo_stack (Hitori *hitori);
void hitori_print_board (Hitori *hitori);
void hitori_enable_events (Hitori *hitori);
void hitori_disable_events (Hitori *hitori);
void hitori_quit (Hitori *hitori);

G_END_DECLS

#endif /* HITORI_MAIN_H */
