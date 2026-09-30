/* Address: ram:00069cb0; name: FUN_ram_00069cb0; body bytes: 350 */

undefined4 FUN_ram_00069cb0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  short *psVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uStack_54;
  undefined2 uStack_50;
  undefined1 auStack_4c [16];
  undefined1 auStack_3c [4];
  short local_38;
  undefined1 auStack_36 [22];
  short asStack_20 [4];
  
  gp = 0x20004000;
  uStack_54 = 0;
  uStack_50 = 0;
  uVar4 = FUN_ram_00069942(param_1,param_2,&uStack_54);
  if (uVar4 < DAT_ram_20001a8d) {
    uVar5 = FUN_ram_00068a5c();
    iVar6 = param_4;
    cVar1 = DAT_ram_200019c7;
    if (param_4 == 4) {
      iVar6 = 4;
      cVar1 = DAT_ram_200019ca;
    }
    FUN_ram_00068ea8(param_3,uVar4,uVar5,iVar6,cVar1 == '\x02');
    tmos_memset(auStack_4c,0,0x14);
    uVar2 = uVar4 * 6 & 0xff;
    iVar6 = tmos_snv_read(uVar2 + 0x24 & 0xfe,0x10,auStack_4c);
    if ((iVar6 == 0) && (iVar6 = tmos_isbufset(auStack_4c,0xff,0x10), iVar6 == 0)) {
      tmos_snv_read(uVar2 + 0x25 & 0xff,4,auStack_3c);
      FUN_ram_00045080(param_3,uVar5 & 1,auStack_4c);
    }
    iVar6 = tmos_snv_read(uVar4 + 0x70 & 0xff,0x18,&local_38);
    if (iVar6 == 0) {
      FUN_ram_00068a38(&local_38);
      psVar3 = &local_38;
      do {
        if (*psVar3 != 0) {
          FUN_ram_0004a878(param_3,*psVar3,(char)psVar3[1]);
        }
        psVar3 = psVar3 + 2;
      } while ((short *)(auStack_36 + 0x16) != psVar3);
    }
    if ((uVar5 & 2) != 0) {
      GATTServApp_SendServiceChangedInd(param_3,DAT_ram_20001a8e);
    }
  }
  else if (param_4 == 8) {
    if (DAT_ram_200019c7 != '\x02') {
      gp = 0x20004000;
      return 0;
    }
    FUN_ram_00068f1c(param_3,param_1,0);
    FUN_ram_00069302(param_3,0,0);
    gp = 0x20004000;
    return 0;
  }
  if ((param_4 == 4) && (DAT_ram_200019ca == '\x02')) {
    GAPBondMgr_PeriSecurityReq(param_3);
  }
  return 0;
}

