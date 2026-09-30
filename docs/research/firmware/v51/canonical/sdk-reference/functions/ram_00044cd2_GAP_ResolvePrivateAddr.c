/* Address: ram:00044cd2; name: GAP_ResolvePrivateAddr; body bytes: 4 */

uint GAP_ResolvePrivateAddr(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 auStack_18 [2];
  byte bStack_16;
  undefined1 auStack_14 [8];
  
  gp = 0x20004000;
  if (param_1 != 0) {
    uVar1 = 2;
    if (param_2 != 0) {
      tmos_memcpy(auStack_18,param_2 + 3,3);
      bStack_16 = bStack_16 & 0x3f | 0x40;
      uVar1 = FUN_ram_0005132e(param_1,auStack_18,auStack_14);
      if (uVar1 == 0) {
        iVar2 = tmos_memcmp(auStack_14,param_2,3);
        uVar1 = (uint)(iVar2 != 1);
      }
    }
    return uVar1;
  }
  return 2;
}

