/* Address: 00040c08; name: FUN_00040c08; body bytes: 46 */

int FUN_00040c08(int param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = 0;
  if (param_1 != 0) {
    uVar2 = FUN_0004089c(0);
    if ((int)((ulonglong)uVar2 >> 0x20) * (int)uVar2 + 0x50 < 0x140) {
      return 1;
    }
    uVar2 = FUN_0004089c(0);
    iVar1 = ((int)((ulonglong)uVar2 >> 0x20) * (int)uVar2 + 0x50) / 0xa0;
  }
  return iVar1;
}

