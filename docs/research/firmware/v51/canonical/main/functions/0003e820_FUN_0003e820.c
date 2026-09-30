/* Address: 0003e820; name: FUN_0003e820; body bytes: 46 */

void FUN_0003e820(int param_1,uint param_2,int param_3)

{
  if (param_2 < *(uint *)(param_1 + 0x38)) {
    *(ushort *)(*(int *)(param_1 + 0x34) + param_2 * 2) =
         *(ushort *)(*(int *)(param_1 + 0x34) + param_2 * 2) & ~(ushort)param_3;
    FUN_0003aa70(param_1);
    if (param_3 << 0x15 < 0) {
      FUN_0004de6c(param_1);
      return;
    }
  }
  return;
}

