/* Address: 00012bec; name: FUN_00012bec; body bytes: 50 */

undefined4 FUN_00012bec(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0001536c(0,0x200);
  if (iVar1 == 0) {
    DAT_1fffa988 = DAT_1fffa988 + param_1;
    if (DAT_1fffa988 < 1000) {
      return 0;
    }
    DAT_1fffaa50 = 1;
  }
  else {
    DAT_1fffa988 = 0;
  }
  return 1;
}

