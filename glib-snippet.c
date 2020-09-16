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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
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

#include "glib-snippet.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#ifdef G_OS_WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

//
// BEGIN gmem.c
//
//#include "gmem.h"

//#include <stdlib.h>
//#include <stdarg.h>
//#include <stdio.h>

//
// g_error() replacement function for use without g_logv()
//
static void
g_error (const gchar *format,
         ...)
{
  va_list args;
  va_start (args, format);
  fprintf(stderr, format, args);
  va_end (args);
  // shutdown now
  abort();
}

gpointer
g_malloc (gsize n_bytes)
{
  if (n_bytes)
  {
    gpointer mem;

    mem = malloc (n_bytes);
    if (mem)
      return mem;

    g_error ("%s: out of memory", G_STRLOC);
  }
  return NULL;
}

gpointer
g_malloc0 (gsize n_bytes)
{
  if (n_bytes)
  {
    gpointer mem;

    mem = calloc (1, n_bytes);
    if (mem)
      return mem;

    g_error ("%s: out of memory", G_STRLOC);
  }
  return NULL;
}

gpointer
g_realloc (gpointer mem,
           gsize    n_bytes)
{
  gpointer newmem;

  if (n_bytes)
  {
    newmem = realloc (mem, n_bytes);
    if (newmem)
      return newmem;

    g_error ("%s: out of memory", G_STRLOC);
  }

  if (mem)
    free (mem);
  return NULL;
}

void
g_free (gpointer mem)
{
  if (mem)
    free (mem);
}
//
// END gmem.c
//

//
// BEGIN gstrfuncs.c
//
//#include "gstrfuncs.h"

//#include "gmem.h"
//#include "gslist.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

static const guint16 ascii_table_data[256] = {
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x004, 0x104, 0x104, 0x004, 0x104, 0x104, 0x004, 0x004,
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x140, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459,
  0x459, 0x459, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x653, 0x653, 0x653, 0x653, 0x653, 0x653, 0x253,
  0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
  0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
  0x253, 0x253, 0x253, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x473, 0x473, 0x473, 0x473, 0x473, 0x473, 0x073,
  0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
  0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
  0x073, 0x073, 0x073, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x004
  /* the upper 128 are all zeroes */
};

const guint16 * const g_ascii_table = ascii_table_data;

gchar*
g_strdup (const gchar *str)
{
  gchar *new_str;
  gsize length;

  if (str)
  {
    length = strlen (str) + 1;
    new_str = g_new (char, length);
    memcpy (new_str, str, length);
  }
  else
    new_str = NULL;

  return new_str;
}

gpointer
g_memdup (gconstpointer mem,
          guint         byte_size)
{
  gpointer new_mem;

  if (mem)
  {
    new_mem = g_malloc (byte_size);
    memcpy (new_mem, mem, byte_size);
  }
  else
    new_mem = NULL;

  return new_mem;
}

gchar*
g_strndup (const gchar *str,
           gsize        n)
{
  gchar *new_str;

  if (str)
  {
    new_str = g_new (gchar, n + 1);
    strncpy (new_str, str, n);
    new_str[n] = '\0';
  }
  else
    new_str = NULL;

  return new_str;
}

gchar*
g_strnfill (gsize length,
            gchar fill_char)
{
  gchar *str;

  str = g_new (gchar, length + 1);
  memset (str, (guchar)fill_char, length);
  str[length] = '\0';

  return str;
}

gchar *
g_stpcpy (gchar       *dest,
          const gchar *src)
{
  register gchar *d = dest;
  register const gchar *s = src;
  if(!src || !dest)
  {
    return(NULL);
  }
  do
    *d++ = *s;
  while (*s++ != '\0');

  return d - 1;
}

//
// g_strdup_vprintf(): replacement function (simplified)
//
gchar *
g_strdup_vprintf (const gchar *  format,
                   va_list        args)
{
  size_t  bufSize = 64;
  gchar * result;
  int     len = 0;

  do
  {
    if(!(result = g_malloc(bufSize)))
    {
      fprintf(stderr, "ERROR: out of memory.\n");
      abort();
    }
    *result = 0;
    if(format && *format)
    {
      len = vsnprintf(result, bufSize, format, args);
    }
    // Win32 (and old glibc) return -1 on failure instead of the required size
    if(len >= 0 && (size_t)(len) < bufSize)
    {
      // success
      return(result);
    }
    // need bigger buffer
    bufSize = len >= 0 ? len+1 : bufSize<<1;
    g_free(result);
  }while(1);
  return(NULL);
}

gchar*
g_strconcat (const gchar *string1, ...)
{
  gsize   l;
  va_list args;
  gchar   *s;
  gchar   *concat;
  gchar   *ptr;

  if (!string1)
    return NULL;

  l = 1 + strlen (string1);
  va_start (args, string1);
  s = va_arg (args, gchar*);
  while (s)
  {
    l += strlen (s);
    s = va_arg (args, gchar*);
  }
  va_end (args);

  concat = g_new (gchar, l);
  ptr = concat;

  ptr = g_stpcpy (ptr, string1);
  va_start (args, string1);
  s = va_arg (args, gchar*);
  while (s)
  {
    ptr = g_stpcpy (ptr, s);
    s = va_arg (args, gchar*);
  }
  va_end (args);

  return concat;
}

