/* Address: 0004b3a0; name: FUN_0004b3a0; body bytes: 106 */

void FUN_0004b3a0(int param_1)

{
  int iVar1;
  
  if (-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x13)) {
    FUN_0004d3d8(param_1);
    iVar1 = FUN_0004bc8c(param_1);
    if (iVar1 == 0) {
      iVar1 = FUN_0004bb48(param_1);
      if (iVar1 != 0) {
        if (*(int *)(iVar1 + 0x2c0) != param_1) {
          FUN_000541d4(param_1);
          return;
        }
        FUN_000541d4(param_1);
        *(undefined4 *)(iVar1 + 0x2c0) = 0;
      }
    }
    else {
      FUN_000541d4();
      if (-1 < (int)((uint)*(ushort *)(iVar1 + 0x2a) << 0x13)) {
        FUN_0004e560(iVar1);
        FUN_0004e5a6(iVar1,0x27,0);
        FUN_0004e5a6(iVar1,0x29,0);
        return;
      }
    }
  }
  return;
}

