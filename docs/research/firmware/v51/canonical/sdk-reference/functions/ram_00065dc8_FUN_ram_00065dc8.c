/* Address: ram:00065dc8; name: FUN_ram_00065dc8; body bytes: 92 */

undefined4 FUN_ram_00065dc8(int param_1,undefined1 param_2)

{
  char *pcVar1;
  int iVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  if (param_1 << 0x14 < 0) {
    pcVar1 = (char *)FUN_ram_00055958();
    uVar4 = 2;
    if ((pcVar1 != (char *)0x0) && (uVar4 = 0xc, *pcVar1 == '\x04')) {
      *pcVar1 = '\x05';
      uVar4 = 0x12;
    }
  }
  else {
    iVar2 = FUN_ram_00057ba2();
    uVar4 = 0x12;
    if ((iVar2 != 0) && (uVar4 = 0x12, (*(byte *)(iVar2 + 10) & 0x10) != 0)) {
      *(undefined1 *)(iVar2 + 0x52) = param_2;
      if (*(char *)(iVar2 + 0xb) == '\0') {
        uVar3 = 0x1a;
      }
      else {
        uVar3 = 0x1b;
      }
      *(undefined1 *)(iVar2 + 0x10) = uVar3;
      uVar4 = 0;
    }
  }
  return uVar4;
}

