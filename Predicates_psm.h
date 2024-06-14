#define GEOGRAM_PSM
#ifndef GEO_STATIC_LIBS
#define GEO_DYNAMIC_LIBS
#endif
/*
 *  Copyright (c) 2000-2022 Inria
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *  * Neither the name of the ALICE Project-Team nor the names of its
 *  contributors may be used to endorse or promote products derived from this
 *  software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  Contact: Bruno Levy
 *
 *     https://www.inria.fr/fr/bruno-levy
 *
 *     Inria,
 *     Domaine de Voluceau,
 *     78150 Le Chesnay - Rocquencourt
 *     FRANCE
 *
 */


/*
 *  This file is a PSM (pluggable software module)
 *   generated from the distribution of Geogram.
 *
 *  See Geogram documentation on:
 *   http://alice.loria.fr/software/geogram/doc/html/index.html
 *
 *  See documentation of the functions bundled in this PSM on:
 *   http://alice.loria.fr/software/geogram/doc/html/namespaceGEO_1_1PCK.html
 */



/******* extracted from ../api/defs.h *******/

#ifndef GEOGRAM_API_DEFS
#define GEOGRAM_API_DEFS


/*
 * Deactivate warnings about documentation
 * We do that, because CLANG's doxygen parser does not know
 * some doxygen commands that we use (retval, copydoc) and
 * generates many warnings for them...
 */
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command" 
#endif


#if defined(GEO_DYNAMIC_LIBS)
   #if defined(_MSC_VER)
      #define GEO_IMPORT __declspec(dllimport) 
      #define GEO_EXPORT __declspec(dllexport) 
   #elif defined(__GNUC__)
      #define GEO_IMPORT  
      #define GEO_EXPORT __attribute__ ((visibility("default")))
   #else
      #define GEO_IMPORT
      #define GEO_EXPORT
   #endif
#else
   #define GEO_IMPORT
   #define GEO_EXPORT
#endif

#ifdef geogram_EXPORTS
#define GEOGRAM_API GEO_EXPORT
#else
#define GEOGRAM_API GEO_IMPORT
#endif


#define NO_GEOGRAM_API

typedef int GeoMesh;

typedef unsigned char geo_coord_index_t;

/* 
 * If GARGANTUA is defined, then geogram is compiled 
 * with 64 bit indices. 
 */
#ifdef GARGANTUA

#include <stdint.h>

typedef uint64_t geo_index_t;

typedef int64_t geo_signed_index_t;

#else

typedef unsigned int geo_index_t;

typedef int geo_signed_index_t;

#endif

typedef double geo_coord_t;

typedef int geo_boolean;

enum {
    GEO_FALSE = 0,
    GEO_TRUE = 1
};

#endif


/******* extracted from ../basic/common.h *******/

#ifndef GEOGRAM_BASIC_COMMON
#define GEOGRAM_BASIC_COMMON


// iostream should be included before anything else,
// otherwise 'cin', 'cout' and 'cerr' will be uninitialized.
#include <iostream>



namespace GEO {

    enum {
	GEOGRAM_NO_HANDLER = 0,
	GEOGRAM_INSTALL_HANDLERS = 1
    };
    
    void GEOGRAM_API initialize(int flags = GEOGRAM_INSTALL_HANDLERS);

    void GEOGRAM_API terminate();
}


#if (defined(NDEBUG) || defined(GEOGRAM_PSM)) && !defined(GEOGRAM_PSM_DEBUG)
#undef GEO_DEBUG
#undef GEO_PARANOID
#else
#define GEO_DEBUG
#define GEO_PARANOID
#endif

// =============================== LINUX defines ===========================

#if defined(__ANDROID__)
#define GEO_OS_ANDROID
#endif

#if defined(__linux__)

#define GEO_OS_LINUX
#define GEO_OS_UNIX

#ifndef GEO_OS_ANDROID
#define GEO_OS_X11
#endif

#if defined(_OPENMP)
#  define GEO_OPENMP
#endif

#if defined(__INTEL_COMPILER)
#  define GEO_COMPILER_INTEL
#elif defined(__clang__)
#  define GEO_COMPILER_CLANG
#elif defined(__GNUC__)
#  define GEO_COMPILER_GCC
#else
#  error "Unsupported compiler"
#endif

