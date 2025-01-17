// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "build/build_config.h"

#if defined(ARCH_CPU_X86_FAMILY) && !defined(OS_MACOSX)

#include "third_party/blink/renderer/platform/audio/cpu/x86/vector_math_avx.h"

#include <immintrin.h>

namespace blink {
namespace vector_math {
namespace AVX {

using MType = __m256;

}  // namespace AVX
}  // namespace vector_math
}  // namespace blink

#define MM_PS(name) _mm256_##name##_ps
#define VECTOR_MATH_SIMD_NAMESPACE_NAME AVX

#include "third_party/blink/renderer/platform/audio/cpu/x86/vector_math_impl.h"

#undef MM_PS
#undef VECTOR_MATH_SIMD_NAMESPACE_NAME

#endif  // defined(ARCH_CPU_X86_FAMILY) && !defined(OS_MACOSX)
