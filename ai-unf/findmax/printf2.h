
#ifndef _PRINTF2_
#define _PRINTF2_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>

#ifdef __KLIBC__

#include <klibc/poet.h>
static inline void fmtint (char *buff, uintmax_t v, int base, int sgn)
{
   format_int2 (buff, 32, v, base, sgn);
}

#else
static inline void fmtint (char *buff, uintmax_t v, int base, int sgn)
{
   int l;

   switch (base)
   {
   case 16:
      l = sprintf (buff, "%lx", v);
      break;
   default :
      if (sgn)
         l = sprintf (buff, "%ld", v);
      else
         l = sprintf (buff, "%lu", v);
      break;
   }
   buff[l] = 0;
}
#define __libc_init_poet()
#endif // __KLIBC__


static inline int fputd (int d, FILE *f)
{
   char buff[32];
   fmtint (buff, d, 10, 1);
   return fputs (buff, f);
}

static inline int fputu (unsigned u, FILE *f)
{
   char buff[32];
   fmtint (buff, u, 10, 0);
   return fputs (buff, f);
}

static inline int fputld (long int d, FILE *f)
{
   char buff[32];
   fmtint (buff, d, 10, 1);
   return fputs (buff, f);
}

static inline int fputlu (long unsigned u, FILE *f)
{
   char buff[32];
   fmtint (buff, u, 10, 0);
   return fputs (buff, f);
}

static inline int fputx (unsigned d, FILE *f)
{
   char buff[32];
   fmtint (buff, d, 16, 0);
   return fputs (buff, f);
}

static inline int fputlx (long unsigned d, FILE *f)
{
   char buff[32];
   fmtint (buff, d, 16, 0);
   return fputs (buff, f);
}

#define putss(s) fputs (s, stdout)
#define putd(d)  fputd  (d, stdout)
#define putu(u)  fputu  (u, stdout)
#define putld(d) fputld (d, stdout)
#define putlu(u) fputlu (u, stdout)
#define putx(u)  fputx  (u, stdout)
#define putlx(u) fputlx (u, stdout)

// NORMAL: printf; printf2(fmt,args) becomes printf (fmt,args)
#ifdef PRINTF2_NORMAL
#define printf2(fmt,args...)             printf (fmt, ##args)
#define fprintf2(f,fmt,args...)          fprintf (f, fmt, ##args)
#define sprintf2(buff,fmt,args...)       sprintf (buff, fmt, ##args)
#define snprintf2(buff,size,fmt,args...) snprintf (buff, size, fmt, ##args)
#define asprintf2(strp,fmt,args...)      asprintf (strp, fmt, ##args)
#define vasprintf2(strp,fmt,ap)          asprintf (strp, fmt, ap)
#endif

// FMTONLY: printf2(fmt,args) becomes puts (fmt)
#ifdef PRINTF2_FMTONLY
#define printf2(fmt,args...)             putss (fmt)
#define fprintf2(f,fmt,args...)          fputs (fmt,f)
#define sprintf2(buff,fmt,args...)       __sprintf2 (buff,fmt)
#define snprintf2(buff,size,fmt,args...) __snprintf2 (buff, size, fmt)
#define asprintf2(strp,fmt,args...)      __asprintf2 (strp, fmt)
#define vasprintf2(strp,fmt,ap)          __asprintf2 (strp, fmt)

inline int __sprintf2 (char *buff, const char *fmt) { strcpy (buff,fmt); return strlen(fmt); }
inline int __snprintf2 (char *buff, size_t s, const char *fmt) { strncpy (buff,fmt,s); return strnlen(fmt,s); }
inline int __asprintf2(char **strp, const char *fmt)
{
   size_t len = strlen (fmt);
   void *buff = malloc (len + 1);
   if (! buff) return -1;
   strcpy (buff, fmt);
   return len;
}
#endif

// REMOVE: printf2(fmt,args) is just removed
#ifdef PRINTF2_REMOVE
#define printf(fmt,args...)            
#define printf2(fmt,args...)            
#define fprintf2(f,fmt,args...)         
#define sprintf2(buff,fmt,args...)      
#define snprintf2(buff,size,fmt,args...)
#define asprintf2(strp,fmt,args...)     
#define vasprintf2(strp,fmt,ap)         
#endif


#endif // _PRINTF2_