// The following works on GCC and ICC
#if defined(__x86_64)
#  define GEO_ARCH_64
#  define GEO_PROCESSOR_X86
#else
#  define GEO_ARCH_32
#endif

// =============================== WINDOWS defines =========================

#elif defined(_WIN32) || defined(_WIN64)

#define GEO_OS_WINDOWS
#define GEO_PROCESSOR_X86

#if defined(_OPENMP)
#  define GEO_OPENMP
#endif

#if defined(_MSC_VER)
#  define GEO_COMPILER_MSVC
#elif defined(__MINGW32__) || defined(__MINGW64__)
#  define GEO_COMPILER_MINGW
#endif

#if defined(_WIN64)
#  define GEO_ARCH_64
#else
#  define GEO_ARCH_32
#endif

// =============================== APPLE defines ===========================

#elif defined(__APPLE__)

#define GEO_OS_APPLE
#define GEO_OS_UNIX

#if defined(_OPENMP)
#  define GEO_OPENMP
#endif

#if defined(__clang__)
#  define GEO_COMPILER_CLANG
#elif defined(__GNUC__)
#  define GEO_COMPILER_GCC
#else
#  error "Unsupported compiler"
#endif

#if defined(__x86_64) || defined(__ppc64__) || defined(__arm64__) || defined(__aarch64__) || (defined(__riscv) && __riscv_xlen == 64)
#  define GEO_ARCH_64
#else
#  define GEO_ARCH_32
#endif

// =============================== Emscripten defines  ======================

#elif defined(__EMSCRIPTEN__)

#define GEO_OS_UNIX
#define GEO_OS_LINUX
#define GEO_OS_EMSCRIPTEN
#define GEO_ARCH_64
#define GEO_COMPILER_EMSCRIPTEN
#define GEO_COMPILER_CLANG

// =============================== Unsupported =============================
#else
#error "Unsupported operating system"
#endif

#if defined(GEO_COMPILER_GCC)   || \
    defined(GEO_COMPILER_CLANG) || \
    defined(GEO_COMPILER_MINGW) || \
    defined(GEO_COMPILER_EMSCRIPTEN)
#define GEO_COMPILER_GCC_FAMILY
#endif

#ifdef DOXYGEN_ONLY
// Keep doxygen happy
#define GEO_OS_WINDOWS
#define GEO_OS_APPLE
#define GEO_OS_ANDROID
#define GEO_ARCH_32
#define GEO_COMPILER_INTEL
#define GEO_COMPILER_MSVC
#endif

#define CPP_CONCAT_(A, B) A ## B

#define CPP_CONCAT(A, B) CPP_CONCAT_(A, B)

#if defined(GOMGEN)
#define GEO_NORETURN
#elif defined(GEO_COMPILER_GCC_FAMILY) || \
      defined(GEO_COMPILER_INTEL) 
#define GEO_NORETURN __attribute__((noreturn))
#else
#define GEO_NORETURN
#endif

#if defined(GOMGEN)
#define GEO_NORETURN_DECL 
#elif defined(GEO_COMPILER_MSVC)
#define GEO_NORETURN_DECL __declspec(noreturn)
#else
#define GEO_NORETURN_DECL 
#endif

#if defined(GEO_COMPILER_CLANG) || defined(GEO_COMPILER_EMSCRIPTEN)
#if __has_feature(cxx_noexcept)
#define GEO_NOEXCEPT noexcept
#endif
#endif

// For Graphite GOM generator (swig is confused by throw() specifier) 
#ifdef GOMGEN 
#define GEO_NOEXCEPT
#endif

#ifndef GEO_NOEXCEPT
#define GEO_NOEXCEPT throw()
#endif

#define FOR(I,UPPERBND) for(index_t I = 0; I<index_t(UPPERBND); ++I)

// Silence warnings for alloca()
// We use it at different places to allocate objects on the stack
// (for instance, in multi-precision predicates).
#ifdef GEO_COMPILER_CLANG
#pragma GCC diagnostic ignored "-Walloca"
#endif

