/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

/*
 * Code taken from glib-2.30.2, truncated, stripped & crippled down
 * to the minimum as required for use with pkg-config-lite.
 * For the full/complete glib code, refer to ftp://ftp.gtk.org/pub/gtk/.
 *
 * This snippet was created by Oliver Lange.
 * All changes from the original code fall under the GLib copyright.
 */

#ifndef __G_LIB_H__
#define __G_LIB_H__

//
// BEGIN glibconfig.h
//
#ifdef  __cplusplus
extern "C"
{
#endif

//
// All we need to know for this tiny glib snippet is guint16, guint32,
// gsize, gssize and the GPOINTER_TO_X() and X_TO_POINTER() macros.
//
// That's so few things that it would be a bit over the top to go and
// utilize autoconf for this.
//

//
// DEBUG
//
#if defined(_DEBUG) && !defined(DEBUG)
  #define DEBUG
#elif defined(DEBUG) && !defined(_DEBUG)
  #define _DEBUG
#endif
#if defined(DEBUG) && defined(NDEBUG)
  #error both DEBUG and NDEBUG defined at the same time.
#endif
#if !defined(DEBUG) && !defined(NDEBUG)
  // turn of debug stuff if DEBUG isn't explicitly defined
  #define NDEBUG
#endif

//
// Windows:
//
// All sources & headers should use _WIN32 as reference define (on 64-bit Windows
// as well), but MSC-Win32 projects usually define WIN32 in the project settings
// (which is correct so far), where WinBase.h would automatically define _WIN32,
// too, but only if Windows.h is included at all, so we just make sure:
//
#if defined(WIN32) && !defined(_WIN32)
  #define _WIN32
#elif defined(_WIN32) && !defined(WIN32)
  #define WIN32
#endif

// Just in case:
#if defined(WIN64) && !defined(_WIN64)
  #define _WIN64
#elif defined(_WIN64) && !defined(WIN64)
  #define WIN64
#endif

//
// G_OS_WIN32
//
#if defined(_WIN32) || defined(_WIN64)
  #define G_OS_WIN32
#endif

//
// guint16, guint32:
//
#ifdef _WIN32
  #if defined(__MINGW32__) || defined(__MINGW64__)
    #include <stdint.h>
    typedef uint16_t  guint16;
    typedef uint32_t  guint32;
  #elif !defined(__GNUC__)
    // MSVC/Borland
    typedef unsigned __int16  guint16;
    typedef unsigned __int32  guint32;
  #else
    // Cygwin
    #include <_G_config.h>
    typedef _G_uint16_t guint16;
    typedef _G_uint32_t guint32;
  #endif
#elif defined(__MACOS__)
  #include <sys/types.h>
  typedef UInt16  guint16;
  typedef UInt32  guint32;
#elif defined(__MACOSX__)
  // MacOS X Framework build
  #include <sys/types.h>
  typedef u_int16_t guint16;
  typedef u_int32_t guint32;
#elif defined(__BEOS__)
  // BeOS
  #include <inttypes.h>
  typedef u_int16_t guint16;
  typedef u_int32_t guint32;
#elif defined (__EMX__)
  /* OS/2 GCC */
  typedef unsigned short  guint16;
  typedef unsigned int    guint32;
#else
  typedef unsigned short  guint16;
  typedef unsigned int    guint32;
#endif // !_WIN32

//
// gsize, gssize:
//
#if defined(_WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__) && !defined(__GNUC__)
  // MSVC/Borland
  #include <basetsd.h>
  typedef SIZE_T  gsize;
  typedef SSIZE_T gssize;
#else
  #include <sys/types.h>
  typedef size_t  gsize;
  typedef ssize_t gssize;
#endif

//
// GPOINTER_TO_X(), X_TO_GPOINTER()
//
#define GPOINTER_TO_INT(p_)   ((gint)(gssize)(p_))
#define GPOINTER_TO_UINT(p_)  ((guint)(gsize)(p_))

#define GINT_TO_POINTER(i_)   ((gpointer)(gssize)(i_))
#define GUINT_TO_POINTER(i_)  ((gpointer)(gsize)(i_))

#ifdef  __cplusplus
}
#endif
//
// END glibconfig.h
//

//
// assert (gtestutils.h)
//
#ifdef DEBUG
  #include  <assert.h>
  #include  <stdio.h>

  #define g_assert(expr_)   assert(expr_)
  #define g_assert_not_reached() \
            fprintf(stderr, "%s:%d: g_assert_not_reached() failed.\n", __FILE__, __LINE__); \
            abort();
