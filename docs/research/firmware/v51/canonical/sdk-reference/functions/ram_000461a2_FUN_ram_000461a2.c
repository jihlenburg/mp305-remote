/* Address: ram:000461a2; name: FUN_ram_000461a2; body bytes: 310 */

void FUN_ram_000461a2(int param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  
  gp = 0x20004000;
  if (DAT_ram_20001a04 == (undefined1 *)0x0) {
    gp = 0x20004000;
    return;
  }
  uVar1 = 0;
  if ((param_1 == 0) && (DAT_ram_20001a08 != 0)) {
    uVar1 = 0;
    for (uVar4 = 0; (uVar4 & 0xff) < (uint)DAT_ram_20001a02; uVar4 = uVar4 + 1) {
      if (*(char *)(uVar4 * 0x10 + DAT_ram_20001a08) != -1) {
        uVar1 = uVar1 + 1 & 0xff;
      }
    }
  }
  puVar2 = (undefined1 *)tmos_msg_allocate(uVar1 * 8 + 8);
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = (undefined1 *)tmos_msg_allocate(8);
    if (puVar2 == (undefined1 *)0x0) goto LAB_ram_0004624e;
    uVar1 = 0;
    param_1 = 0x13;
  }
  *puVar2 = 0xd0;
  puVar2[1] = (char)param_1;
  puVar2[2] = 1;
  puVar2[3] = (char)uVar1;
  if (uVar1 == 0) {
    *(undefined4 *)(puVar2 + 4) = 0;
  }
  else {
    pcVar5 = puVar2 + 8;
    *(char **)(puVar2 + 4) = pcVar5;
    uVar4 = 0;
    while ((uVar4 < DAT_ram_20001a02 && (uVar1 != 0))) {
      pcVar3 = (char *)(uVar4 * 0x10 + DAT_ram_20001a08);
      if (*pcVar3 != -1) {
        *pcVar5 = *pcVar3;
        pcVar5[1] = pcVar3[1];
        uVar1 = uVar1 - 1 & 0xff;
        tmos_memcpy(pcVar5 + 2,pcVar3 + 2,6);
        pcVar5 = pcVar5 + 8;
      }
      uVar4 = uVar4 + 1 & 0xff;
    }
  }
  tmos_msg_send(*DAT_ram_20001a04,puVar2);
LAB_ram_0004624e:
  FUN_ram_000460f6(DAT_ram_20001a02,0);
  FUN_ram_20000104(DAT_ram_20001a04);
  DAT_ram_20001a04 = (undefined1 *)0x0;
  return;
}

