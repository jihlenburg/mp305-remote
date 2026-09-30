/* Address: ram:0004cf50; name: FUN_ram_0004cf50; body bytes: 336 */

int FUN_ram_0004cf50(undefined4 param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  undefined2 uVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined1 uVar7;
  short sStack_38;
  ushort uStack_36;
  ushort uStack_34;
  undefined2 uStack_32;
  short sStack_30;
  
  gp = 0x20004000;
  pcVar4 = (char *)FUN_ram_0004c376(param_2[1]);
  if (pcVar4 == (char *)0x0) {
    gp = 0x20004000;
    return 0;
  }
  pcVar4[4] = '\0';
  pcVar4[2] = '\0';
  pcVar4[3] = '\0';
  cVar1 = *param_2;
  if (cVar1 == '\x01') {
    iVar5 = FUN_ram_0004cac0(&sStack_38,param_3,param_2[2]);
  }
  else {
    if (cVar1 == '\a') {
      if (*pcVar4 != '\x03') {
        gp = 0x20004000;
        return 0;
      }
      bVar3 = true;
      iVar5 = FUN_ram_0004cb4c(&sStack_38,param_3,param_2[2]);
      if (iVar5 == 0) {
        FUN_ram_0004d36e(pcVar4,0,1);
      }
      goto LAB_ram_0004cfd4;
    }
    if (cVar1 != '\x13') {
      if ((cVar1 != '\x15') || (*pcVar4 != '\x02')) {
        return 0;
      }
      bVar3 = true;
      iVar5 = FUN_ram_0004cce2(&sStack_38,param_3,param_2[2]);
      if (iVar5 == 0) {
        if (sStack_30 == 0) {
          puVar6 = *(undefined2 **)(pcVar4 + 0xc);
          if ((((ushort)(sStack_38 - 0x40U) < 0x40) && (0x16 < uStack_36)) && (0x16 < uStack_34)) {
            puVar6[1] = sStack_38;
            puVar6[2] = uStack_36;
            *puVar6 = uStack_32;
            puVar6[3] = uStack_34;
            *pcVar4 = '\x01';
            uVar7 = 0;
            bVar3 = false;
          }
          else {
            uVar2 = *(undefined2 *)(pcVar4 + 2);
            puVar6[1] = sStack_38;
            FUN_ram_0004ddde(uVar2);
            uVar7 = 2;
            bVar3 = true;
          }
        }
        else {
          uVar7 = 0;
          bVar3 = true;
        }
        FUN_ram_0004d312(pcVar4,uVar7,sStack_30);
      }
      goto LAB_ram_0004cfd4;
    }
    if (*pcVar4 != '\x04') {
      gp = 0x20004000;
      return 0;
    }
    iVar5 = FUN_ram_0004cbc8(&sStack_38,param_3,param_2[2]);
  }
  bVar3 = true;
LAB_ram_0004cfd4:
  FUN_ram_0004c604(pcVar4);
  FUN_ram_0004d1f6(pcVar4[8],param_1,iVar5,cVar1,0,&sStack_38);
  if (bVar3) {
    FUN_ram_0004c420(pcVar4);
    gp = 0x20004000;
    return iVar5;
  }
  gp = 0x20004000;
  return iVar5;
}

