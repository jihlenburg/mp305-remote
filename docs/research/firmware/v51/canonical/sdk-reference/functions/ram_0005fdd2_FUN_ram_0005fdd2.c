/* Address: ram:0005fdd2; name: FUN_ram_0005fdd2; body bytes: 208 */

undefined4 FUN_ram_0005fdd2(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  byte *pbVar3;
  byte bVar4;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_20001120(*(undefined4 *)(param_1 + 0x78),0,param_1 + 0x15,0);
  if (iVar2 != 0) {
    gp = 0x20004000;
    return 1;
  }
  pbVar3 = *(byte **)(param_1 + 0x78);
  bVar4 = pbVar3[1];
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(byte *)(param_1 + 0xe) = bVar4 & 0x3f;
  if (0x1f < (byte)((bVar4 & 0x3f) - 6)) {
    gp = 0x20004000;
    return 3;
  }
  bVar4 = *pbVar3;
  *(byte *)(param_1 + 0xd) = bVar4 & 0xf;
  if ((bVar4 & 0xf) != 4) {
    gp = 0x20004000;
    return 7;
  }
  if (*(char *)(param_1 + 0x54) == '\x03') {
    if ((*pbVar3 & 0x40) == 0) {
      gp = 0x20004000;
      return 0x11;
    }
    iVar2 = *(int *)(param_1 + 100) + 0x14;
  }
  else {
    if ((uint)*(byte *)(param_1 + 0x55) != ((int)(uint)*pbVar3 >> 6 & 1U)) {
      gp = 0x20004000;
      return 0x11;
    }
    iVar2 = param_1 + 0x56;
  }
  iVar2 = tmos_memcmp(iVar2,pbVar3 + 2,6);
  if (iVar2 == 0) {
    return 0x11;
  }
  if (*(char *)(param_1 + 0x14) < '\x01') {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  else {
    bVar4 = *(byte *)(param_1 + 0x13) >> 1;
    if (bVar4 == 0) {
      bVar4 = 1;
    }
    *(byte *)(param_1 + 0x13) = bVar4;
  }
  uVar1 = FUN_ram_000428ec(1,*(undefined1 *)(param_1 + 0x13));
  *(undefined1 *)(param_1 + 0x11) = uVar1;
  FUN_ram_0005dd6c(param_1);
  gp = 0x20004000;
  return 0;
}