#else
  #define g_assert(expr_)
  #define g_assert_not_reached()
#endif

//
// other includes used in this file:
//

// gmacros.h:
#include <stddef.h>
// gstrfuncs.h:
#include <stdarg.h>

//
// BEGIN gmacros.h
//
/* We include stddef.h to get the system's definition of NULL
 */
//#include <stddef.h>

/* Provide macros to feature the GCC function attribute.
 */
#if     __GNUC__ >= 4
#define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#else
#define G_GNUC_NULL_TERMINATED
#endif

#if    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define G_GNUC_WARN_UNUSED_RESULT 		\
  __attribute__((warn_unused_result))
#else
#define G_GNUC_WARN_UNUSED_RESULT
#endif /* __GNUC__ */

#define G_STRINGIFY(macro_or_string)	G_STRINGIFY_ARG (macro_or_string)
#define	G_STRINGIFY_ARG(contents)	#contents

/* Provide a string identifying the current code position */
#if defined(__GNUC__) && (__GNUC__ < 3) && !defined(__cplusplus)
#  define G_STRLOC	__FILE__ ":" G_STRINGIFY (__LINE__) ":" __PRETTY_FUNCTION__ "()"
#else
#  define G_STRLOC	__FILE__ ":" G_STRINGIFY (__LINE__)
#endif

/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
# define G_BEGIN_DECLS  extern "C" {
# define G_END_DECLS    }
#else
# define G_BEGIN_DECLS
# define G_END_DECLS
#endif

#ifndef NULL
#  ifdef __cplusplus
#    define NULL        (0L)
#  else /* !__cplusplus */
#    define NULL        ((void*) 0)
#  endif /* !__cplusplus */
#endif

#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	TRUE
#define	TRUE	(!FALSE)
#endif

#undef	MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef	MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#if !(defined (G_STMT_START) && defined (G_STMT_END))
#  define G_STMT_START  do
#  define G_STMT_END    while (0)
#endif
//
// END gmacros.h
//

//
// BEGIN gtypes.h
//
G_BEGIN_DECLS

typedef char   gchar;
typedef long   glong;
typedef int    gint;
typedef gint   gboolean;

typedef unsigned char   guchar;
typedef unsigned long   gulong;
typedef unsigned int    guint;

/* Define min and max constants for the fixed size numerical types */
typedef void* gpointer;
typedef const void *gconstpointer;

typedef gint            (*GCompareFunc)         (gconstpointer  a,
                                                 gconstpointer  b);
typedef gint            (*GCompareDataFunc)     (gconstpointer  a,
                                                 gconstpointer  b,
						 gpointer       user_data);
typedef gboolean        (*GEqualFunc)           (gconstpointer  a,
                                                 gconstpointer  b);
typedef void            (*GDestroyNotify)       (gpointer       data);
typedef void            (*GFunc)                (gpointer       data,
                                                 gpointer       user_data);
typedef guint           (*GHashFunc)            (gconstpointer  key);
typedef void            (*GHFunc)               (gpointer       key,
                                                 gpointer       value,
                                                 gpointer       user_data);
G_END_DECLS
//
// END gtypes.h
//

//
// BEGIN gmem.h
//
G_BEGIN_DECLS

void      g_free    (gpointer mem);

gpointer  g_malloc  (gsize    n_bytes);
gpointer  g_malloc0 (gsize    n_bytes);
gpointer  g_realloc (gpointer mem,
                     gsize    n_bytes) G_GNUC_WARN_UNUSED_RESULT;

#define g_new(struct_type_,n_structs_)  (struct_type_ *)(g_malloc(sizeof(struct_type_) * (size_t)(n_structs_)))
#define g_new0(struct_type_,n_structs_) (struct_type_ *)(g_malloc0(sizeof(struct_type_) * (size_t)(n_structs_)))

G_END_DECLS
//
// END gmem.h
//

//
// BEGIN gstrfuncs.h
//
//#include <stdarg.h>

G_BEGIN_DECLS

/* Functions like the ones in <ctype.h> that are not affected by locale. */
typedef enum {
  G_ASCII_ALNUM  = 1 << 0,
  G_ASCII_ALPHA  = 1 << 1,
  G_ASCII_CNTRL  = 1 << 2,
  G_ASCII_DIGIT  = 1 << 3,
  G_ASCII_GRAPH  = 1 << 4,
  G_ASCII_LOWER  = 1 << 5,
  G_ASCII_PRINT  = 1 << 6,
  G_ASCII_PUNCT  = 1 << 7,
  G_ASCII_SPACE  = 1 << 8,
  G_ASCII_UPPER  = 1 << 9,
  G_ASCII_XDIGIT = 1 << 10
} GAsciiType;

