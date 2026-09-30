/* Address: ram:00042a74; name: FUN_ram_00042a74; body bytes: 168 */

undefined4 FUN_ram_00042a74(void)

{
  ushort uVar1;
  int *piVar2;
  code *pcVar3;
  int iVar4;
  undefined4 extraout_a3;
  undefined4 uVar5;
  undefined4 extraout_a3_00;
  int iVar6;
  int iStack_14;
  
  gp = 0x20004000;
  if ((((DAT_ram_20001bc4 != 0) && (DAT_ram_20001bf0 != (code *)0x0)) &&
      (DAT_ram_20001bf4 != (code *)0x0)) &&
     (((*DAT_ram_20001bf0)(DAT_ram_20001bc4,1,&iStack_14), DAT_ram_20001bc4 != iStack_14 &&
      (DAT_ram_20001b84 = (int *)FUN_ram_20000040(DAT_ram_20001bc8,0x4e),
      DAT_ram_20001b84 != (int *)0x0)))) {
    tmos_memset(DAT_ram_20001b84,0xff,DAT_ram_20001bc8);
    uVar5 = extraout_a3;
    for (iVar6 = 0; pcVar3 = DAT_ram_20001bf4, piVar2 = DAT_ram_20001b84,
        iVar6 < (int)(uint)DAT_ram_20001bca; iVar6 = iVar6 + 1) {
      uVar1 = DAT_ram_20001bc8 >> 2;
      iVar4 = DAT_ram_20001bc4 + (uint)DAT_ram_20001bc8 * iVar6;
      *DAT_ram_20001b84 = iVar4;
      (*pcVar3)(iVar4,uVar1,piVar2,uVar5,pcVar3);
      uVar5 = extraout_a3_00;
    }
    FUN_ram_20000104(DAT_ram_20001b84);
    gp = 0x20004000;
    DAT_ram_20001b84 = (int *)0x0;
    DAT_ram_20001b88 = 0;
    return 0;
  }
  return 1;
}

