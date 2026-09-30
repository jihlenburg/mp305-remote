/* Address: ram:0004ac56; name: FUN_ram_0004ac56; body bytes: 426 */

/* WARNING: Removing unreachable block (ram,0x0004ad92) */

undefined4 FUN_ram_0004ac56(undefined4 param_1,ushort *param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  ushort uVar7;
  ushort uStack_3a;
  ushort uStack_38;
  char cStack_36;
  char *pcStack_34;
  
  gp = 0x20004000;
  uVar7 = *param_2;
  if (param_2[1] < uVar7) {
    uVar5 = 1;
  }
  else {
    uVar5 = 1;
    if (uVar7 != 0) {
      uStack_38 = 0;
      pcStack_34 = (char *)0x0;
      pcVar2 = (char *)0x0;
      uVar6 = 0;
      while( true ) {
        uStack_3a = 0;
        pcVar3 = (char *)FUN_ram_0004aaf8(uVar7,param_2[1],0,0,0);
        if (pcVar3 == (char *)0x0) break;
        if ((pcVar2 == (char *)0x0) &&
           (pcVar2 = (char *)GATT_bm_alloc(param_1,5,0xffff,&uStack_3a,0x22), pcVar2 == (char *)0x0)
           ) {
          gp = 0x20004000;
          return 0x11;
        }
        cVar1 = *pcVar3;
        if (uStack_38 == 0) {
          pcStack_34 = pcVar2;
          if (cVar1 == '\x02') {
            cStack_36 = '\x01';
            *pcVar2 = pcVar3[10];
            uVar6 = uStack_3a >> 2 & 0xff;
            pcVar2[1] = (char)((ushort)*(undefined2 *)(pcVar3 + 10) >> 8);
            uVar5 = *(undefined4 *)(pcVar3 + 4);
            goto LAB_ram_0004ad74;
          }
          cStack_36 = '\x02';
          *pcVar2 = pcVar3[10];
          pcVar2[1] = (char)((ushort)*(undefined2 *)(pcVar3 + 10) >> 8);
          uVar5 = *(undefined4 *)(pcVar3 + 4);
          uVar6 = uStack_3a / 0x12 & 0xff;
LAB_ram_0004ad28:
          tmos_memcpy(pcVar2 + 2,uVar5,0x10);
          pcVar2 = pcVar2 + 0x12;
        }
        else {
          if (cStack_36 != '\x01') {
            if (cVar1 == '\x10') {
              *pcVar2 = (char)*(undefined2 *)(pcVar3 + 10);
              pcVar2[1] = (char)((ushort)*(undefined2 *)(pcVar3 + 10) >> 8);
              uVar5 = *(undefined4 *)(pcVar3 + 4);
              goto LAB_ram_0004ad28;
            }
            goto LAB_ram_0004ace8;
          }
          if (cVar1 != '\x02') goto LAB_ram_0004ace8;
          *pcVar2 = (char)*(undefined2 *)(pcVar3 + 10);
          pcVar2[1] = (char)((ushort)*(undefined2 *)(pcVar3 + 10) >> 8);
          uVar5 = *(undefined4 *)(pcVar3 + 4);
LAB_ram_0004ad74:
          tmos_memcpy(pcVar2 + 2,uVar5,2);
          pcVar2 = pcVar2 + 4;
        }
        uStack_38 = uStack_38 + 1;
        if ((uVar6 <= uStack_38) || (*(short *)(pcVar3 + 10) == -1)) break;
        uVar7 = uVar7 + 1;
      }
      if (uStack_38 == 0) {
        uVar5 = 10;
      }
      else {
LAB_ram_0004ace8:
        iVar4 = FUN_ram_00043a74(param_1,&uStack_38);
        if ((iVar4 != 0) && (iVar4 = FUN_ram_00048a38(param_1,0x16,5,&uStack_38), iVar4 != 0)) {
          FUN_ram_20000104(pcStack_34);
        }
        uVar5 = 0;
      }
    }
  }
  return uVar5;
}

