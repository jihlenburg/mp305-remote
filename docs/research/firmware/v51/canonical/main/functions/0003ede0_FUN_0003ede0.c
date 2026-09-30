/* Address: 0003ede0; name: FUN_0003ede0; body bytes: 72 */

void FUN_0003ede0(int param_1,uint param_2,int param_3)

{
  if (param_2 < *(uint *)(param_1 + 0x38)) {
    if (((*(byte *)(param_1 + 0x44) & 1) != 0) && (param_3 << 0x17 < 0)) {
      FUN_0003e84e(param_1,0x100);
    }
    *(ushort *)(*(int *)(param_1 + 0x34) + param_2 * 2) =
         *(ushort *)(*(int *)(param_1 + 0x34) + param_2 * 2) | (ushort)param_3;
    FUN_0003aa70(param_1,param_2);
    if (param_3 << 0x15 < 0) {
      FUN_0004de6c(param_1);
      return;
    }
  }
  return;
}

