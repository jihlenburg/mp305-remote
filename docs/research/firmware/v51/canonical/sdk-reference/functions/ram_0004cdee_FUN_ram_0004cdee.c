/* Address: ram:0004cdee; name: FUN_ram_0004cdee; body bytes: 354 */

int FUN_ram_0004cdee(undefined4 param_1,char *param_2,undefined4 param_3)

{
  short sVar1;
  int iVar2;
  char cVar3;
  short *psVar4;
  undefined4 local_40;
  short sStack_3c;
  short sStack_38;
  short sStack_36;
  
  gp = 0x20004000;
  cVar3 = *param_2;
  if (cVar3 == '\x06') {
    iVar2 = FUN_ram_0004cb1e(&sStack_38,param_3,param_2[2]);
    if (iVar2 != 0) {
      gp = 0x20004000;
      return iVar2;
    }
    iVar2 = FUN_ram_0004c344(sStack_38);
    cVar3 = param_2[1];
    if (iVar2 != 0) {
      FUN_ram_0004da64(param_1,7,cVar3,&sStack_38,&LAB_ram_0004dcfc);
      FUN_ram_0004d36e(iVar2,0,2);
      FUN_ram_0004c420(iVar2);
      gp = 0x20004000;
      return 0;
    }
    local_40 = CONCAT22(sStack_38,2);
    sStack_3c = sStack_36;
  }
  else {
    if (cVar3 == '\x12') {
      iVar2 = FUN_ram_0004cb7a(&sStack_38,param_3,*(undefined2 *)(param_2 + 2));
      if (iVar2 != 0) {
        gp = 0x20004000;
        return iVar2;
      }
      if (DAT_ram_20001cd8 == 0) {
        gp = 0x20004000;
        return 0;
      }
      FUN_ram_0004d1f6(DAT_ram_20001cda,param_1,0,*param_2,param_2[1],&sStack_38);
      gp = 0x20004000;
      return 0;
    }
    if (cVar3 == '\x14') {
      iVar2 = FUN_ram_0004c782(&sStack_38,param_3,*(undefined2 *)(param_2 + 2));
      if (iVar2 != 0) {
        gp = 0x20004000;
        return iVar2;
      }
      FUN_ram_0004cbe6(param_1,param_2[1],&sStack_38);
      gp = 0x20004000;
      return 0;
    }
    if (cVar3 != '\x16') {
      local_40 = local_40 & 0xffff0000;
      FUN_ram_0004ddcc(param_1,param_2[1],&local_40);
      gp = 0x20004000;
      return 0;
    }
    iVar2 = FUN_ram_0004c7e0(&sStack_38,param_3,*(undefined2 *)(param_2 + 2));
    if (iVar2 != 0) {
      gp = 0x20004000;
      return iVar2;
    }
    iVar2 = FUN_ram_0004c3de(param_1,sStack_38);
    if (iVar2 != 0) {
      psVar4 = *(short **)(iVar2 + 0xc);
      sVar1 = *psVar4;
      *psVar4 = sVar1 + sStack_36;
      if ((short)(sVar1 + sStack_36) == 0) {
        gp = 0x20004000;
        return 0;
      }
      if (*(int *)(psVar4 + 6) == 0) {
        gp = 0x20004000;
        return 0;
      }
      if (DAT_ram_20001a62 == '\0') {
        gp = 0x20004000;
        return 0;
      }
      tmos_set_event(DAT_ram_20001cc8,1);
      gp = 0x20004000;
      return 0;
    }
    local_40 = 2;
    sStack_3c = sStack_38;
    cVar3 = param_2[1];
  }
  FUN_ram_0004ddcc(param_1,cVar3,&local_40);
  return 0;
}