#endif


/******* extracted from ../basic/argused.h *******/

#ifndef GEOGRAM_BASIC_ARGUSED
#define GEOGRAM_BASIC_ARGUSED



namespace GEO {

    template <class T>
    inline void geo_argused(const T&) {
    }
}

#endif


/******* extracted from ../basic/numeric.h *******/

#ifndef GEOGRAM_BASIC_NUMERIC
#define GEOGRAM_BASIC_NUMERIC

#include <cmath>
#include <float.h>
#include <limits.h>
#include <algorithm> // for std::min / std::max
#include <stdint.h>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


namespace GEO {

    enum Sign {
        
        NEGATIVE = -1,
        
        ZERO = 0,
        
        POSITIVE = 1
    };

    template <class T>
    inline Sign geo_sgn(const T& x) {
        return (x > 0) ? POSITIVE : (
            (x < 0) ? NEGATIVE : ZERO
        );
    }

    template <class T>
    inline Sign geo_cmp(const T& a, const T& b) {
        return Sign((a > b) * POSITIVE + (a < b) * NEGATIVE);
    }
    
    namespace Numeric {

        
        typedef void* pointer;

        
        typedef int8_t int8;

        
        typedef int16_t int16;

        
        typedef int32_t int32;

        
        typedef int64_t int64;

        
        typedef uint8_t uint8;

        
        typedef uint16_t uint16;

        
        typedef uint32_t uint32;

        
        typedef uint64_t uint64;

        
        typedef float float32;

        
        typedef double float64;

        inline float32 max_float32() {
            return std::numeric_limits<float32>::max();
        }

        inline float32 min_float32() {
            // Note: numeric_limits<>::min() is not
            // what we want (it returns the smallest
            // positive non-denormal).
            return -max_float32();
        }

        inline float64 max_float64() {
            return std::numeric_limits<float64>::max();
        }

        inline float64 min_float64() {
            // Note: numeric_limits<>::min() is not
            // what we want (it returns the smallest
            // positive non-denormal).
            return -max_float64();
        }

        bool GEOGRAM_API is_nan(float32 x);

        bool GEOGRAM_API is_nan(float64 x);

        void GEOGRAM_API random_reset();

        int32 GEOGRAM_API random_int32();

        float32 GEOGRAM_API random_float32();

        float64 GEOGRAM_API random_float64();

        template <class T, bool is_numeric>
        struct LimitsHelper : std::numeric_limits<T> {
        };

        template <class T>
        struct LimitsHelper<T, true> : std::numeric_limits<T> {
            
            static const size_t size = sizeof(T);
            
            static const size_t numbits = 8 * sizeof(T);
        };

        template <class T>
        struct Limits : 
            LimitsHelper<T, std::numeric_limits<T>::is_specialized> {
        };

        template <class T> inline void optimize_number_representation(T& x) {
            geo_argused(x);
        }

        template <class T> inline Sign ratio_compare(
            const T& a_num, const T& a_denom, const T& b_num, const T& b_denom
        ) {
            if(a_denom == b_denom) {
                return Sign(geo_cmp(a_num,b_num)*geo_sgn(a_denom));
            }
            return Sign(
                geo_cmp(a_num*b_denom, b_num*a_denom) *
                geo_sgn(a_denom) * geo_sgn(b_denom)
            );
        }
    }

    


    template <class T>
    inline T geo_sqr(T x) {
        return x * x;
    }

    template <class T>
    inline void geo_clamp(T& x, T min, T max) {
        if(x < min) {
            x = min;
        } else if(x > max) {
            x = max;
        }
    }

    typedef geo_index_t index_t;

    inline index_t max_index_t() {
        return std::numeric_limits<index_t>::max();
    }

    typedef geo_signed_index_t signed_index_t;

    inline signed_index_t max_signed_index_t() {
        return std::numeric_limits<signed_index_t>::max();
    }

    inline signed_index_t min_signed_index_t() {
        return std::numeric_limits<signed_index_t>::min();
    }

    typedef geo_coord_index_t coord_index_t;

    inline double round(double x) {
	return ((x - floor(x)) > 0.5 ? ceil(x) : floor(x));
    }

    
    
