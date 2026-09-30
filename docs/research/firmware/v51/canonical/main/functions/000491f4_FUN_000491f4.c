/* Address: 000491f4; name: FUN_000491f4; body bytes: 100 */

void FUN_000491f4(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (-1 < (int)((uint)*(byte *)(param_1 + 0x5c) << 0x1c)) {
    FUN_0004d3d8(param_1);
    iVar1 = FUN_00050a64(*(undefined4 *)(param_1 + 0x2c));
    iVar2 = FUN_00050a64(param_3);
    iVar1 = FUN_0004f588(*(undefined4 *)(param_1 + 0x2c),iVar2 + iVar1 + 1);
    *(int *)(param_1 + 0x2c) = iVar1;
    if (iVar1 != 0) {
      if (param_2 == 0xffff) {
        param_2 = FUN_00051c88();
      }
      FUN_00051a80(*(undefined4 *)(param_1 + 0x2c),param_2,param_3);
      FUN_00049974(param_1,0);
      return;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}

