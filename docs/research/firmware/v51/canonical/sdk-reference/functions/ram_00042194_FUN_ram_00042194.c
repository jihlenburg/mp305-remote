/* Address: ram:00042194; name: FUN_ram_00042194; body bytes: 184 */

undefined4 FUN_ram_00042194(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  gp = 0x20004000;
  if ((param_1 < 0x30) && (*(int *)(DAT_ram_20001bf8 + param_1 * 0xc) != 0)) {
    uVar1 = 1 << (param_1 & 0xf) & 0xffff;
    iVar2 = FUN_ram_00041d8e(param_1 >> 4,uVar1);
    if (iVar2 != 0) {
      tmos_clear_event(param_1 >> 4,uVar1);
      iVar3 = (*DAT_ram_20001c00)();
      uVar5 = DAT_ram_20001b8c * param_2;
      uVar1 = uVar5 + 800;
      iVar4 = FUN_ram_0006bae2(uVar1,(uint)(uVar1 < uVar5) +
                                     (int)((ulonglong)(uint)DAT_ram_20001b8c * (ulonglong)param_2 >>
                                          0x20),0x640,0);
      uVar1 = iVar4 + iVar3;
      if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar1)) {
        uVar1 = uVar1 + 0x57400000;
      }
      *(uint *)(iVar2 + 8) = uVar1;
    }
    return 0;
  }
  return 2;
}