gchar
g_ascii_tolower (gchar c)
{
  return g_ascii_isupper (c) ? c - 'A' + 'a' : c;
}

gchar
g_ascii_toupper (gchar c)
{
  return g_ascii_islower (c) ? c - 'a' + 'A' : c;
}

#define ISUPPER(c)              ((c) >= 'A' && (c) <= 'Z')
#define TOLOWER(c)              (ISUPPER (c) ? (c) - 'A' + 'a' : (c))

gint
g_ascii_strcasecmp (const gchar *s1,
                    const gchar *s2)
{
  gint c1, c2;

  if(!s1 || !s2)
  {
    return(0);
  }
  while (*s1 && *s2)
  {
    c1 = (gint)(guchar) TOLOWER (*s1);
    c2 = (gint)(guchar) TOLOWER (*s2);
    if (c1 != c2)
      return (c1 - c2);
    s1++; s2++;
  }

  return (((gint)(guchar) *s1) - ((gint)(guchar) *s2));
}

gchar*
g_strchug (gchar *string)
{
  guchar *start;

  if(!string)
  {
    return(NULL);
  }
  for (start = (guchar*) string; *start && g_ascii_isspace (*start); start++)
  ;

  memmove (string, start, strlen ((gchar *) start) + 1);

  return string;
}

gchar*
g_strchomp (gchar *string)
{
  gsize len;

  if(!string)
  {
    return(NULL);
  }
  len = strlen (string);
  while (len--)
  {
    if (g_ascii_isspace ((guchar) string[len]))
      string[len] = '\0';
    else
      break;
  }

  return string;
}

//
// g_strsplit: in contrast to the original glib function, this function is
// using guint instead of gint for max_tokens, where 0 still means no limit.
// This is used to get rid of G_MAXINT and it also makes sense to use guint
// for max_tokens anyhow.
//
gchar**
g_strsplit (const gchar *string,
            const gchar *delimiter,
            guint        max_tokens)
{
  GSList *string_list = NULL, *slist;
  gchar **str_array, *s;
  guint n = 0;
  const gchar *remainder;

  if(!string || !delimiter || !*delimiter)
  {
    return(NULL);
  }

  if (max_tokens < 1)
    max_tokens = ~((guint)0); //G_MAXINT;

  remainder = string;
  s = strstr (remainder, delimiter);
  if (s)
  {
    gsize delimiter_len = strlen (delimiter);

    while (--max_tokens && s)
    {
      gsize len;

      len = s - remainder;
      string_list = g_slist_prepend (string_list,
                                     g_strndup (remainder, len));
      n++;
      remainder = s + delimiter_len;
      s = strstr (remainder, delimiter);
    }
  }
  if (*string)
  {
    n++;
    string_list = g_slist_prepend (string_list, g_strdup (remainder));
  }

  str_array = g_new (gchar*, n + 1);

  str_array[n--] = NULL;
  for (slist = string_list; slist; slist = slist->next)
    str_array[n--] = slist->data;

  g_slist_free (string_list);

  return str_array;
}

void
g_strfreev (gchar **str_array)
{
  if (str_array)
  {
    int i;

    for (i = 0; str_array[i] != NULL; i++)
      g_free (str_array[i]);

    g_free (str_array);
  }
}

gchar**
g_strdupv (gchar **str_array)
{
  if (str_array)
  {
    gint i;
    gchar **retval;

    i = 0;
    while (str_array[i])
      ++i;

    retval = g_new (gchar*, i + 1);

    i = 0;
    while (str_array[i])
    {
      retval[i] = g_strdup (str_array[i]);
      ++i;
    }
    retval[i] = NULL;

    return retval;
  }
  else
    return NULL;
}
//
// END gstrfuncs.c
//

//
// BEGIN gutils.c
//
//#include "gutils.h"

//#include "gmem.h"
//#include "gstrfuncs.h"

//#include <string.h>

