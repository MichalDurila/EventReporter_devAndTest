/*
 ******************************************************************************
 *                                                                            *
 *                              Michal Durila                                 *
 *                                                                            *
 *                                                                            *
 *                           ALL RIGHTS RESERVED                              *
 *                                                                            *
 ******************************************************************************
 */

/**
 *  @file MainTest.c
 *  @author Michal Durila
 *  @brief This module tests the functionality of event reporting.
 *
 * Copyright 2021 Michal Durila, All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/NvmMem.h"
#include "../src/EventHandler.h"
#include "../src/Timing.h"


static const float64_t m_f64TimeIncrement = 20.0;

static void MainTest_OutputCounters(void);
static void MainTest_OutputStandbyModes(void);
static void MainTest_OutputEnabledReporting(void);
static void MainTest_OutputStatistics(void);
static void MainTest_TC_01(void);
static void MainTest_TC_02(void);
static void MainTest_TC_03(void);


int main(void) {
    EventHandler_InitializeOnStart();
    Timing_SetTime(TIMING_INITIAL_TIME);

    MainTest_TC_01();
    MainTest_TC_02();
    MainTest_TC_03();

    return 0;
}

/**
 * @brief Tests 3 basic types of events
 */
static void MainTest_TC_01(void)
{
    uint8_t au8TestArray[10U];

    printf("TC_01: start\n");
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, au8TestArray, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00001000, NULL, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00001000, au8TestArray, 0U);
    MainTest_OutputStatistics();

    printf("TC_01: end\n\n");
    return;
}

/**
 * @brief Tests the protection against overflow and re-enabling of reporting
 */
static void MainTest_TC_02(void)
{
    uint8_t u8TestVariable = 0U;

    printf("TC_02: start\n");
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + 600.1);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    printf("TC_02: end\n\n");
    return;
}

/**
 * @brief Tests disabling of event reporting
 */
static void MainTest_TC_03(void)
{
    uint8_t u8TestVariable = 0U;

    printf("TC_03: start\n");
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    EventHandler_SetEnabledReporting(E_EVENTHANDLER_TYPE_ADDRESSRANGE, E_FALSE);
    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    EventHandler_SetEnabledReporting(E_EVENTHANDLER_TYPE_ADDRESSRANGE, E_TRUE);
    Timing_SetTime(Timing_GetTime() + m_f64TimeIncrement);
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputStatistics();

    printf("TC_03: end\n\n");
    return;
}

static void MainTest_OutputCounters(void)
{
    printf("Counter address = %d, counter NULL = %d, counter size = %d\n", EventHandler_GetEventsCounter(E_EVENTHANDLER_SEVERITY_NORMAL, E_EVENTHANDLER_TYPE_ADDRESSRANGE), EventHandler_GetEventsCounter(E_EVENTHANDLER_SEVERITY_MEDIUM, E_EVENTHANDLER_TYPE_NULLARGUMENT), EventHandler_GetEventsCounter(E_EVENTHANDLER_SEVERITY_LOW, E_EVENTHANDLER_TYPE_MINDATALENGTH));
    return;
}

static void MainTest_OutputStandbyModes(void)
{
    printf("Standby %d, %d, %d, %d, %d\n", EventHandler_GetStandbyMode(E_EVENTHANDLER_TYPE_NULLARGUMENT), EventHandler_GetStandbyMode(E_EVENTHANDLER_TYPE_MINDATALENGTH), EventHandler_GetStandbyMode(E_EVENTHANDLER_TYPE_ADDRESSRANGE), EventHandler_GetStandbyMode(E_EVENTHANDLER_TYPE_DIVISIONBYZERO), EventHandler_GetStandbyMode(E_EVENTHANDLER_TYPE_UNUPDATEDCONSTANTS));
    return;
}

static void MainTest_OutputEnabledReporting(void)
{
    printf("Enabled Reporting %d, %d, %d, %d, %d\n", EventHandler_GetEnabledReporting(E_EVENTHANDLER_TYPE_NULLARGUMENT), EventHandler_GetEnabledReporting(E_EVENTHANDLER_TYPE_MINDATALENGTH), EventHandler_GetEnabledReporting(E_EVENTHANDLER_TYPE_ADDRESSRANGE), EventHandler_GetEnabledReporting(E_EVENTHANDLER_TYPE_DIVISIONBYZERO), EventHandler_GetEnabledReporting(E_EVENTHANDLER_TYPE_UNUPDATEDCONSTANTS));
    return;
}

static void MainTest_OutputStatistics(void)
{
    MainTest_OutputCounters();
    MainTest_OutputStandbyModes();
    MainTest_OutputEnabledReporting();
    return;
}
