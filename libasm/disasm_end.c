/* Release descriptor for disassembler.
   Copyright (C) 2005 Red Hat, Inc.
   Written by Ulrich Drepper <drepper@redhat.com>, 2005.

   This program is Open Source software; you can redistribute it and/or
   modify it under the terms of the Open Software License version 1.0 as
   published by the Open Source Initiative.

   You should have received a copy of the Open Software License along
   with this program; if not, you may obtain a copy of the Open Software
   License version 1.0 from http://www.opensource.org/licenses/osl.php or
   by writing the Open Source Initiative c/o Lawrence Rosen, Esq.,
   3001 King Ranch Road, Ukiah, CA 95482.   */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>

#include "libasmP.h"


int
disasm_end (DisasmCtx_t *ctx)
{
  free (ctx);

  return 0;
}