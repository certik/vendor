/* ---------------------------------------------------------------------
 *
 * -- Automatically Tuned Linear Algebra Software (ATLAS)
 *    (C) Copyright 2000 All Rights Reserved
 *
 * -- ATLAS routine -- Version 3.2 -- December 25, 2000
 *
 * Author         : Antoine P. Petitet
 * Originally developed at the University of Tennessee,
 * Innovative Computing Laboratory, Knoxville TN, 37996-1301, USA.
 *
 * ---------------------------------------------------------------------
 *
 * -- Copyright notice and Licensing terms:
 *
 *  Redistribution  and  use in  source and binary forms, with or without
 *  modification, are  permitted provided  that the following  conditions
 *  are met:
 *
 * 1. Redistributions  of  source  code  must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce  the above copyright
 *    notice,  this list of conditions, and the  following disclaimer in
 *    the documentation and/or other materials provided with the distri-
 *    bution.
 * 3. The name of the University,  the ATLAS group,  or the names of its
 *    contributors  may not be used to endorse or promote products deri-
 *    ved from this software without specific written permission.
 *
 * -- Disclaimer:
 *
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO,  PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEO-
 * RY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (IN-
 * CLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ---------------------------------------------------------------------
 */
/*
 * Include files
 */
#include "atlas_refmisc.h"
#include "atlas_reflvl3.h"
#include "atlas_reflevel3.h"

void ATL_crefsyr2kLN
(
   const int                  N,
   const int                  K,
   const float                * ALPHA,
   const float                * A,
   const int                  LDA,
   const float                * B,
   const int                  LDB,
   const float                * BETA,
   float                      * C,
   const int                  LDC
)
{
/*
 * Purpose
 * =======
 *
 * ATL_crefsyr2kLN( ... )
 *
 * <=>
 *
 * ATL_crefsyr2k( AtlasLower, AtlasNoTrans, ... )
 *
 * See ATL_crefsyr2k for details.
 *
 * ---------------------------------------------------------------------
 */
/*
 * .. Local Variables ..
 */
   float                      t0_i, t0_r, t1_i, t1_r;
   int                        i, iail, iaj, iajl, ibil, ibj, ibjl, icij,
                              j, jal, jbl, jcj, l, lda2 = ( LDA << 1 ),
                              ldb2 = ( LDB << 1 ), ldc2 = ( LDC << 1 );
/* ..
 * .. Executable Statements ..
 *
 */
   for( j = 0,      iaj  = 0, ibj  = 0, jcj  = 0;
        j < N; j++, iaj += 2, ibj += 2, jcj += ldc2 )
   {
      Mcvscal( N-j, BETA, C+(j << 1)+jcj, 1 );

      for( l = 0,      iajl  = iaj,  ibjl  = ibj,  jal   = 0,    jbl  = 0;
           l < K; l++, iajl += lda2, ibjl += ldb2, jal  += lda2, jbl  += ldb2 )
      {
         Mmul( ALPHA[0], ALPHA[1], B[ibjl], B[ibjl+1], t0_r, t0_i );
         Mmul( ALPHA[0], ALPHA[1], A[iajl], A[iajl+1], t1_r, t1_i );
         for( i = j, iail  = (j << 1)+jal, ibil  = (j << 1)+jbl,
                     icij  = (j << 1)+jcj;
              i < N; i++, iail += 2, ibil += 2, icij += 2 )
         {
            Mmla( A[iail], A[iail+1], t0_r, t0_i, C[icij], C[icij+1] );
            Mmla( B[ibil], B[ibil+1], t1_r, t1_i, C[icij], C[icij+1] );
         }
      }
   }
/*
 * End of ATL_crefsyr2kLN
 */
}
