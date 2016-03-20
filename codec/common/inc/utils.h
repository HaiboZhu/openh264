/*!
 * \copy
 *     Copyright (c)  2009-2013, Cisco Systems
 *     All rights reserved.
 *
 *     Redistribution and use in source and binary forms, with or without
 *     modification, are permitted provided that the following conditions
 *     are met:
 *
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in
 *          the documentation and/or other materials provided with the
 *          distribution.
 *
 *     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *     "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *     COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *     BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *     CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *     LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *     ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *     POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * \brief   Tool kits for decoder
 *          ( malloc, realloc, free, log output and PSNR calculation and so on )
 *
 * \date    03/10/2009 Created
 *
 *************************************************************************************
 */
#ifndef WELS_UTILS_H__
#define WELS_UTILS_H__

#include <stdarg.h>
#include "typedefs.h"

#define MAX_LOG_SIZE    1024
#define MAX_MBS_PER_FRAME 36864 //in accordance with max level support in Rec

#define CM_LOG_IF(mask, level, condition, str) \
    if (condition) UTIL_ADAPTER_TRACE(mask, level, str)

#define CM_IF_ERROR_TRACE(condition, str)   CM_LOG_IF(CM_TRACE_LEVEL_ERROR, "ERROR: ", condition, str<<FILE_LINE)
#define CM_IF_WARNING_TRACE(condition, str) CM_LOG_IF(CM_TRACE_LEVEL_WARNING, "WARNING: ", condition, str<<FILE_LINE)
#define CM_IF_INFO_TRACE(condition, str)    CM_LOG_IF(CM_TRACE_LEVEL_INFO, "INFO: ", condition, str)
#define CM_IF_DEBUG_TRACE(condition, str)   CM_LOG_IF(CM_TRACE_LEVEL_DEBUG, "DEBUG: ", condition, str)
#define CM_IF_DETAIL_TRACE(condition, str)  CM_LOG_IF(CM_TRACE_LEVEL_DETAIL, "DETAIL: ", condition, str)

#define LOG_EVERY_N_VARNAME_CONCAT(base, line) base ## line
#define LOG_EVERY_N_VARNAME(base, line) LOG_EVERY_N_VARNAME_CONCAT(base, line)
#define LOG_OCCURRENCES LOG_EVERY_N_VARNAME(occurrences_, __LINE__)
#define LOG_OCCURRENCES_MOD_N LOG_EVERY_N_VARNAME(occurrences_mod_n_, __LINE__)

#define CM_LOG_EVERY_N(mask, level, n, str) \
    static int LOG_OCCURRENCES = 0, LOG_OCCURRENCES_MOD_N = 0; \
    ++LOG_OCCURRENCES; \
    if (++LOG_OCCURRENCES_MOD_N > n) LOG_OCCURRENCES_MOD_N -= n; \
    if (LOG_OCCURRENCES_MOD_N == 1) UTIL_ADAPTER_TRACE(mask, level, str)

#define CM_EVERY_N_ERROR_TRACE(n, str)   CM_LOG_EVERY_N(CM_TRACE_LEVEL_ERROR, "ERROR: ", n, str<<FILE_LINE)
#define CM_EVERY_N_WARNING_TRACE(n, str) CM_LOG_EVERY_N(CM_TRACE_LEVEL_WARNING, "WARNING: ", n, str<<FILE_LINE)
#define CM_EVERY_N_INFO_TRACE(n, str)    CM_LOG_EVERY_N(CM_TRACE_LEVEL_INFO, "INFO: ", n, str)
#define CM_EVERY_N_DEBUG_TRACE(n, str)   CM_LOG_EVERY_N(CM_TRACE_LEVEL_DEBUG, "DEBUG: ", n, str)
#define CM_EVERY_N_DETAIL_TRACE(n, str)  CM_LOG_EVERY_N(CM_TRACE_LEVEL_DETAIL, "DETAIL: ", n, str)

#define CM_LOG_IF_EVERY_N(mask, level, condition, n, str) \
    static int LOG_OCCURRENCES = 0, LOG_OCCURRENCES_MOD_N = 0; \
    ++LOG_OCCURRENCES; \
    if (condition && \
        ((LOG_OCCURRENCES_MOD_N=(LOG_OCCURRENCES_MOD_N + 1) % n) == (1 % n))) \
        UTIL_ADAPTER_TRACE(mask, level, str)

