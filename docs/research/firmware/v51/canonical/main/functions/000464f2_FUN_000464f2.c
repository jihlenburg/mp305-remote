/* Address: 000464f2; name: FUN_000464f2; body bytes: 128 */

void FUN_000464f2(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(undefined4 *)(param_1 + 0x3c) = 0;
  for (iVar1 = 0; *(char *)(param_2 + iVar1) != '\0'; iVar1 = iVar1 + 1) {
    if (*(char *)(param_2 + iVar1) == '\n') {
      *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
    }
  }
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  iVar1 = FUN_00050a64(param_2);
  if ((*(int *)(param_1 + 0x38) != 0) && (-1 < (int)((uint)*(byte *)(param_1 + 0x4c) << 0x1b))) {
    FUN_00046bec();
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  iVar1 = FUN_0004a318(iVar1 + 1);
  *(int *)(param_1 + 0x38) = iVar1;
  if (iVar1 != 0) {
    FUN_00050a2c(iVar1,param_2);
    *(byte *)(param_1 + 0x4c) = *(byte *)(param_1 + 0x4c) & 0xef;
    FUN_0004d3d8(param_1);
    if (*(int *)(param_1 + 0x2c) != 0) {
      FUN_0004d3d8();
      return;
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

