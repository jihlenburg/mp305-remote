/* Address: 00049974; name: FUN_00049974; body bytes: 106 */

void FUN_00049974(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  FUN_0004d3d8();
  if (param_2 == 0) {
    param_2 = *(int *)(param_1 + 0x2c);
  }
  iVar1 = FUN_00050a64(param_2);
  iVar2 = *(int *)(param_1 + 0x2c);
  if ((iVar2 == param_2) && (-1 < (int)((uint)*(byte *)(param_1 + 0x5c) << 0x1c))) {
    iVar1 = FUN_0004f588(iVar2,iVar1 + 1);
    *(int *)(param_1 + 0x2c) = iVar1;
    if (iVar1 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  else {
    if ((iVar2 != 0) && (-1 < (int)((uint)*(byte *)(param_1 + 0x5c) << 0x1c))) {
      FUN_00046bec();
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    iVar1 = FUN_0004a318(iVar1 + 1);
    *(int *)(param_1 + 0x2c) = iVar1;
    if (iVar1 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_00050a2c(iVar1,param_2);
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xf7;
  }
  FUN_000493d0(param_1);
  return;
}

