/* Address: 0005e710; name: FUN_0005e710; body bytes: 100 */

undefined4 FUN_0005e710(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_2003a470;
  if ((((param_1 == 1) || (param_1 == 4)) || (param_1 == 7)) ||
     (((param_1 == 8 || (param_1 == 5)) || ((param_1 == 6 || (param_1 == 0xf)))))) {
    FUN_0004883e(DAT_2003a470,param_1,DAT_2003a474);
    iVar1 = FUN_0003a5c8(iVar2);
    if (iVar1 != 0) {
      return 0;
    }
    if ((int)((uint)*(byte *)(iVar2 + 10) << 0x1b) < 0) {
      *(byte *)(iVar2 + 10) = *(byte *)(iVar2 + 10) & 0xef;
      return 1;
    }
  }
  FUN_0004e5a6(DAT_2003a474,param_1,param_2);
  iVar2 = FUN_0003a5c8(iVar2);
  if (iVar2 != 0) {
    return 0;
  }
  return 1;
}

