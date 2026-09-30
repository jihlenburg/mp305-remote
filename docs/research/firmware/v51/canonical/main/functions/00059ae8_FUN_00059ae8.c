/* Address: 00059ae8; name: FUN_00059ae8; body bytes: 80 */

/* Recovered from stored Thumb pointer at 00065c00; callback identification is inferred until
   reviewed. */

void FUN_00059ae8(void)

{
  int iVar1;
  
  do {
    do {
      while (DAT_1ffe0004 != 0) {
        enter_critical();
        iVar1 = *(int *)(DAT_1ffe0e48 + 0xc);
        FUN_00065666(iVar1 + 4);
        DAT_1ffe0008 = DAT_1ffe0008 + -1;
        DAT_1ffe0004 = DAT_1ffe0004 + -1;
        exit_critical();
        FUN_00059a8e(iVar1);
      }
    } while (DAT_1ffe0d9c < 2);
    DAT_e000ed04 = 0x10000000;
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
  } while( true );
}

