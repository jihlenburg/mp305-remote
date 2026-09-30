/* Address: ram:00055078; name: FUN_ram_00055078; body bytes: 268 */

undefined4 FUN_ram_00055078(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  
  gp = 0x20004000;
  pbVar5 = *(byte **)(param_1 + 0x50);
  bVar1 = pbVar5[1];
  *(byte *)(param_1 + 0x12) = bVar1 & 0x3f;
  if (((byte)((bVar1 & 0x3f) - 6) < 0x20) &&
     (bVar1 = *pbVar5, *(byte *)(param_1 + 0x13) = bVar1 & 0xf, ((bVar1 & 0xf) - 3 & 0xfd) == 0)) {
    iVar2 = tmos_memcmp(param_1 + 0x36,pbVar5 + 8,6);
    if (iVar2 == 0) {
      gp = 0x20004000;
      return 4;
    }
    *(undefined1 *)(param_1 + 0x44) = 1;
    *(byte *)(param_1 + 0x45) = (byte)((int)(uint)**(byte **)(param_1 + 0x50) >> 6) & 1;
    tmos_memcpy(param_1 + 0x46,*(byte **)(param_1 + 0x50) + 2,6);
    iVar2 = FUN_ram_000536fe(param_1);
    if (iVar2 == 1) {
      if ((*(char *)(param_1 + 0x13) == '\x05') &&
         (uVar3 = FUN_ram_00055ed6(), uVar3 < (DAT_ram_20001bd3 & 3))) {
        if (*(byte *)(param_1 + 0x10) < 2) {
          uVar4 = (*DAT_ram_20001c00)();
          *(undefined4 *)(param_1 + 0x24) = uVar4;
          iVar2 = FUN_ram_00053524(param_1);
          if (iVar2 != 1) {
            gp = 0x20004000;
            return 0;
          }
          FUN_ram_0005501c(param_1);
          gp = 0x20004000;
          return 0;
        }
      }
      else if ((*(char *)(param_1 + 0x10) == '\0') || (*(char *)(param_1 + 0x10) == '\x06')) {
        FUN_ram_000534a8(param_1);
        FUN_ram_00061f0a(*(undefined1 *)(param_1 + 100),*(undefined1 *)(param_1 + 0x11));
        FUN_ram_200011be(3,*(undefined1 *)(param_1 + 100),*(undefined1 *)(param_1 + 0x11));
        FUN_ram_00062262();
        gp = 0x20004000;
        return 0;
      }
    }
  }
  return 0x80;
}

