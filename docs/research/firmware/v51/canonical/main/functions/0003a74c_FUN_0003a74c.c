/* Address: 0003a74c; name: FUN_0003a74c; body bytes: 60 */

/* Recovered from stored Thumb pointer at 0007a510; callback identification is inferred until
   reviewed. */

bool FUN_0003a74c(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    if (*(int *)(param_1 + 4) != 0) {
      iVar1 = FUN_0003f184();
      iVar1 = FUN_0004f42e(param_1 + 0x24,*(undefined4 *)(param_1 + 0x10),iVar1 + 4);
      if (iVar1 != 0) {
        FUN_0004a152(param_1 + 0x30,4);
        *(undefined4 *)(param_1 + 0x3c) = 0x276bd;
      }
      return iVar1 != 0;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

