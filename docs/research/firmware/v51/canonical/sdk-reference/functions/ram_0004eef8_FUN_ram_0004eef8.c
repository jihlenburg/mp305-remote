/* Address: ram:0004eef8; name: FUN_ram_0004eef8; body bytes: 84 */

int FUN_ram_0004eef8(int param_1,int param_2)

{
  int iVar1;
  undefined1 auStack_14 [2];
  byte bStack_12;
  
  gp = 0x20004000;
  iVar1 = 2;
  if ((param_1 != 0) && (param_2 != 0)) {
    FUN_ram_000440ba(auStack_14,3);
    bStack_12 = bStack_12 & 0x3f | 0x40;
    iVar1 = FUN_ram_0005132e(param_1,auStack_14,param_2);
    if (iVar1 == 0) {
      tmos_memcpy(param_2 + 3,auStack_14,3);
    }
  }
  return iVar1;
}

