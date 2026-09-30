/* Address: ram:00053b6e; name: FUN_ram_00053b6e; body bytes: 348 */

undefined4 FUN_ram_00053b6e(int param_1)

{
  byte bVar1;
  char cVar2;
  undefined1 *puVar3;
  int iVar4;
  byte *pbVar5;
  undefined4 uVar6;
  
  gp = 0x20004000;
  pbVar5 = *(byte **)(param_1 + 0x50);
  bVar1 = pbVar5[1];
  *(byte *)(param_1 + 0x12) = bVar1 & 0x3f;
  if ((bVar1 & 0x3f) != 0x22) {
    return 0x80;
  }
  bVar1 = *pbVar5;
  *(byte *)(param_1 + 0x13) = bVar1 & 0xf;
  if ((bVar1 & 0xf) == 5) {
    iVar4 = tmos_memcmp(param_1 + 0x36,pbVar5 + 8,6);
    if (iVar4 == 0) {
      gp = 0x20004000;
      return 4;
    }
    *(byte *)(param_1 + 0x45) = (byte)((int)(uint)**(byte **)(param_1 + 0x50) >> 6) & 1;
    tmos_memcpy(param_1 + 0x46,*(byte **)(param_1 + 0x50) + 2,6);
  }
  iVar4 = FUN_ram_000536fe(param_1);
  uVar6 = 8;
  if (iVar4 != 0) {
    uVar6 = (*DAT_ram_20001c00)();
    puVar3 = *(undefined1 **)(param_1 + 0x4c);
    *(undefined4 *)(param_1 + 0x24) = uVar6;
    *(undefined1 *)(param_1 + 0x10) = 8;
    *puVar3 = 8;
    puVar3[2] = 1;
    puVar3[3] = 1;
    tmos_memcpy(puVar3 + 4,param_1 + 0x36,6);
    puVar3[2] = puVar3[2] + '\x06';
    puVar3[3] = puVar3[3] | 2;
    if (*(char *)(param_1 + 0x45) != '\0') {
      **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x80;
    }
    tmos_memcpy(puVar3 + 10,param_1 + 0x46,6);
    cVar2 = puVar3[2];
    *(byte *)(param_1 + 0x11) = (cVar2 + 6U & 0x3f) + 1;
    puVar3[2] = cVar2 + 6U;
    if (((*(byte *)(param_1 + 0x35) & 1) != 0) || (*(char *)(param_1 + 0x34) == '\x02')) {
      **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x40;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x4c) + 1) = *(undefined1 *)(param_1 + 0x11);
    *(undefined1 *)(param_1 + 0xb) = 0x9a;
    FUN_ram_00061f0a(*(undefined1 *)(param_1 + 99));
    FUN_ram_200011be(3,*(undefined1 *)(param_1 + 99),*(undefined1 *)(param_1 + 0x11));
    FUN_ram_00062262();
    uVar6 = 0;
  }
  return uVar6;
}