gchar*
g_path_get_dirname (const gchar    *file_name)
{
  register gchar *base;
  register gsize len;

  if(!file_name)
  {
    return(NULL);
  }

  base = strrchr (file_name, G_DIR_SEPARATOR);
#ifdef G_OS_WIN32
  {
    gchar *q = strrchr (file_name, '/');
    if (base == NULL || (q != NULL && q > base))
        base = q;
  }
#endif
  if (!base)
  {
#ifdef G_OS_WIN32
    if (g_ascii_isalpha (file_name[0]) && file_name[1] == ':')
    {
      gchar drive_colon_dot[4];

      drive_colon_dot[0] = file_name[0];
      drive_colon_dot[1] = ':';
      drive_colon_dot[2] = '.';
      drive_colon_dot[3] = '\0';

      return g_strdup (drive_colon_dot);
    }
#endif
    return g_strdup (".");
  }

  while (base > file_name && G_IS_DIR_SEPARATOR (*base))
    base--;

#ifdef G_OS_WIN32
  if (base == file_name + 1 && g_ascii_isalpha (file_name[0]) && file_name[1] == ':')
    base++;
  else if (G_IS_DIR_SEPARATOR (file_name[0]) &&
           G_IS_DIR_SEPARATOR (file_name[1]) &&
           file_name[2] &&
           !G_IS_DIR_SEPARATOR (file_name[2]) &&
           base >= file_name + 2)
  {
    const gchar *p = file_name + 2;
    while (*p && !G_IS_DIR_SEPARATOR (*p))
      p++;
    if (p == base + 1)
    {
      len = (guint) strlen (file_name) + 1;
      base = g_new (gchar, len + 1);
      strcpy (base, file_name);
      base[len-1] = G_DIR_SEPARATOR;
      base[len] = 0;
      return base;
    }
    if (G_IS_DIR_SEPARATOR (*p))
    {
      p++;
      while (*p && !G_IS_DIR_SEPARATOR (*p))
        p++;
      if (p == base + 1)
        base++;
    }
  }
#endif

  len = (guint) 1 + base - file_name;

  base = g_new (gchar, len + 1);
  memmove (base, file_name, len);
  base[len] = 0;

  return base;
}
//
// END gutils.c
//

//
// BEGIN gfileutils.c
//
//#include "gfileutils.h"

//#ifdef G_OS_WIN32
//#include <windows.h>
//#else
//#include <sys/stat.h>
//#endif