    static constexpr index_t NO_INDEX = index_t(-1);
    
    
}

#endif


/******* extracted from ../basic/psm.h *******/

#ifndef GEOGRAM_BASIC_PSM
#define GEOGRAM_BASIC_PSM


#include <assert.h>
#include <iostream>
#include <string>

#ifndef GEOGRAM_PSM
#define GEOGRAM_PSM
#endif

#ifndef GEOGRAM_BASIC_ASSERT

#define geo_assert(x) assert(x)
#define geo_range_assert(x, min_val, max_val) \
    assert((x) >= (min_val) && (x) <= (max_val))
#define geo_assert_not_reached assert(0)

#ifdef GEO_DEBUG
#define geo_debug_assert(x) assert(x)
#define geo_debug_range_assert(x, min_val, max_val) \
    assert((x) >= (min_val) && (x) <= (max_val))
#else
#define geo_debug_assert(x) 
#define geo_debug_range_assert(x, min_val, max_val)
#endif

#ifdef GEO_PARANOID
#define geo_parano_assert(x) geo_assert(x)
#define geo_parano_range_assert(x, min_val, max_val) \
    geo_range_assert(x, min_val, max_val)
#else
#define geo_parano_assert(x)
#define geo_parano_range_assert(x, min_val, max_val)
#endif

#endif

#ifndef geo_cite
#define geo_cite(x)
#endif

#ifndef geo_cite_with_info
#define geo_cite_with_info(x,y)
#endif

#ifndef GEOGRAM_BASIC_LOGGER

namespace GEO {
    namespace Logger {
        inline std::ostream& out(const std::string& name) {
            return std::cout << " [" << name << "]";
        }

        inline std::ostream& err(const std::string& name) {
            return std::cerr << "E[" << name << "]";
        }

        inline std::ostream& warn(const std::string& name) {
            return std::cerr << "W[" << name << "]";
        }
    }
    
}

#endif

#ifndef FPG_UNCERTAIN_VALUE
#define FPG_UNCERTAIN_VALUE 0
#endif

#define GEOGRAM_WITH_PDEL

#endif

/******* extracted from ../basic/thread_sync.h *******/

#ifndef GEOGRAM_BASIC_THREAD_SYNC
#define GEOGRAM_BASIC_THREAD_SYNC


#include <vector>
#include <atomic>

// On Windows/MSCV, we need to use a special implementation
// of spinlocks because std::atomic_flag in MSVC's stl does
// not fully implement the norm (lacks a constructor).
#ifdef GEO_OS_WINDOWS
#include <windows.h>
#include <intrin.h>
#pragma intrinsic(_InterlockedCompareExchange16)
#pragma intrinsic(_WriteBarrier)
#endif

// On MacOS, I get many warnings with atomic_flag initialization,
// such as std::atomic_flag f = ATOMIC_FLAG_INIT
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wbraced-scalar-init"
#endif

inline void geo_pause() {
#ifdef GEO_OS_WINDOWS
    YieldProcessor();
#else
#  ifdef GEO_PROCESSOR_X86
#    ifdef __ICC
    _mm_pause();
#    else
    __builtin_ia32_pause();
#    endif
#  endif
#endif
}



#ifdef GEO_OS_WINDOWS

// Windows-specific spinlock implementation.
// I'd have prefered to use std::atomic_flag for everybody,
// unfortunately atomic_flag's constructor is not implemented in MSCV's stl,
// so we reimplement them using atomic compare-exchange functions...

namespace GEO {
    namespace Process {
        
        typedef short spinlock;

        
#       define GEOGRAM_SPINLOCK_INIT 0
        inline void acquire_spinlock(volatile spinlock& x) {
            while(_InterlockedCompareExchange16(&x, 1, 0) == 1) {
                // Intel recommends to have a PAUSE asm instruction
                // in the spinlock loop. Under MSVC/Windows,
                // YieldProcessor() is a macro that calls the
                // (undocumented) _mm_pause() intrinsic function
                // that generates a PAUSE opcode.
                YieldProcessor();
            }
            // We do not need _ReadBarrier() here since
            // _InterlockedCompareExchange16
            // "acts as a full barrier in VC2005" according to the doc
        }

