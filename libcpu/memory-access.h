/* Unaligned memory access functionality.
   Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005 Red Hat, Inc.
   Written by Ulrich Drepper <drepper@redhat.com>, 2001.

   This program is Open Source software; you can redistribute it and/or
   modify it under the terms of the Open Software License version 1.0 as
   published by the Open Source Initiative.

   You should have received a copy of the Open Software License along
   with this program; if not, you may obtain a copy of the Open Software
   License version 1.0 from http://www.opensource.org/licenses/osl.php or
   by writing the Open Source Initiative c/o Lawrence Rosen, Esq.,
   3001 King Ranch Road, Ukiah, CA 95482.   */

#ifndef _MEMORY_ACCESS_H
#define _MEMORY_ACCESS_H 1

#include <byteswap.h>
#include <endian.h>
#include <limits.h>
#include <stdint.h>


/* When loading this file we require the macro MACHINE_ENCODING to be
   defined to signal the endianness of the architecture which is
   defined.  */
#ifndef MACHINE_ENCODING
# error "MACHINE_ENCODING needs to be defined"
#endif
#if MACHINE_ENCODING != __BIG_ENDIAN && MACHINE_ENCODING != __LITTLE_ENDIAN
# error "MACHINE_ENCODING must signal either big or little endian"
#endif


/* We use simple memory access functions in case the hardware allows it.
   The caller has to make sure we don't have alias problems.  */
#if ALLOW_UNALIGNED

# define read_2ubyte_unaligned(Addr) \
  (unlikely (MACHINE_ENCODING != __BYTE_ORDER)				      \
   ? bswap_16 (*((const uint16_t *) (Addr)))				      \
   : *((const uint16_t *) (Addr)))
# define read_2sbyte_unaligned(Addr) \
  (unlikely (MACHINE_ENCODING != __BYTE_ORDER)				      \
   ? (int16_t) bswap_16 (*((const int16_t *) (Addr)))			      \
   : *((const int16_t *) (Addr)))

# define read_4ubyte_unaligned_noncvt(Addr) \
   *((const uint32_t *) (Addr))
# define read_4ubyte_unaligned(Addr) \
  (unlikely (MACHINE_ENCODING != __BYTE_ORDER)				      \
   ? bswap_32 (*((const uint32_t *) (Addr)))				      \
   : *((const uint32_t *) (Addr)))
# define read_4sbyte_unaligned(Addr) \
  (unlikely (MACHINE_ENCODING != __BYTE_ORDER)				      \
   ? (int32_t) bswap_32 (*((const int32_t *) (Addr)))			      \
   : *((const int32_t *) (Addr)))

# define read_8ubyte_unaligned(Addr) \
  (unlikely (MACHINE_ENCODING != __BYTE_ORDER)				      \
   ? bswap_64 (*((const uint64_t *) (Addr)))				      \
   : *((const uint64_t *) (Addr)))
# define read_8sbyte_unaligned(Addr) \
  (unlikely (MACHINE_ENCODING != __BYTE_ORDER)				      \
   ? (int64_t) bswap_64 (*((const int64_t *) (Addr)))			      \
   : *((const int64_t *) (Addr)))

#else

union unaligned
  {
    void *p;
    uint16_t u2;
    uint32_t u4;
    uint64_t u8;
    int16_t s2;
    int32_t s4;
    int64_t s8;
  } __attribute__ ((packed));

static inline uint16_t
read_2ubyte_unaligned (const void *p)
{
  const union unaligned *up = p;
  if (MACHINE_ENCODING != __BYTE_ORDER)
    return bswap_16 (up->u2);
  return up->u2;
}
static inline int16_t
read_2sbyte_unaligned (const void *p)
{
  const union unaligned *up = p;
  if (MACHINE_ENCODING != __BYTE_ORDER)
    return (int16_t) bswap_16 (up->u2);
  return up->s2;
}

static inline uint32_t
read_4ubyte_unaligned_noncvt (const void *p)
{
  const union unaligned *up = p;
  return up->u4;
}
static inline uint32_t
read_4ubyte_unaligned (const void *p)
{
  const union unaligned *up = p;
  if (MACHINE_ENCODING != __BYTE_ORDER)
    return bswap_32 (up->u4);
  return up->u4;
}
static inline int32_t
read_4sbyte_unaligned (const void *p)
{
  const union unaligned *up = p;
  if (MACHINE_ENCODING != __BYTE_ORDER)
    return (int32_t) bswap_32 (up->u4);
  return up->s4;
}

static inline uint64_t
read_8ubyte_unaligned (const void *p)
{
  const union unaligned *up = p;
  if (MACHINE_ENCODING != __BYTE_ORDER)
    return bswap_64 (up->u8);
  return up->u8;
}
static inline int64_t
read_8sbyte_unaligned (const void *p)
{
  const union unaligned *up = p;
  if (MACHINE_ENCODING != __BYTE_ORDER)
    return (int64_t) bswap_64 (up->u8);
  return up->s8;
}

#endif	/* allow unaligned */


#define read_2ubyte_unaligned_inc(Addr) \
  ({ uint16_t t_ = read_2ubyte_unaligned (Addr);			      \
     Addr = (__typeof (Addr)) (((uintptr_t) (Addr)) + 2);		      \
     t_; })
#define read_2sbyte_unaligned_inc(Addr) \
  ({ int16_t t_ = read_2sbyte_unaligned (Addr);				      \
     Addr = (__typeof (Addr)) (((uintptr_t) (Addr)) + 2);		      \
     t_; })

#define read_4ubyte_unaligned_inc(Addr) \
  ({ uint32_t t_ = read_4ubyte_unaligned (Addr);			      \
     Addr = (__typeof (Addr)) (((uintptr_t) (Addr)) + 4);		      \
     t_; })
#define read_4sbyte_unaligned_inc(Addr) \
  ({ int32_t t_ = read_4sbyte_unaligned (Addr);				      \
     Addr = (__typeof (Addr)) (((uintptr_t) (Addr)) + 4);		      \
     t_; })

#define read_8ubyte_unaligned_inc(Addr) \
  ({ uint64_t t_ = read_8ubyte_unaligned (Addr);			      \
     Addr = (__typeof (Addr)) (((uintptr_t) (Addr)) + 8);		      \
     t_; })
#define read_8sbyte_unaligned_inc(Addr) \
  ({ int64_t t_ = read_8sbyte_unaligned (Addr);				      \
     Addr = (__typeof (Addr)) (((uintptr_t) (Addr)) + 8);		      \
     t_; })

#endif	/* memory-access.h */