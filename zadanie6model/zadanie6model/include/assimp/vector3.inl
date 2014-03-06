/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2012, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file  aiVector3D.inl
 *  @brief Inline implementation of aiVector3t<TReal> operators
 */
#ifndef AI_VECTOR3D_INL_INC
#define AI_VECTOR3D_INL_INC

#ifdef __cplusplus
#include "vector3.h"

// ------------------------------------------------------------------------------------------------
/** Transformation of a vector by a 3x3 matrix */
template <typename TReal>
inline aiVector3t<TReal> operator * (const aiMatrix3x3t<TReal>& pMatrix, const aiVector3t<TReal>& pVector)
{
	aiVector3t<TReal> res;
	res.x = pMatrix.a1 * pVector.x + pMatrix.a2 * pVector.y + pMatrix.a3 * pVector.z;
	res.y = pMatrix.b1 * pVector.x + pMatrix.b2 * pVector.y + pMatrix.b3 * pVector.z;
	res.z = pMatrix.c1 * pVector.x + pMatrix.c2 * pVector.y + pMatrix.c3 * pVector.z;
	return res;
}

// ------------------------------------------------------------------------------------------------
/** Transformation of a vector by a 4x4 matrix */
template <typename TReal>
inline aiVector3t<TReal> operator * (const aiMatrix4x4t<TReal>& pMatrix, const aiVector3t<TReal>& pVector)
{
	aiVector3t<TReal> res;
	res.x = pMatrix.a1 * pVector.x + pMatrix.a2 * pVector.y + pMatrix.a3 * pVector.z + pMatrix.a4;
	res.y = pMatrix.b1 * pVector.x + pMatrix.b2 * pVector.y + pMatrix.b3 * pVector.z + pMatrix.b4;
	res.z = pMatrix.c1 * pVector.x + pMatrix.c2 * pVector.y + pMatrix.c3 * pVector.z + pMatrix.c4;
	return res;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
template <typename TOther>
aiVector3t<TReal>::operator aiVector3t<TOther> () const {
	return aiVector3t<TOther>(static_cast<TOther>(x),static_cast<TOther>(y),static_cast<TOther>(z));
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE void aiVector3t<TReal>::Set( TReal pX, TReal pY, TReal pZ) { 
	x = pX; y = pY; z = pZ; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE TReal aiVector3t<TReal>::SquareLength() const {
	return x*x + y*y + z*z; 
}
// -----------------------------------------------------