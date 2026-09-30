/* Address: ram:00056878; name: FUN_ram_00056878; body bytes: 240 */

/* WARNING: Removing unreachable block (ram,0x000568d0) */

void FUN_ram_00056878(int param_1)

{
  code *pcVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  
  gp = 0x20004000;
  if ((DAT_ram_20001e80 == (code *)0x0) || (DAT_ram_20001e04 != 1)) goto LAB_ram_0005692a;
  uVar3 = *(uint *)(param_1 + 0x90);
  uVar2 = ((uint)*(ushort *)(param_1 + 0x84) * (uint)DAT_ram_20001b8c + 999999) / 1000000;
  if ((-1 < DAT_ram_20001bd2) && (uVar3 < uVar2)) {
    uVar3 = uVar3 + 0xa8c00000;
  }
  uVar3 = uVar3 - uVar2;
  uVar2 = (*DAT_ram_20001c00)();
  pcVar1 = DAT_ram_20001e80;
  if (uVar3 < uVar2) {
    uVar5 = 0;
    if ((int)(uVar2 - uVar3) < 0) {
      if (-1 < DAT_ram_20001bd2) {
        uVar3 = uVar3 + 0xa8c00000;
      }
      goto LAB_ram_000568f6;
    }
  }
  else {
LAB_ram_000568f6:
    uVar5 = uVar3 - uVar2;
  }
  uVar4 = 0;
  if (DAT_ram_20001bd5 >> 1 < uVar5) {
    uVar5 = uVar5 - (DAT_ram_20001bd5 >> 1);
    uVar4 = FUN_ram_0006bae2(uVar5 * 1000000,(int)((ulonglong)uVar5 * 1000000 >> 0x20),
                             DAT_ram_20001b8c,0);
  }
  (*pcVar1)(uVar4);
LAB_ram_0005692a:
  *(undefined1 *)(param_1 + 0xe) = 0xb0;
  return;
}

