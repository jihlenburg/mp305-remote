/* Address: ram:00069942; name: FUN_ram_00069942; body bytes: 244 */

uint FUN_ram_00069942(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined1 auStack_30 [24];
  
  gp = 0x20004000;
  if (param_1 == 2) {
    for (uVar2 = 0; uVar1 = (uint)DAT_ram_20001a8d, uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
      iVar3 = tmos_memcmp(uVar2 * 0x10 + DAT_ram_20001a88 + 6,param_2,6);
      if (iVar3 != 0) goto LAB_ram_00069a1a;
    }
  }
  else if (param_1 < 2) {
    uVar1 = FUN_ram_0006908a(param_2);
    if ((uVar1 < DAT_ram_20001a8d) && (param_3 != 0)) {
      tmos_memcpy(param_3,param_2,6);
    }
  }
  else if (param_1 == 3) {
    for (uVar2 = 0; uVar1 = (uint)DAT_ram_20001a8d, uVar2 < uVar1; uVar2 = uVar2 + 1 & 0xff) {
      iVar3 = tmos_snv_read(uVar2 * 6 + 0x23 & 0xff,0x10,auStack_30);
      if (((iVar3 == 0) && (iVar3 = tmos_isbufset(auStack_30,0xff,0x10), iVar3 == 0)) &&
         (iVar3 = GAP_ResolvePrivateAddr(auStack_30,param_2), iVar3 == 0)) {
LAB_ram_00069a1a:
        if (DAT_ram_20001a8d <= uVar2) {
          gp = 0x20004000;
          return uVar2;
        }
        if (param_3 == 0) {
          gp = 0x20004000;
          return uVar2;
        }
        FUN_ram_000692b4(uVar2,param_3);
        gp = 0x20004000;
        return uVar2;
      }
    }
  }
  else {
    uVar1 = (uint)DAT_ram_20001a8d;
  }
  return uVar1;
}