        inline void release_spinlock(volatile spinlock& x) {
            _WriteBarrier(); // prevents compiler reordering
            x = 0;
        }
        
    }
}



#else

namespace GEO {
    namespace Process {

        
        // Note: C++20 does not need it anymore, in C++20
        // std::atomic_flag's constructor initializes it,
        // we keep it because
        // - we are using C++17
        // - the Windows implementation that uses integers rather than
        //   std::atomic_flag needs an initialization value.
#define GEOGRAM_SPINLOCK_INIT ATOMIC_FLAG_INIT 

        typedef std::atomic_flag spinlock;

        inline void acquire_spinlock(volatile spinlock& x) {
            for (;;) {
                if (!x.test_and_set(std::memory_order_acquire)) {
                    break;
                }
// If compiling in C++20 we can be slightly more efficient when spinning
// (avoid unrequired atomic operations, just "peek" the flag)
#if defined(__cpp_lib_atomic_flag_test)                
                while (x.test(std::memory_order_relaxed)) 
#endif
                    geo_pause();
            }            
        }

        inline void release_spinlock(volatile spinlock& x) {
            x.clear(std::memory_order_release); 
        }
        
    }
}
#endif



namespace GEO {
    namespace Process {
    
        class BasicSpinLockArray {
        public:
            BasicSpinLockArray() : spinlocks_(nullptr), size_(0) {
            }

            BasicSpinLockArray(index_t size_in) : spinlocks_(nullptr), size_(0) {
                resize(size_in);
            }

            BasicSpinLockArray(const BasicSpinLockArray& rhs) = delete;

            BasicSpinLockArray& operator=(
                const BasicSpinLockArray& rhs
            ) = delete;
            
            void resize(index_t size_in) {
                delete[] spinlocks_;
                spinlocks_ = new spinlock[size_in];
                size_ = size_in;
                // Need to initialize the spinlocks to false (dirty !)
                // (maybe use placement new on each item..., to be tested)
                for(index_t i=0; i<size_; ++i) {
                    Process::release_spinlock(spinlocks_[i]);
                }
            }

            void clear() {
                delete[] spinlocks_;
                spinlocks_ = nullptr;
            }

            index_t size() const {
                return size_;
            }

            void acquire_spinlock(index_t i) {
                geo_debug_assert(i < size());
                GEO::Process::acquire_spinlock(spinlocks_[i]);
            }

            void release_spinlock(index_t i) {
                geo_debug_assert(i < size());
                GEO::Process::release_spinlock(spinlocks_[i]);
            }

        private:
            // Cannot use a std::vector because std::atomic_flag does not
            // have copy ctor nor assignment operator.
            spinlock* spinlocks_;
            index_t size_;
        };
    }
}



namespace GEO {
    namespace Process {

        class CompactSpinLockArray {
        public:
            CompactSpinLockArray() : spinlocks_(nullptr), size_(0) {
            }

            CompactSpinLockArray(index_t size_in) : spinlocks_(nullptr),size_(0){
                resize(size_in);
            }

            ~CompactSpinLockArray() {
                clear();
            }
            
            CompactSpinLockArray(const CompactSpinLockArray& rhs) = delete;

            CompactSpinLockArray& operator=(
                const CompactSpinLockArray& rhs
            ) = delete;
            
            void resize(index_t size_in) {
                if(size_ != size_in) {
                    size_ = size_in;
                    index_t nb_words = (size_ >> 5) + 1;
                    delete[] spinlocks_;
                    spinlocks_ = new std::atomic<uint32_t>[nb_words];
                    for(index_t i=0; i<nb_words; ++i) {
                        // Note: std::atomic_init() is deprecated in C++20
                        // that can initialize std::atomic through its
                        // non-default constructor. We'll need to do something
                        // else when we'll switch to C++20 (placement new...)
                        std::atomic_init(&spinlocks_[i],0u);
                    }
                }
// Test at compile time that we are using atomic uint32_t operations (and not
// using an additional lock which would be catastrophic in terms of performance)
#ifdef __cpp_lib_atomic_is_always_lock_free                
                static_assert(std::atomic<uint32_t>::is_always_lock_free);
#else
// If we cannot test that at compile time, we test that at runtime in debug
// mode (so that we will be notified in the non-regression test if one of
// the platforms has the problem, which is very unlikely though...)
                geo_debug_assert(size_ == 0 || spinlocks_[0].is_lock_free());
#endif                
            }

