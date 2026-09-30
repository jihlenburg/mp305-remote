/* Address: ram:0005c760; name: FUN_ram_0005c760; body bytes: 236 */

undefined4 FUN_ram_0005c760(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined2 uVar4;
  
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x16) != '\x18') {
    gp = 0x20004000;
    return 1;
  }
  if ((*(uint *)(param_1 + 0x108) & 2) == 0) {
    gp = 0x20004000;
    return 1;
  }
  if (*(char *)(param_1 + 0xb) == '\x01') {
    uVar2 = FUN_ram_0005b4ec();
    *(undefined1 *)(param_1 + 0x2a) = uVar2;
    if (*(char *)(param_1 + 0x10) != '\x01') {
      if (*(char *)(param_1 + 0x10) == '@') {
        *(undefined1 *)(param_1 + 0x10) = 0x41;
        *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
        gp = 0x20004000;
        return 0;
      }
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 2;
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x80;
      gp = 0x20004000;
      return 0;
    }
LAB_ram_0005c798:
    *(undefined1 *)(param_1 + 0x10) = 0x41;
  }
  else {
    if ((*(byte *)(param_1 + 0x11) & 3) == 0) {
      cVar1 = *(char *)(param_1 + 0x10);
      if (cVar1 == '\x01') {
        uVar2 = FUN_ram_0005b4ec();
        *(undefined1 *)(param_1 + 0x2a) = uVar2;
        goto LAB_ram_0005c798;
      }
      if (cVar1 == ' ') {
        iVar3 = FUN_ram_0005b4ec();
        *(char *)(param_1 + 0x2a) = (char)iVar3;
        if (iVar3 == 0) {
          *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x80000000;
          gp = 0x20004000;
          return 0;
        }
        gp = 0x20004000;
        return 0;
      }
      if (cVar1 != '@') {
        gp = 0x20004000;
        return 1;
      }
      uVar4 = 0xf23;
    }
    else {
      uVar4 = 0xf2a;
    }
    *(undefined2 *)(param_1 + 0x2a) = uVar4;
    *(uint *)(param_1 + 0xa8) = *(uint *)(param_1 + 0xa8) | 2;
  }
  return 0;
}