//
// g_file_test: strongly crippled.
//
gboolean
g_file_test (const gchar *filename,
             GFileTest    test)
{
#ifdef G_OS_WIN32
#if defined(UNICODE) || defined (_UNICODE)
  #error This application must not be compiled in UNICODE mode.
#endif
/* stuff missing in std vc6 api */
#  ifndef INVALID_FILE_ATTRIBUTES
#    define INVALID_FILE_ATTRIBUTES -1
#  endif
#  ifndef FILE_ATTRIBUTE_DEVICE
#    define FILE_ATTRIBUTE_DEVICE 64
#  endif
  int attributes = GetFileAttributes (filename);

  if (attributes == INVALID_FILE_ATTRIBUTES)
    return FALSE;

  if (test & G_FILE_TEST_IS_REGULAR)
  {
    if ((attributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_DEVICE)) == 0)
      return TRUE;
  }

  if (test & G_FILE_TEST_IS_DIR)
  {
    if ((attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      return TRUE;
  }

  return FALSE;
#else
  if (test & (G_FILE_TEST_IS_REGULAR | G_FILE_TEST_IS_DIR))
  {
    struct stat s;

    if (stat (filename, &s) == 0)
    {
      if ((test & G_FILE_TEST_IS_REGULAR) && S_ISREG (s.st_mode))
        return TRUE;

      if ((test & G_FILE_TEST_IS_DIR) && S_ISDIR (s.st_mode))
        return TRUE;

    }
  }

  return FALSE;
#endif
}
//
// END gfileutils.c
//

//
// BEGIN gslist.c
//
//#include "gslist.h"

//#include "gmem.h"

#define _g_slist_alloc0()       g_malloc0(sizeof(GSList)) //g_slice_new0 (GSList)
#define _g_slist_alloc()        g_malloc(sizeof(GSList))  //g_slice_new (GSList)
#define _g_slist_free1(slist)   g_free(slist)             //g_slice_free (GSList, slist)

GSList*
g_slist_alloc (void)
{
  return _g_slist_alloc0 ();
}

void
g_slist_free (GSList *list)
{
  while(list)
  {
    GSList *next = list->next;
    _g_slist_free1(list);
    list = next;
  }
}

void
g_slist_free_1 (GSList *list)
{
  _g_slist_free1 (list);
}

GSList*
g_slist_append (GSList   *list,
                gpointer  data)
{
  GSList *new_list;
  GSList *last;

  new_list = _g_slist_alloc ();
  new_list->data = data;
  new_list->next = NULL;

  if (list)
  {
    last = g_slist_last (list);
    /* g_assert (last != NULL); */
    last->next = new_list;

    return list;
  }
  else
    return new_list;
}

GSList*
g_slist_prepend (GSList   *list,
                 gpointer  data)
{
  GSList *new_list;

  new_list = _g_slist_alloc ();
  new_list->data = data;
  new_list->next = list;

  return new_list;
}

GSList *
g_slist_concat (GSList *list1, GSList *list2)
{
  if (list2)
  {
    if (list1)
      g_slist_last (list1)->next = list2;
    else
      list1 = list2;
  }

  return list1;
}

GSList*
g_slist_remove (GSList        *list,
                gconstpointer  data)
{
  GSList *tmp, *prev = NULL;

  tmp = list;
  while (tmp)
  {
    if (tmp->data == data)
    {
      if (prev)
        prev->next = tmp->next;
      else
        list = tmp->next;

      g_slist_free_1 (tmp);
      break;
    }
    prev = tmp;
    tmp = prev->next;
  }

  return list;
}

GSList*
g_slist_copy (GSList *list)
{
  GSList *new_list = NULL;

  if (list)
  {
    GSList *last;

    new_list = _g_slist_alloc ();
    new_list->data = list->data;
    last = new_list;
    list = list->next;
    while (list)
    {
      last->next = _g_slist_alloc ();
      last = last->next;
      last->data = list->data;
      list = list->next;
    }
    last->next = NULL;
  }

  return new_list;
}

GSList*
g_slist_reverse (GSList *list)
{
  GSList *prev = NULL;

  while (list)
  {
    GSList *next = list->next;

    list->next = prev;

    prev = list;
    list = next;
  }

  return prev;
}

GSList*
g_slist_find (GSList        *list,
              gconstpointer  data)
{
  while (list)
  {
    if (list->data == data)
      break;
    list = list->next;
  }

  return list;
}

GSList*
g_slist_last (GSList *list)
{
  if (list)
  {
    while (list->next)
      list = list->next;
  }

  return list;
}

void
g_slist_foreach (GSList   *list,
                 GFunc     func,
                 gpointer  user_data)
{
  while (list)
  {
    GSList *next = list->next;
    (*func) (list->data, user_data);
    list = next;
  }
}

static GSList *
g_slist_sort_merge (GSList   *l1,
                    GSList   *l2,
                    GFunc     compare_func,
                    gpointer  user_data)
{
  GSList list, *l;
  gint cmp;

  l=&list;

  while (l1 && l2)
  {
    cmp = ((GCompareDataFunc) compare_func) (l1->data, l2->data, user_data);

    if (cmp <= 0)
    {
      l=l->next=l1;
      l1=l1->next;
    }
    else
    {
      l=l->next=l2;
      l2=l2->next;
    }
  }
  l->next= l1 ? l1 : l2;

  return list.next;
}

static GSList *
g_slist_sort_real (GSList   *list,
                   GFunc     compare_func,
                   gpointer  user_data)
{
  GSList *l1, *l2;

  if (!list)
    return NULL;
  if (!list->next)
    return list;

  l1 = list;
  l2 = list->next;

  while ((l2 = l2->next) != NULL)
  {
    if ((l2 = l2->next) == NULL)
      break;
    l1=l1->next;
  }
  l2 = l1->next;
  l1->next = NULL;

  return g_slist_sort_merge (g_slist_sort_real (list, compare_func, user_data),
                             g_slist_sort_real (l2, compare_func, user_data),
                             compare_func,
                             user_data);
}

GSList *
g_slist_sort (GSList       *list,
              GCompareFunc  compare_func)
{
  return g_slist_sort_real (list, (GFunc) compare_func, NULL);
}
//
// END gslist.c
//

//
// BEGIN ghash.c
//
//#include "ghash.h"

//#include "gmem.h"
//#include "gstrfuncs.h"

//#include <string.h>

#define HASH_TABLE_MIN_SHIFT 3  /* 1 << 3 == 8 buckets */

#define UNUSED_HASH_VALUE 0
#define TOMBSTONE_HASH_VALUE 1
#define HASH_IS_UNUSED(h_) ((h_) == UNUSED_HASH_VALUE)
#define HASH_IS_TOMBSTONE(h_) ((h_) == TOMBSTONE_HASH_VALUE)
#define HASH_IS_REAL(h_) ((h_) >= 2)

struct _GHashTable
{
  gint             size;
  gint             mod;
  guint            mask;
  gint             nnodes;
  gint             noccupied;  /* nnodes + tombstones */

  gpointer        *keys;
  guint           *hashes;
  gpointer        *values;

  GHashFunc        hash_func;
  GEqualFunc       key_equal_func;
  gint             ref_count;
  GDestroyNotify   key_destroy_func;
  GDestroyNotify   value_destroy_func;
};

static const gint prime_mod [] =
{
  1,          /* For 1 << 0 */
  2,
  3,
  7,
  13,
  31,
  61,
  127,
  251,
  509,
  1021,
  2039,
  4093,
  8191,
  16381,
  32749,
  65521,      /* For 1 << 16 */
  131071,
  262139,
  524287,
  1048573,
  2097143,
  4194301,
  8388593,
  16777213,
  33554393,
  67108859,
  134217689,
  268435399,
  536870909,
  1073741789,
  2147483647  /* For 1 << 31 */
};

static void
g_hash_table_set_shift (GHashTable *hash_table, gint shift)
{
  gint i;
  guint mask = 0;

  hash_table->size = 1 << shift;
  hash_table->mod  = prime_mod [shift];

  for (i = 0; i < shift; i++)
  {
    mask <<= 1;
    mask |= 1;
  }

  hash_table->mask = mask;
}

static gint
g_hash_table_find_closest_shift (gint n)
{
  gint i;

  for (i = 0; n; i++)
    n >>= 1;

  return i;
}

static void
g_hash_table_set_shift_from_size (GHashTable *hash_table, gint size)
{
  gint shift;

  shift = g_hash_table_find_closest_shift (size);
  shift = MAX (shift, HASH_TABLE_MIN_SHIFT);

  g_hash_table_set_shift (hash_table, shift);
}

static guint
g_hash_table_lookup_node (GHashTable    *hash_table,
                          gconstpointer  key,
                          guint         *hash_return)
{
  guint node_index;
  guint node_hash;
  guint hash_value;
  guint first_tombstone = 0;
  gboolean have_tombstone = FALSE;
  guint step = 0;

  hash_value = hash_table->hash_func (key);
  if (!HASH_IS_REAL (hash_value))
    hash_value = 2;

  *hash_return = hash_value;

  node_index = hash_value % hash_table->mod;
  node_hash = hash_table->hashes[node_index];

  while (!HASH_IS_UNUSED (node_hash))
  {
    if (node_hash == hash_value)
    {
      gpointer node_key = hash_table->keys[node_index];

      if (hash_table->key_equal_func)
      {
        if (hash_table->key_equal_func (node_key, key))
          return node_index;
      }
      else if (node_key == key)
      {
        return node_index;
      }
    }
    else if (HASH_IS_TOMBSTONE (node_hash) && !have_tombstone)
    {
      first_tombstone = node_index;
      have_tombstone = TRUE;
    }

    step++;
    node_index += step;
    node_index &= hash_table->mask;
    node_hash = hash_table->hashes[node_index];
  }

  if (have_tombstone)
    return first_tombstone;

  return node_index;
}

//currently unused..
//static void
//g_hash_table_remove_node (GHashTable   *hash_table,
//                          int           i,
//                          gboolean      notify)
//{
//  gpointer key;
//  gpointer value;
//
//  key = hash_table->keys[i];
//  value = hash_table->values[i];
//
//  /* Erect tombstone */
//  hash_table->hashes[i] = TOMBSTONE_HASH_VALUE;
//
//  /* Be GC friendly */
//  hash_table->keys[i] = NULL;
//  hash_table->values[i] = NULL;
//
//  hash_table->nnodes--;
//
//  if (notify && hash_table->key_destroy_func)
//    hash_table->key_destroy_func (key);
//
//  if (notify && hash_table->value_destroy_func)
//    hash_table->value_destroy_func (value);
//
//}

static void
g_hash_table_remove_all_nodes (GHashTable *hash_table,
                               gboolean    notify)
{
  int i;
  gpointer key;
  gpointer value;

  hash_table->nnodes = 0;
  hash_table->noccupied = 0;

  if (!notify ||
      (hash_table->key_destroy_func == NULL &&
       hash_table->value_destroy_func == NULL))
  {
    memset (hash_table->hashes, 0, hash_table->size * sizeof (guint));
    memset (hash_table->keys, 0, hash_table->size * sizeof (gpointer));
    memset (hash_table->values, 0, hash_table->size * sizeof (gpointer));

    return;
  }

  for (i = 0; i < hash_table->size; i++)
  {
    if (HASH_IS_REAL (hash_table->hashes[i]))
    {
      key = hash_table->keys[i];
      value = hash_table->values[i];

      hash_table->hashes[i] = UNUSED_HASH_VALUE;
      hash_table->keys[i] = NULL;
      hash_table->values[i] = NULL;

      if (hash_table->key_destroy_func != NULL)
        hash_table->key_destroy_func (key);

      if (hash_table->value_destroy_func != NULL)
        hash_table->value_destroy_func (value);
    }
    else if (HASH_IS_TOMBSTONE (hash_table->hashes[i]))
    {
      hash_table->hashes[i] = UNUSED_HASH_VALUE;
    }
  }
}

static void
g_hash_table_resize (GHashTable *hash_table)
{
  gpointer *new_keys;
  gpointer *new_values;
  guint *new_hashes;
  gint old_size;
  gint i;

  old_size = hash_table->size;
  g_hash_table_set_shift_from_size (hash_table, hash_table->nnodes * 2);

  new_keys = g_new0 (gpointer, hash_table->size);
  if (hash_table->keys == hash_table->values)
    new_values = new_keys;
  else
    new_values = g_new0 (gpointer, hash_table->size);
  new_hashes = g_new0 (guint, hash_table->size);

  for (i = 0; i < old_size; i++)
  {
    guint node_hash = hash_table->hashes[i];
    guint hash_val;
    guint step = 0;

    if (!HASH_IS_REAL (node_hash))
      continue;

    hash_val = node_hash % hash_table->mod;

    while (!HASH_IS_UNUSED (new_hashes[hash_val]))
    {
      step++;
      hash_val += step;
      hash_val &= hash_table->mask;
    }

    new_hashes[hash_val] = hash_table->hashes[i];
    new_keys[hash_val] = hash_table->keys[i];
    new_values[hash_val] = hash_table->values[i];
  }

  if (hash_table->keys != hash_table->values)
    g_free (hash_table->values);

  g_free (hash_table->keys);
  g_free (hash_table->hashes);

  hash_table->keys = new_keys;
  hash_table->values = new_values;
  hash_table->hashes = new_hashes;

  hash_table->noccupied = hash_table->nnodes;
}

static void
g_hash_table_maybe_resize (GHashTable *hash_table)
{
  gint noccupied = hash_table->noccupied;
  gint size = hash_table->size;

  if ((size > hash_table->nnodes * 4 && size > 1 << HASH_TABLE_MIN_SHIFT) ||
      (size <= noccupied + (noccupied / 16)))
    g_hash_table_resize (hash_table);
}

GHashTable*
g_hash_table_new (GHashFunc    hash_func,
                  GEqualFunc   key_equal_func)
{
  return g_hash_table_new_full (hash_func, key_equal_func, NULL, NULL);
}

GHashTable*
g_hash_table_new_full (GHashFunc       hash_func,
                       GEqualFunc      key_equal_func,
                       GDestroyNotify  key_destroy_func,
                       GDestroyNotify  value_destroy_func)
{
  GHashTable *hash_table;

  hash_table = g_malloc(sizeof(GHashTable));  //g_slice_new (GHashTable);
  g_hash_table_set_shift (hash_table, HASH_TABLE_MIN_SHIFT);
  hash_table->nnodes             = 0;
  hash_table->noccupied          = 0;
  hash_table->hash_func          = hash_func ? hash_func : g_direct_hash;
  hash_table->key_equal_func     = key_equal_func;
  hash_table->ref_count          = 1;
  hash_table->key_destroy_func   = key_destroy_func;
  hash_table->value_destroy_func = value_destroy_func;
  hash_table->keys               = g_new0 (gpointer, hash_table->size);
  hash_table->values             = hash_table->keys;
  hash_table->hashes             = g_new0 (guint, hash_table->size);

  return hash_table;
}

static void
g_hash_table_insert_node (GHashTable *hash_table,
                          guint       node_index,
                          guint       key_hash,
                          gpointer    key,
                          gpointer    value,
                          gboolean    keep_new_key,
                          gboolean    reusing_key)
{
  guint old_hash;
  gpointer old_key;
  gpointer old_value;

  if (hash_table->keys == hash_table->values && key != value)
    hash_table->values = g_memdup (hash_table->keys, sizeof (gpointer) * hash_table->size);

  old_hash = hash_table->hashes[node_index];
  old_key = hash_table->keys[node_index];
  old_value = hash_table->values[node_index];

  if (HASH_IS_REAL (old_hash))
  {
    if (keep_new_key)
      hash_table->keys[node_index] = key;
    hash_table->values[node_index] = value;
  }
  else
  {
    hash_table->keys[node_index] = key;
    hash_table->values[node_index] = value;
    hash_table->hashes[node_index] = key_hash;

    hash_table->nnodes++;

    if (HASH_IS_UNUSED (old_hash))
    {
      /* We replaced an empty node, and not a tombstone */
      hash_table->noccupied++;
      g_hash_table_maybe_resize (hash_table);
    }
  }

  if (HASH_IS_REAL (old_hash))
  {
    if (hash_table->key_destroy_func && !reusing_key)
      hash_table->key_destroy_func (keep_new_key ? old_key : key);
    if (hash_table->value_destroy_func)
      hash_table->value_destroy_func (old_value);
  }
}

void
g_hash_table_unref (GHashTable *hash_table)
{
  if(hash_table)
  {
    if(!--hash_table->ref_count)
    {
      g_hash_table_remove_all_nodes (hash_table, TRUE);
      if (hash_table->keys != hash_table->values)
        g_free (hash_table->values);
      g_free (hash_table->keys);
      g_free (hash_table->hashes);
      g_free(hash_table);
    }
  }
}

void
g_hash_table_destroy (GHashTable *hash_table)
{
  if(hash_table)
  {
    g_hash_table_remove_all (hash_table);
    g_hash_table_unref (hash_table);
  }
}

gpointer
g_hash_table_lookup (GHashTable   *hash_table,
                     gconstpointer key)
{
  guint node_index;
  guint node_hash;

//  g_return_val_if_fail (hash_table != NULL, NULL);

  node_index = g_hash_table_lookup_node (hash_table, key, &node_hash);

  return HASH_IS_REAL (hash_table->hashes[node_index])
    ? hash_table->values[node_index]
    : NULL;
}

static void
g_hash_table_insert_internal (GHashTable *hash_table,
                              gpointer    key,
                              gpointer    value,
                              gboolean    keep_new_key)
{
  guint key_hash;
  guint node_index;

  if(hash_table)
  {
    node_index = g_hash_table_lookup_node (hash_table, key, &key_hash);
    g_hash_table_insert_node (hash_table, node_index, key_hash, key, value, keep_new_key, FALSE);
  }
}

void
g_hash_table_insert (GHashTable *hash_table,
                     gpointer    key,
                     gpointer    value)
{
  g_hash_table_insert_internal (hash_table, key, value, FALSE);
}

//currently unused..
//static gboolean
//g_hash_table_remove_internal (GHashTable    *hash_table,
//                              gconstpointer  key,
//                              gboolean       notify)
//{
//  guint node_index;
//  guint node_hash;
//
////  g_return_val_if_fail (hash_table != NULL, FALSE);
//
//  node_index = g_hash_table_lookup_node (hash_table, key, &node_hash);
//
//  if (!HASH_IS_REAL (hash_table->hashes[node_index]))
//    return FALSE;
//
//  g_hash_table_remove_node (hash_table, node_index, notify);
//  g_hash_table_maybe_resize (hash_table);
//
//  return TRUE;
//}

//currently unused..
//gboolean
//g_hash_table_remove (GHashTable    *hash_table,
//                     gconstpointer  key)
//{
//  return g_hash_table_remove_internal (hash_table, key, TRUE);
//}

void
g_hash_table_remove_all (GHashTable *hash_table)
{
  if(!hash_table)
  {
    return;
  }
  g_hash_table_remove_all_nodes (hash_table, TRUE);
  g_hash_table_maybe_resize (hash_table);
}

void
g_hash_table_foreach (GHashTable *hash_table,
                      GHFunc      func,
                      gpointer    user_data)
{
  gint i;

  if(!hash_table || !func)
  {
    return;
  }
  for (i = 0; i < hash_table->size; i++)
  {
    guint node_hash = hash_table->hashes[i];
    gpointer node_key = hash_table->keys[i];
    gpointer node_value = hash_table->values[i];

    if (HASH_IS_REAL (node_hash))
      (* func) (node_key, node_value, user_data);
  }
}

guint
g_direct_hash (gconstpointer v)
{
  return GPOINTER_TO_UINT (v);
}
//
// END ghash.c
//

//
// BEGIN gstring.c
//
//#include "gstring.h"

//#include "gmem.h"

//#include <string.h>

gboolean
g_str_equal (gconstpointer v1,
             gconstpointer v2)
{
  const gchar *string1 = v1;
  const gchar *string2 = v2;

  return strcmp (string1, string2) == 0;
}

guint
g_str_hash (gconstpointer v)
{
  const signed char *p;
  guint32 h = 5381;

  for (p = v; *p != '\0'; p++)
    h = (h << 5) + h + *p;

  return h;
}

#define MY_MAXSIZE ((gsize)-1)

static gsize
nearest_power (gsize base, gsize num)
{
  if (num > MY_MAXSIZE / 2)
  {
    return MY_MAXSIZE;
  }
  else
  {
    gsize n = base;

    while (n < num)
      n <<= 1;

    return n;
  }
}

static void
g_string_maybe_expand (GString* string,
                       gsize    len)
{
  if (string->len + len >= string->allocated_len)
  {
    string->allocated_len = nearest_power (1, string->len + len + 1);
    string->str = g_realloc (string->str, string->allocated_len);
  }
}

GString*
g_string_sized_new (gsize dfl_size)
{
  GString *string = g_malloc(sizeof(GString));

  string->allocated_len = 0;
  string->len   = 0;
  string->str   = NULL;

  g_string_maybe_expand (string, MAX (dfl_size, 2));
  string->str[0] = 0;

  return string;
}

GString*
g_string_new (const gchar *init)
{
  GString *string;

  if (init == NULL || *init == '\0')
    string = g_string_sized_new (2);
  else
  {
    gint len;

    len = strlen (init);
    string = g_string_sized_new (len + 2);

    g_string_append_len (string, init, len);
  }

  return string;
}

GString*
g_string_new_len (const gchar *init,
                  gssize       len)
{
  GString *string;

  if (len < 0)
    return g_string_new (init);
  else
  {
    string = g_string_sized_new (len);

    if (init)
      g_string_append_len (string, init, len);

    return string;
  }
}

gchar*
g_string_free (GString *string,
               gboolean free_segment)
{
  gchar *segment;

  if(!string)
  {
    return(NULL);
  }
  if (free_segment)
  {
    g_free (string->str);
    segment = NULL;
  }
  else
    segment = string->str;

  g_free (string);

  return segment;
}

GString*
g_string_truncate (GString *string,
                   gsize    len)
{
  if(!string)
  {
    return(NULL);
  }
  string->len = MIN (len, string->len);
  string->str[string->len] = 0;

  return string;
}

GString*
g_string_insert_len (GString     *string,
                     gssize       pos,
                     const gchar *val,
                     gssize       len)
{
  if(!string || !(len == 0 || val != NULL))
  {
    return(string);
  }
  if (len == 0)
    return string;

  if (len < 0)
    len = strlen (val);

  if (pos < 0)
    pos = string->len;
  else if(!(pos <= string->len))
    return(string);

  if (val >= string->str && val <= string->str + string->len)
  {
    gsize offset = val - string->str;
    gsize precount = 0;

    g_string_maybe_expand (string, len);
    val = string->str + offset;
    /* At this point, val is valid again.  */

    /* Open up space where we are going to insert.  */
    if (pos < string->len)
      memmove (string->str + pos + len, string->str + pos, string->len - pos);

    /* Move the source part before the gap, if any.  */
    if (offset < pos)
    {
      precount = MIN (len, pos - offset);
      memcpy (string->str + pos, val, precount);
    }

    /* Move the source part after the gap, if any.  */
    if (len > precount)
      memcpy (string->str + pos + precount,
              val + /* Already moved: */ precount + /* Space opened up: */ len,
              len - precount);
  }
  else
  {
    g_string_maybe_expand (string, len);

    /* If we aren't appending at the end, move a hunk
     * of the old string to the end, opening up space
     */
    if (pos < string->len)
      memmove (string->str + pos + len, string->str + pos, string->len - pos);

    /* insert the new string */
    if (len == 1)
      string->str[pos] = *val;
    else
      memcpy (string->str + pos, val, len);
  }

  string->len += len;

  string->str[string->len] = 0;

  return string;
}

GString*
g_string_append (GString     *string,
                 const gchar *val)
{
  if(!string || !val)
  {
    return(string);
  }
  return g_string_insert_len (string, -1, val, -1);
}

GString*
g_string_append_len (GString     *string,
                     const gchar *val,
                     gssize       len)
{
  if(!string || !(len == 0 || val != NULL))
  {
    return(string);
  }
  return g_string_insert_len (string, -1, val, len);
}

GString*
g_string_append_c (GString *string,
                   gchar    c)
{
  if(!string)
  {
    return(NULL);
  }
  return g_string_insert_c (string, -1, c);
}

GString*
g_string_insert (GString     *string,
                 gssize       pos,
                 const gchar *val)
{
  if(!string || !val || !(pos <= string->len))
  {
    return(string);
  }
  return g_string_insert_len (string, pos, val, -1);
}

GString*
g_string_insert_c (GString *string,
                   gssize   pos,
                   gchar    c)
{
  if(!string)
  {
    return(NULL);
  }
  g_string_maybe_expand (string, 1);

  if (pos < 0)
    pos = string->len;
  else if(!(pos <= string->len))
    return(string);

  /* If not just an append, move the old stuff */
  if (pos < string->len)
    memmove (string->str + pos + 1, string->str + pos, string->len - pos);

  string->str[pos] = c;

  string->len += 1;

  string->str[string->len] = 0;

  return string;
}

GString*
g_string_erase (GString *string,
                gssize   pos,
                gssize   len)
{
  if(!string || !(pos >= 0) || !(pos <= string->len))
  {
    return(string);
  }

  if (len < 0)
    len = string->len - pos;
  else
  {
    if(!(pos + len <= string->len))
    {
      return(string);
    }

    if (pos + len < string->len)
      memmove (string->str + pos, string->str + pos + len, string->len - (pos + len));
  }

  string->len -= len;

  string->str[string->len] = 0;

  return string;
}
//
// END gstring.c
//

//
// BEGIN gwin32.c
//
#ifdef G_OS_WIN32

//#include "gwin32.h"

//#include "gmem.h"

//#include <string.h>
//#include <windows.h>

//
// g_win32_get_package_installation_subdir()
//
// Custom function, similar to the deprecated glib funtion named
// g_win32_get_package_installation_subdirectory().
//
#if defined(UNICODE) || defined (_UNICODE)
  #error This application must not be compiled in UNICODE mode.
#endif

gchar *
g_win32_get_package_installation_subdir(const gchar *  subdir)
{
  TCHAR   buffer[MAXPATHLEN];
  DWORD   len;
  gchar * result;

  len = GetModuleFileName(NULL, buffer, sizeof(buffer));
  if(!len || len >= sizeof(buffer)
  || strlen(buffer) + 1 + strlen(subdir) >= sizeof(buffer))
  {
    *buffer = 0;
  }
  else if((result = strrchr(buffer, '\\')))
  {
    *result = 0;
  }
  if(strlen(buffer) >= 4
  && (!stricmp(buffer + strlen(buffer) - 4, "\\bin")
   || !stricmp(buffer + strlen(buffer) - 4, "\\lib")))
  {
    buffer[strlen(buffer) - 4] = 0;
  }
  strcat(buffer, "\\");
  if(strlen(buffer) + strlen(subdir) < sizeof(buffer))
  {
    strcat(buffer, subdir);
  }
  result = g_malloc(strlen(buffer) + 1);
  strcpy(result, buffer);
  return(result);
}

#endif // G_OS_WIN32
//
// END gwin32.c
//
