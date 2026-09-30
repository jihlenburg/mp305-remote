/* Address: ram:0004332a; name: FUN_ram_0004332a; body bytes: 182 */

int FUN_ram_0004332a(undefined4 param_1,code *param_2,char param_3,undefined4 param_4,char *param_5)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined2 uStack_28;
  undefined2 uStack_26;
  char *pcStack_24;
  
  gp = 0x20004000;
  if (param_5 == (char *)0x0) {
    uVar3 = ATT_GetMTU();
    param_5 = (char *)FUN_ram_0004c868(uVar3,4);
    if (param_5 == (char *)0x0) {
      gp = 0x20004000;
      return 0x13;
    }
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  *param_5 = param_3;
  uVar2 = 1;
  if (param_2 != (code *)0x0) {
    iVar4 = (*param_2)(param_5 + 1,param_4);
    uVar2 = iVar4 + 1U & 0xffff;
  }
  if (param_3 < '\0') {
    iVar4 = linkDB_State(param_1,0x10);
    iVar5 = 0x19;
    if ((iVar4 != 0) || (iVar5 = FUN_ram_0004ef4c(param_5,uVar2,param_5 + uVar2), iVar5 != 0))
    goto LAB_ram_000433b6;
    uVar2 = uVar2 + 0xc & 0xffff;
  }
  uStack_28 = 4;
  uStack_26 = (undefined2)uVar2;
  pcStack_24 = param_5;
  iVar5 = FUN_ram_0004d9da(param_1,&uStack_28);
  if (iVar5 == 0) {
    gp = 0x20004000;
    return 0;
  }
LAB_ram_000433b6:
  if (bVar1) {
    FUN_ram_20000104(param_5);
  }
  return iVar5;
}

