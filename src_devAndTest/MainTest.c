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

void TC_01(void);

int main(void) {
    uint8_t u8TestVariable = 0U;

    printf("main: start\n");
    NvmMem_Write(0x00001000, &u8TestVariable, 2U);
    Comm_SendEventReport(&u8TestVariable, 2U);
    Storage_StoreEventReport(&u8TestVariable, 2U);
    printf("main: end\n\n");

    TC_01();

    return 0;
}

void TC_01(void)
{
    uint8_t u8TestVariable = 0U;

    printf("TC_01: start\n");
    NvmMem_Write(0x00000000, &u8TestVariable, 2U);
    NvmMem_Write(0x00001000, NULL, 2U);
    NvmMem_Write(0x00001000, &u8TestVariable, 0U);
    printf("TC_01: end\n\n");

    return;
}