extern const guint16 * const g_ascii_table;

#define g_ascii_isalnum(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_ALNUM) != 0)
#define g_ascii_isalpha(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_ALPHA) != 0)
#define g_ascii_iscntrl(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_CNTRL) != 0)
#define g_ascii_isdigit(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_DIGIT) != 0)
#define g_ascii_isgraph(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_GRAPH) != 0)
#define g_ascii_islower(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_LOWER) != 0)
#define g_ascii_isprint(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_PRINT) != 0)
#define g_ascii_ispunct(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_PUNCT) != 0)
#define g_ascii_isspace(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_SPACE) != 0)
#define g_ascii_isupper(c)  ((g_ascii_table[(guchar) (c)] & G_ASCII_UPPER) != 0)
#define g_ascii_isxdigit(c) ((g_ascii_table[(guchar) (c)] & G_ASCII_XDIGIT) != 0)

gchar                 g_ascii_tolower  (gchar        c);
gchar                 g_ascii_toupper  (gchar        c);

/* removes leading spaces */
gchar*                g_strchug        (gchar        *string);
/* removes trailing spaces */
gchar*                g_strchomp       (gchar        *string);
/* removes leading & trailing spaces */
#define g_strstrip( string )	g_strchomp (g_strchug (string))

gint                  g_ascii_strcasecmp  (const gchar *s1,
					   const gchar *s2);

gchar*	              g_strdup	       (const gchar *str);

//
// g_strdup_vprintf(): replacement function
//
gchar * g_strdup_vprintf (const gchar *  format,
                          va_list        args);

gchar*	              g_strndup	       (const gchar *str,
					gsize        n);
gchar*	              g_strnfill       (gsize        length,
					gchar        fill_char);
gchar*	              g_strconcat      (const gchar *string1,
					...) G_GNUC_NULL_TERMINATED;

gpointer              g_memdup	       (gconstpointer mem,
					guint	       byte_size);

gchar**	              g_strsplit       (const gchar  *string,
					const gchar  *delimiter,
					guint         max_tokens);
void                  g_strfreev       (gchar       **str_array);
gchar**               g_strdupv        (gchar       **str_array);

gchar*                g_stpcpy         (gchar        *dest,
                                        const char   *src);

G_END_DECLS
//
// END gstrfuncs.h
//

//
// BEGIN gutils.h
//
G_BEGIN_DECLS

#ifdef G_OS_WIN32

#define G_DIR_SEPARATOR '\\'
#define G_DIR_SEPARATOR_S "\\"
#define G_IS_DIR_SEPARATOR(c) ((c) == G_DIR_SEPARATOR || (c) == '/')
#define G_SEARCHPATH_SEPARATOR ';'
#define G_SEARCHPATH_SEPARATOR_S ";"

#else  /* !G_OS_WIN32 */

/* Unix */

#define G_DIR_SEPARATOR '/'
#define G_DIR_SEPARATOR_S "/"
#define G_IS_DIR_SEPARATOR(c) ((c) == G_DIR_SEPARATOR)
#define G_SEARCHPATH_SEPARATOR ':'
#define G_SEARCHPATH_SEPARATOR_S ":"

#endif /* !G_OS_WIN32 */

/* The returned strings are newly allocated with g_malloc() */
gchar*                g_path_get_dirname   (const gchar *file_name);

G_END_DECLS
//
// END gutils.h
//

//
// BEGIN gfileutils.h
//
G_BEGIN_DECLS

typedef enum
{
  G_FILE_TEST_IS_REGULAR    = 1 << 0,
  G_FILE_TEST_IS_DIR        = 1 << 2
} GFileTest;

gboolean g_file_test         (const gchar  *filename,
                              GFileTest     test);

G_END_DECLS
//
// END gfileutils.h
//

//
// BEGIN gslist.h
//
G_BEGIN_DECLS

typedef struct _GSList GSList;

struct _GSList
{
  gpointer data;
  GSList *next;
};

GSList*  g_slist_alloc                   (void) G_GNUC_WARN_UNUSED_RESULT;
void     g_slist_free                    (GSList           *list);
void     g_slist_free_1                  (GSList           *list);
GSList*  g_slist_append                  (GSList           *list,
					  gpointer          data) G_GNUC_WARN_UNUSED_RESULT;