            index_t size() const {
                return size_;
            }

            void clear() {
                delete[] spinlocks_;
                size_ = 0;
            }

            void acquire_spinlock(index_t i) {
                geo_debug_assert(i < size());
                index_t  w = i >> 5;
                uint32_t b = uint32_t(i & 31);
                uint32_t mask = (1u << b);
                while(
                    (spinlocks_[w].fetch_or(
                        mask, std::memory_order_acquire
                    ) & mask) != 0
                ) {
                    geo_pause();
                }
            }

            void release_spinlock(index_t i) {
                geo_debug_assert(i < size());
                index_t  w = i >> 5;
                uint32_t b = uint32_t(i & 31);
                uint32_t mask = ~(1u << b);
                spinlocks_[w].fetch_and(mask, std::memory_order_release);
            }

        private:
            // Cannot use a std::vector because std::atomic<> does not
            // have copy ctor nor assignment operator.
            std::atomic<uint32_t>* spinlocks_;
            index_t size_;
        };
        
    }
}



namespace GEO {
    namespace Process {
        typedef CompactSpinLockArray SpinLockArray;
    }
}



#endif


/******* extracted from ../basic/determinant.h *******/

#ifndef GEOGRAM_BASIC_DETERMINANT
#define GEOGRAM_BASIC_DETERMINANT



namespace GEO {

    

    template <class T>
    inline T det2x2(
        const T& a11, const T& a12,                    
        const T& a21, const T& a22
    ) {                                 
        return a11*a22-a12*a21 ;
    }

    template <class T>    
    inline T det3x3(
        const T& a11, const T& a12, const T& a13,                
        const T& a21, const T& a22, const T& a23,                
        const T& a31, const T& a32, const T& a33
    ) {
    return
         a11*det2x2(a22,a23,a32,a33)   
        -a21*det2x2(a12,a13,a32,a33)   
        +a31*det2x2(a12,a13,a22,a23);
    }   


    template <class T>    
    inline T det4x4(
        const T& a11, const T& a12, const T& a13, const T& a14,
        const T& a21, const T& a22, const T& a23, const T& a24,               
        const T& a31, const T& a32, const T& a33, const T& a34,  
        const T& a41, const T& a42, const T& a43, const T& a44  
    ) {
        T m12 = a21*a12 - a11*a22;
        T m13 = a31*a12 - a11*a32;
        T m14 = a41*a12 - a11*a42;
        T m23 = a31*a22 - a21*a32;
        T m24 = a41*a22 - a21*a42;
        T m34 = a41*a32 - a31*a42;

        T m123 = m23*a13 - m13*a23 + m12*a33;
        T m124 = m24*a13 - m14*a23 + m12*a43;
        T m134 = m34*a13 - m14*a33 + m13*a43;
        T m234 = m34*a23 - m24*a33 + m23*a43;
        
        return (m234*a14 - m134*a24 + m124*a34 - m123*a44);
    }   
}

#endif

/******* extracted from PCK.h *******/

#ifndef GEOGRAM_NUMERICS_PCK
#define GEOGRAM_NUMERICS_PCK

#include <functional>
#include <algorithm>
#include <atomic>


// Uncomment to get full reporting on predicate statistics
// (but has a non-negligible impact on performance)
// For instance, Early Universe Reconstruction with 2M points:
// with PCK_STATS: 6'36   without PCK_STATS: 3'38

//#define PCK_STATS

namespace GEO {

