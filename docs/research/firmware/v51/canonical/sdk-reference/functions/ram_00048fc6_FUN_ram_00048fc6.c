/* Address: ram:00048fc6; name: FUN_ram_00048fc6; body bytes: 128 */

int FUN_ram_00048fc6(undefined4 param_1,undefined2 *param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uStack_38;
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [12];
  undefined2 uStack_24;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004957c(param_1,&uStack_38);
  if (iVar1 == 0) {
    iVar1 = ATT_GetMTU(param_1);
    uVar2 = (uint)(ushort)param_2[2];
    if ((int)(iVar1 - 5U) <= (int)uVar2) {
      uVar2 = iVar1 - 5U & 0xffff;
    }
    iVar1 = FUN_ram_00048dc4(param_1,*param_2,param_2[1],uVar2,*(undefined4 *)(param_2 + 4));
    if (iVar1 == 0) {
      auStack_34[0] = 0;
      tmos_memcpy(auStack_30,param_2,0xc);
      uStack_24 = param_2[1];
      FUN_ram_0004972e(uStack_38,auStack_34,0x17,&LAB_ram_00043868,param_3);
    }
  }
  return iVar1;
}

