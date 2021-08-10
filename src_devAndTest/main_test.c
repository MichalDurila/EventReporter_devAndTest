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
 *  @file main_test.c
 *  @author Michal Durila
 *  @brief This module tests the functionality of event reporting.
 *
 * Copyright 2021 Michal Durila, All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/Comm.h"
#include "../src/Modules.h"
#include "../src/NvmMem.h"
#include "../src/Storage.h"

int main(void) {
	uint8_t u8TestVariable;

	printf("main: start\n");
	NvmMem_Write(0x00001000, &u8TestVariable, 2U);
	//Comm_SendEventReport(&u8TestVariable, 2U);
	//Storage_StoreEventReport(&u8TestVariable, 2U);
	printf("main: end\n\n");

	return 0;
}
