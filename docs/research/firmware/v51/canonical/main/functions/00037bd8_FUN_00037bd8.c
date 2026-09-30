/* Address: 00037bd8; name: FUN_00037bd8; body bytes: 124 */

undefined4 FUN_00037bd8(undefined4 *param_1,uint param_2,uint param_3,int *param_4)

{
  byte bVar1;
  int iVar2;
  
  param_2 = param_2 & 0xff0000;
  iVar2 = FUN_000378ca();
  if (iVar2 == 1) {
    return 1;
  }
  if (param_3 < 0x8d) {
    bVar1 = (&DAT_0007a228)[param_3];
  }
  else {
    if (DAT_2003a450 == 0) goto LAB_00037c28;
    bVar1 = *(byte *)(DAT_2003a450 + (param_3 - 0x8d));
  }
  if ((bVar1 & 1) != 0) {
    if (param_2 == 0) goto LAB_00037c10;
    param_2 = 0;
    while( true ) {
      if (param_1 == (undefined4 *)0x0) {
        return 0;
      }
      iVar2 = FUN_000378ca(param_1,*(ushort *)(param_1 + 10) | param_2,param_3,param_4);
      if (iVar2 == 1) break;
LAB_00037c10:
      param_1 = (undefined4 *)param_1[1];
    }
    return 1;
  }
LAB_00037c28:
  if ((param_2 == 0) && ((param_3 == 1 || (param_3 == 2)))) {
    for (param_1 = (undefined4 *)*param_1; param_1 != (undefined4 *)0x0;
        param_1 = (undefined4 *)*param_1) {
      if (param_3 == 1) {
        iVar2 = param_1[6];
      }
      else {
        iVar2 = param_1[7];
      }
      if (iVar2 != 0) {
        *param_4 = iVar2;
        return 1;
      }
    }
  }
  return 0;
}