#define CM_IF_EVERY_N_ERROR_TRACE(condition, n, str)   CM_LOG_IF_EVERY_N(CM_TRACE_LEVEL_ERROR, "ERROR: ", condition, n, str<<FILE_LINE)
#define CM_IF_EVERY_N_WARNING_TRACE(condition, n, str) CM_LOG_IF_EVERY_N(CM_TRACE_LEVEL_WARNING, "WARNING: ", condition, n, str<<FILE_LINE)
#define CM_IF_EVERY_N_INFO_TRACE(condition, n, str)    CM_LOG_IF_EVERY_N(CM_TRACE_LEVEL_INFO, "INFO: ", condition, n, str)
#define CM_IF_EVERY_N_DEBUG_TRACE(condition, n, str)   CM_LOG_IF_EVERY_N(CM_TRACE_LEVEL_DEBUG, "DEBUG: ", condition, n, str)
#define CM_IF_EVERY_N_DETAIL_TRACE(condition, n, str)  CM_LOG_IF_EVERY_N(CM_TRACE_LEVEL_DETAIL, "DETAIL: ", condition, n, str)

// WARNING: It is your duty to supply the counter, just give the variable pointer, the macro will modify its value
#define CM_LOG_FIRST_N(mask, level, counter_ptr, n, str) \
  if ((*counter_ptr) < n) { \
    ++(*counter_ptr); \
    UTIL_ADAPTER_TRACE(mask, level, str); }

#define CM_FIRST_N_ERROR_TRACE(counter_ptr, n, str)   CM_LOG_FIRST_N(CM_TRACE_LEVEL_ERROR, "ERROR: ", counter_ptr, n, str<<FILE_LINE)
#define CM_FIRST_N_WARNING_TRACE(counter_ptr, n, str) CM_LOG_FIRST_N(CM_TRACE_LEVEL_WARNING, "WARNING: ", counter_ptr, n, str<<FILE_LINE)
#define CM_FIRST_N_INFO_TRACE(counter_ptr, n, str)    CM_LOG_FIRST_N(CM_TRACE_LEVEL_INFO, "INFO: ", counter_ptr, n, str)
#define CM_FIRST_N_DEBUG_TRACE(counter_ptr, n, str)   CM_LOG_FIRST_N(CM_TRACE_LEVEL_DEBUG, "DEBUG: ", counter_ptr, n, str)
#define CM_FIRST_N_DETAIL_TRACE(counter_ptr, n, str)  CM_LOG_FIRST_N(CM_TRACE_LEVEL_DETAIL, "DETAIL: ", counter_ptr, n, str)

/*
 *  Function pointer declaration for various tool sets
 */
// wels log output
typedef void (*PWelsLogCallbackFunc) (void* pCtx, const int32_t iLevel, const char* kpFmt, va_list argv);

typedef struct TagLogContext {
  PWelsLogCallbackFunc pfLog;
  void* pLogCtx;
  void* pCodecInstance;
} SLogContext;


#ifdef __GNUC__
extern void WelsLog (SLogContext* pCtx, int32_t iLevel, const char* kpFmt, ...) __attribute__ ((__format__ (__printf__,
    3,
    4)));
#else
extern void WelsLog (SLogContext* pCtx, int32_t iLevel, const char* kpFmt, ...);
#endif

/*
 *  PSNR calculation routines
 */
/*!
 *************************************************************************************
 * \brief   PSNR calculation utilization in Wels
 *
 * \param   kpTarPic    target picture to be calculated in Picture pData format
 * \param   kiTarStride stride of target picture pData pBuffer
 * \param   kpRefPic    base referencing picture samples
 * \param   kiRefStride stride of reference picture pData pBuffer
 * \param   kiWidth     picture iWidth in pixel
 * \param   kiHeight    picture iHeight in pixel
 *
 * \return  actual PSNR result;
 *
 * \note    N/A
 *************************************************************************************
 */
float WelsCalcPsnr (const void* kpTarPic,
                    const int32_t kiTarStride,
                    const void* kpRefPic,
                    const int32_t kiRefStride,
                    const int32_t kiWidth,
                    const int32_t kiHeight);


#endif//WELS_UTILS_H__
