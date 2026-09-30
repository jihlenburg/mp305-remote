/* Address: 00058a6c; name: FUN_00058a6c; body bytes: 48 */

void FUN_00058a6c(int *param_1,byte param_2)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    do {
      iVar1 = FUN_0001f01c(&DAT_40021000,0x40);
    } while (iVar1 == 0);
    DAT_40021004 = (ushort)param_2;
    return;
  }
  *(byte *)*param_1 = param_2;
  *param_1 = *param_1 + 1;
  return;
}

