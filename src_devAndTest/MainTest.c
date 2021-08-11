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

#include "../src/Comm.h"
#include "../src/NvmMem.h"
#include "../src/Storage.h"
#include "../src/EventHandler.h"

void MainTest_TC_01(void);
void MainTest_OutputCounters(void);

int main(void) {
    uint8_t u8TestVariable = 0U;

    EventHandler_InitializeOnStart();

    printf("main: start\n");
    NvmMem_Write(0x00001000, &u8TestVariable, 2U);
    Comm_SendEventReport(&u8TestVariable, 2U);
    Storage_StoreEventReport(&u8TestVariable, 2U);
    printf("main: end\n\n");

    MainTest_TC_01();

    return 0;
}

void MainTest_TC_01(void)
{
    uint8_t u8TestVariable = 0U;

    printf("TC_01: start\n");
    MainTest_OutputCounters();
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    MainTest_OutputCounters();
    NvmMem_Write(0x00001000, NULL, 2U);
    MainTest_OutputCounters();
    NvmMem_Write(0x00001000, &u8TestVariable, 0U);
    MainTest_OutputCounters();
    printf("TC_01: end\n\n");

    return;
}

void MainTest_OutputCounters(void)
{
    printf("Counter address = %d, counter NULL = %d, counter size = %d\n", EventHandler_GetEventsCounter(E_EVENTHANDLER_SEVERITY_NORMAL, E_EVENTHANDLER_TYPE_ADDRESSRANGE), EventHandler_GetEventsCounter(E_EVENTHANDLER_SEVERITY_MEDIUM, E_EVENTHANDLER_TYPE_NULLARGUMENT), EventHandler_GetEventsCounter(E_EVENTHANDLER_SEVERITY_LOW, E_EVENTHANDLER_TYPE_MINDATALENGTH));
    return;
}