GSList*  g_slist_prepend                 (GSList           *list,
					  gpointer          data) G_GNUC_WARN_UNUSED_RESULT;
GSList*  g_slist_concat                  (GSList           *list1,
					  GSList           *list2) G_GNUC_WARN_UNUSED_RESULT;
GSList*  g_slist_remove                  (GSList           *list,
					  gconstpointer     data) G_GNUC_WARN_UNUSED_RESULT;
GSList*  g_slist_reverse                 (GSList           *list) G_GNUC_WARN_UNUSED_RESULT;
GSList*  g_slist_copy                    (GSList           *list) G_GNUC_WARN_UNUSED_RESULT;
GSList*  g_slist_find                    (GSList           *list,
					  gconstpointer     data);
GSList*  g_slist_last                    (GSList           *list);
void     g_slist_foreach                 (GSList           *list,
					  GFunc             func,
					  gpointer          user_data);
GSList*  g_slist_sort                    (GSList           *list,
					  GCompareFunc      compare_func) G_GNUC_WARN_UNUSED_RESULT;

#define  g_slist_next(slist)	         ((slist) ? (((GSList *)(slist))->next) : NULL)

G_END_DECLS
//
// END gslist.h
//

//
// BEGIN ghash.h
//
G_BEGIN_DECLS

typedef struct _GHashTable  GHashTable;

GHashTable* g_hash_table_new		   (GHashFunc	    hash_func,
					    GEqualFunc	    key_equal_func);
GHashTable* g_hash_table_new_full      	   (GHashFunc	    hash_func,
					    GEqualFunc	    key_equal_func,
					    GDestroyNotify  key_destroy_func,
					    GDestroyNotify  value_destroy_func);
void	    g_hash_table_destroy	   (GHashTable	   *hash_table);
void	    g_hash_table_insert		   (GHashTable	   *hash_table,
					    gpointer	    key,
					    gpointer	    value);
//currently unused..
//gboolean    g_hash_table_remove		   (GHashTable	   *hash_table,
//					    gconstpointer   key);
void        g_hash_table_remove_all        (GHashTable     *hash_table);
gpointer    g_hash_table_lookup		   (GHashTable	   *hash_table,
					    gconstpointer   key);
void	    g_hash_table_foreach	   (GHashTable	   *hash_table,
					    GHFunc	    func,
					    gpointer	    user_data);

/* keeping hash tables alive */
void        g_hash_table_unref             (GHashTable     *hash_table);

// in gstring.c
gboolean g_str_equal (gconstpointer  v1,
                      gconstpointer  v2);
// in gstring.c
guint    g_str_hash  (gconstpointer  v);

guint    g_direct_hash  (gconstpointer  v);

G_END_DECLS
//
// END ghash.h
//

//
// BEGIN gstring.h
//
G_BEGIN_DECLS

typedef struct _GString		GString;
struct _GString
{
  gchar  *str;
  gsize len;
  gsize allocated_len;
};

GString*     g_string_new	        (const gchar	 *init);
GString*     g_string_new_len           (const gchar     *init,
                                         gssize           len);
GString*     g_string_sized_new         (gsize            dfl_size);
gchar*	     g_string_free	        (GString	 *string,
					 gboolean	  free_segment);
GString*     g_string_truncate          (GString	 *string,
					 gsize		  len);
GString*     g_string_insert_len        (GString         *string,
                                         gssize           pos,
                                         const gchar     *val,
                                         gssize           len);
GString*     g_string_append            (GString	 *string,
			                 const gchar	 *val);
GString*     g_string_append_len        (GString	 *string,
			                 const gchar	 *val,
                                         gssize           len);
GString*     g_string_append_c          (GString	 *string,
					 gchar		  c);
GString*     g_string_insert            (GString	 *string,
					 gssize		  pos,
					 const gchar	 *val);
GString*     g_string_insert_c          (GString	 *string,
					 gssize		  pos,
					 gchar		  c);
GString*     g_string_erase	        (GString	 *string,
					 gssize		  pos,
					 gssize		  len);

G_END_DECLS
//
// END gstring.h
//

//
// BEGIN gwin32.h
//
#ifdef G_OS_WIN32
G_BEGIN_DECLS

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

//
// replacement function, similar to g_win32_get_package_installation_subdirectory()
//
gchar * g_win32_get_package_installation_subdir(const gchar * subdir);

G_END_DECLS
#endif // G_OS_WIN32
//
// END gwin32.h
//

#endif /* __G_LIB_H__ */
