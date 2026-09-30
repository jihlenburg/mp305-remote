/* Address: 0004743a; name: FUN_0004743a; body bytes: 68 */

void FUN_0004743a(int param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*(byte *)(param_1 + 0x1c) & 3) >> 1 != param_2) {
    *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) & 0xfd | (byte)((param_2 & 1) << 1);
    iVar1 = FUN_000472e0(param_1);
    if (iVar1 != 0) {
      uVar2 = FUN_00037430(param_1);
      iVar3 = FUN_0004e5a6(**(undefined4 **)(param_1 + 0xc),0x10,uVar2);
      if (iVar3 == 1) {
        FUN_0004d3d8(iVar1);
        return;
      }
    }
  }
  return;
}

