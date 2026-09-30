/* Address: ram:00042b1c; name: FUN_ram_00042b1c; body bytes: 152 */

undefined4 FUN_ram_00042b1c(void)

{
  ushort uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  
  gp = 0x20004000;
  if ((DAT_ram_20001bc4 != 0) && (DAT_ram_20001bf4 != (code *)0x0)) {
    if (DAT_ram_20001b84 == (int *)0x0) {
      DAT_ram_20001b84 = (int *)FUN_ram_20000040(DAT_ram_20001bc8,0x4e);
    }
    if (DAT_ram_20001b84 != (int *)0x0) {
      tmos_memset(DAT_ram_20001b84,0xff,DAT_ram_20001bc8);
      for (iVar4 = 0; pcVar2 = DAT_ram_20001bf4, iVar4 < (int)(uint)DAT_ram_20001bca;
          iVar4 = iVar4 + 1) {
        uVar1 = DAT_ram_20001bc8 >> 2;
        iVar3 = (uint)DAT_ram_20001bc8 * iVar4 + DAT_ram_20001bc4;
        *DAT_ram_20001b84 = iVar3;
        (*pcVar2)(iVar3,uVar1);
      }
    }
  }
  if (DAT_ram_20001b84 != (int *)0x0) {
    FUN_ram_20000104();
    DAT_ram_20001b84 = (int *)0x0;
    DAT_ram_20001b88 = 0;
  }
  return 0;
}