    namespace PCK {

        
#ifdef PCK_STATS
        class GEOGRAM_API PredicateStats {
        public:
            PredicateStats(const char* name);
            void log_invoke() {
                ++invoke_count_;
            }
            void log_exact() {
                ++exact_count_;
            }
            void log_SOS() {
                ++SOS_count_;
            }
            void show_stats();
            static void show_all_stats();
        private:
            static PredicateStats* first_;
            PredicateStats* next_;
            const char* name_;
            std::atomic<Numeric::int64> invoke_count_;
            std::atomic<Numeric::int64> exact_count_;
            std::atomic<Numeric::int64> SOS_count_;
        };
#else
        class PredicateStats {
        public:
            PredicateStats(const char* name) {
                geo_argused(name);
            }
            void log_invoke() {
            }
            void log_exact() {
            }
            void log_SOS() {
            }
            static void show_all_stats() {
                Logger::out("Stats") << "Compiled without PCK_STAT (no stats)"
                                     << std::endl;
            }
        };
#endif

        
#define SOS_result(x) [&]()->Sign { return Sign(x); }

        template <
            class POINT, class COMPARE,
            class FUNC1, class FUNC2, class FUNC3, class FUNC4
            > inline Sign SOS(
                COMPARE compare,
                const POINT& p1, FUNC1 sos_p1,
                const POINT& p2, FUNC2 sos_p2,
                const POINT& p3, FUNC3 sos_p3,
                const POINT& p4, FUNC4 sos_p4
            ) {
            static constexpr int N = 4;
            Sign result = ZERO;
            const POINT* p[N] = {&p1, &p2, &p3, &p4};
            std::sort(
                p, p+N,
                [compare](const POINT* A, const POINT* B)->bool{
                    return compare(*A,*B);
                }
            );
            for(int i=0; i<N; ++i) {
                if(p[i] == &p1) {
                    result = sos_p1();
                    if(result != ZERO) {
                        return result;
                    }
                }
                if(p[i] == &p2) {
                    result = sos_p2();
                    if(result != ZERO) {
                        return result;
                    }
                }
                if(p[i] == &p3) {
                    result = sos_p3();
                    if(result != ZERO) {
                        return result;
                    }
                }
                if(p[i] == &p4) {
                    result = sos_p4();
                    if(result != ZERO) {
                        return result;
                    }
                }
            }
            geo_assert_not_reached;
        }

    }
}

#endif

/******* extracted from predicates.h *******/

#ifndef GEOGRAM_NUMERICS_PREDICATES
#define GEOGRAM_NUMERICS_PREDICATES




namespace GEO {

    namespace PCK {

	enum SOSMode { SOS_ADDRESS, SOS_LEXICO };

	void GEOGRAM_API set_SOS_mode(SOSMode m);

	SOSMode GEOGRAM_API get_SOS_mode();
	
        Sign GEOGRAM_API side1_SOS(
            const double* p0, const double* p1,
            const double* q0,
            coord_index_t DIM
        );

        Sign GEOGRAM_API side2_SOS(
            const double* p0, const double* p1, const double* p2,
            const double* q0, const double* q1,
            coord_index_t DIM
        );

        Sign GEOGRAM_API side3_SOS(
            const double* p0, const double* p1, 
            const double* p2, const double* p3,
            const double* q0, const double* q1, const double* q2,
            coord_index_t DIM
        );

        Sign GEOGRAM_API side3_3dlifted_SOS(
            const double* p0, const double* p1, 
            const double* p2, const double* p3,
            double h0, double h1, double h2, double h3,
            const double* q0, const double* q1, const double* q2,
	    bool SOS=true
        );
        
        Sign GEOGRAM_API side4_SOS(
            const double* p0,
            const double* p1, const double* p2,
            const double* p3, const double* p4,
            const double* q0, const double* q1,
            const double* q2, const double* q3,
            coord_index_t DIM
        );


        Sign GEOGRAM_API side4_3d(
            const double* p0,
            const double* p1, const double* p2,
            const double* p3, const double* p4
        );

        Sign GEOGRAM_API side4_3d_SOS(
            const double* p0, const double* p1, 
            const double* p2, const double* p3, const double* p4
        );
       
         Sign GEOGRAM_API in_sphere_3d_SOS(
            const double* p0, const double* p1, 
            const double* p2, const double* p3,
            const double* p4
         );


