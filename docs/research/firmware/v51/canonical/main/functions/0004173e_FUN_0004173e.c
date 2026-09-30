/* Address: 0004173e; name: FUN_0004173e; body bytes: 74 */

ushort * FUN_0004173e(ushort *param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5
                     )

{
  uint uVar1;
  
  if (param_1 != (ushort *)0x0) {
    if (param_2 == 0) {
      param_2 = (uint)(*param_1 >> 8);
    }
    if (param_5 == 0) {
      param_5 = FUN_00041788(param_3,param_2);
    }
    uVar1 = FUN_00020316(param_3,param_4,param_2,param_5);
    if (uVar1 <= *(uint *)(param_1 + 6)) {
      *(char *)((int)param_1 + 1) = (char)param_2;
      param_1[2] = (ushort)param_3;
      param_1[3] = (ushort)param_4;
      param_1[4] = (ushort)param_5;
      return param_1;
    }
  }
  return (ushort *)0x0;
}

