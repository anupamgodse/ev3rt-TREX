/*
 * cyclic_alarm.h
 *
 *  Created on: Jan 24, 2014
 *      Author: liyixiao
 */

#pragma once

#define TNUM_HIRES_ALMID (10)

typedef struct {
    ATR      almatr;     /* 周期ハンドラ属性 */
    intptr_t exinf;      /* 周期ハンドラの拡張情報 */
    ALMHDR   almhdr;     /* 周期ハンドラの先頭番地 */
//    RELTIM      cyctim;     /* 周期ハンドラの起動周期 (microsecond) */
//    RELTIM      cycphs;     /* 周期ハンドラの起動位相 */ not supported
} T_HIRES_CALM;



typedef struct {
    T_HIRES_CALM alminib;    //* Initialization block 
    bool_t       almsta;     //* Is the cyclic started 
    uint32_t     left_ticks; //* Left ticks to call the handler 
} HIRES_ALMCB;

static HIRES_ALMCB hires_almcb_table[TNUM_HIRES_ALMID];


static inline
uint32_t usecs_to_ticks(uint32_t usecs) {
    return usecs / (1000 * TIC_NUME / TIC_DENO);
}

static inline
uint32_t ticks_to_usecs(uint32_t ticks) {
    return ticks * (1000 * TIC_NUME / TIC_DENO);
}

static inline
HIRES_ALMCB* get_control_block(ID id) {
    return &hires_almcb_table[id - 1];
}





/**
 * Return:
 * > 0 ID
 * E_NOID
 */
extern ER_ID acre_hires_alm(const T_HIRES_CALM *pk_hires_calm);

/**
 * @par almtim microseconds
 * Return:
 * E_ID
 * E_OK
 */
extern ER sta_hires_alm(ID hires_almid, RELTIM almtim);

/**
 * Return:
 * E_ID
 * E_OK
 */
extern ER stp_hires_alm(ID almid);

extern void hires_alm_isr(intptr_t exinf);