         Sign GEOGRAM_API in_circle_2d_SOS(
             const double* p0, const double* p1, const double* p2,
             const double* p3
         );

	 
         Sign GEOGRAM_API in_circle_3d_SOS(
             const double* p0, const double* p1, const double* p2,
             const double* p3
         );


        Sign GEOGRAM_API in_circle_3dlifted_SOS(
            const double* p0, const double* p1, const double* p2,
            const double* p3,
            double h0, double h1, double h2, double h3,
	    bool SOS=true
        );
        
        Sign GEOGRAM_API orient_2d(
            const double* p0, const double* p1, const double* p2
        );


#ifndef GEOGRAM_PSM        
        inline Sign orient_2d(
            const vec2& p0, const vec2& p1, const vec2& p2
        ) {
            return orient_2d(p0.data(),p1.data(),p2.data());
        }
#endif

        Sign GEOGRAM_API orient_2dlifted_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3, 
            double h0, double h1, double h2, double h3
        );
	
        
        Sign GEOGRAM_API orient_3d(
            const double* p0, const double* p1,
            const double* p2, const double* p3
        );


#ifndef GEOGRAM_PSM
        inline Sign orient_3d(
            const vec3& p0, const vec3& p1,
            const vec3& p2, const vec3& p3
        ) {
            return orient_3d(p0.data(),p1.data(),p2.data(),p3.data());
        }
#endif
        
        Sign GEOGRAM_API orient_3dlifted(
            const double* p0, const double* p1,
            const double* p2, const double* p3, const double* p4,
            double h0, double h1, double h2, double h3, double h4
        );


        Sign GEOGRAM_API orient_3dlifted_SOS(
            const double* p0, const double* p1,
            const double* p2, const double* p3, const double* p4,
            double h0, double h1, double h2, double h3, double h4
        );


	Sign GEOGRAM_API det_3d(
	    const double* p0, const double* p1, const double* p2
	);

	Sign GEOGRAM_API det_4d(
	    const double* p0, const double* p1,
	    const double* p2, const double* p3
	);

	Sign GEOGRAM_API det_compare_4d(
	    const double* p0, const double* p1,
	    const double* p2, const double* p3,
	    const double* p4
	);
	
	bool GEOGRAM_API aligned_3d(
	    const double* p0, const double* p1, const double* p2
	);
	
	Sign GEOGRAM_API dot_3d(
	    const double* p0, const double* p1, const double* p2
	);

#ifndef GEOGRAM_PSM

	inline bool aligned_3d(
	    const vec3& p0, const vec3& p1, const vec3& p2
	) {
            return aligned_3d(p0.data(), p1.data(), p2.data());
        }
        
	inline Sign dot_3d(
	    const vec3& p0, const vec3& p1, const vec3& p2
	) {
            return dot_3d(p0.data(), p1.data(), p2.data());
        }
#endif
	
	Sign GEOGRAM_API dot_compare_3d(
	    const double* v0, const double* v1, const double* v2
	);
	
	bool points_are_identical_2d(
	    const double* p1,
	    const double* p2
	);
    
	bool GEOGRAM_API points_are_identical_3d(
	    const double* p1,
	    const double* p2
	);

	bool GEOGRAM_API points_are_colinear_3d(
	    const double* p1,
	    const double* p2,
	    const double* p3
        );

	inline Sign orient_3d_inexact(
	    const double* p0, const double* p1,
	    const double* p2, const double* p3
	) {
	    double a11 = p1[0] - p0[0] ;
	    double a12 = p1[1] - p0[1] ;
	    double a13 = p1[2] - p0[2] ;
	    
	    double a21 = p2[0] - p0[0] ;
	    double a22 = p2[1] - p0[1] ;
	    double a23 = p2[2] - p0[2] ;
	    
	    double a31 = p3[0] - p0[0] ;
	    double a32 = p3[1] - p0[1] ;
	    double a33 = p3[2] - p0[2] ;
	    
	    double Delta = det3x3(
		a11,a12,a13,
		a21,a22,a23,
		a31,a32,a33
	    );

	    return geo_sgn(Delta);
	}
	
        void GEOGRAM_API show_stats();

        void GEOGRAM_API initialize();

        void GEOGRAM_API terminate();
    }
}

#endif

