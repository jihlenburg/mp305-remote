/* Address: ram:00044504; name: FUN_ram_00044504; body bytes: 286 */

void FUN_ram_00044504(undefined1 param_1,undefined4 param_2,undefined1 param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  char cVar6;
  undefined1 *puVar7;
  
  gp = 0x20004000;
  pcVar2 = (char *)FUN_ram_0004df14(param_2);
  if ((pcVar2 != (char *)0x0) && (iVar1 = *(int *)(pcVar2 + 0x38), iVar1 != 0)) {
    iVar3 = 0x18;
    if (*(int *)(iVar1 + 0x20) != 0) {
      iVar3 = 0x34;
    }
    if (*(int *)(iVar1 + 0x28) != 0) {
      iVar3 = iVar3 + 0x14;
    }
    if (param_4 != 0) {
      iVar3 = iVar3 + 0x1c;
    }
    if (*(int *)(iVar1 + 0x24) != 0) {
      iVar3 = iVar3 + 0x16;
    }
    puVar4 = (undefined1 *)tmos_msg_allocate(iVar3);
    if (puVar4 != (undefined1 *)0x0) {
      tmos_memset(puVar4,0,0x18);
      cVar6 = DAT_ram_20001c54;
      if (DAT_ram_20001c54 == '\0') {
        cVar6 = *pcVar2;
      }
      *puVar4 = 0xd0;
      puVar4[1] = param_1;
      puVar4[2] = 10;
      puVar4[6] = param_3;
      iVar3 = *(int *)(iVar1 + 0x20);
      *(short *)(puVar4 + 4) = (short)param_2;
      puVar5 = puVar4 + 0x18;
      puVar7 = puVar5;
      if (iVar3 != 0) {
        *(undefined1 **)(puVar4 + 8) = puVar5;
        puVar7 = puVar4 + 0x34;
        tmos_memcpy(puVar5,iVar3,0x1c);
      }
      iVar3 = *(int *)(iVar1 + 0x28);
      puVar5 = puVar7;
      if (iVar3 != 0) {
        *(undefined1 **)(puVar4 + 0xc) = puVar7;
        puVar5 = puVar7 + 0x14;
        tmos_memcpy(puVar7,iVar3,0x14);
      }
      puVar7 = puVar5;
      if (param_4 != 0) {
        *(undefined1 **)(puVar4 + 0x10) = puVar5;
        puVar7 = puVar5 + 0x1c;
        tmos_memcpy(puVar5,param_4,0x1c);
      }
      iVar1 = *(int *)(iVar1 + 0x24);
      if (iVar1 != 0) {
        *(undefined1 **)(puVar4 + 0x14) = puVar7;
        tmos_memcpy(puVar7,iVar1,0x16);
      }
      tmos_msg_send(cVar6,puVar4);
      FUN_ram_0004434e(pcVar2);
      return;
    }
  }
  return;
}

