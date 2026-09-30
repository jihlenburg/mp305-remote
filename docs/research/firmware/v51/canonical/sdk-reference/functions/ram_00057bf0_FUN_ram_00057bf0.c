/* Address: ram:00057bf0; name: FUN_ram_00057bf0; body bytes: 160 */

void FUN_ram_00057bf0(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  
  gp = 0x20004000;
  if ((DAT_ram_20001e00 == (int *)0x0) &&
     (piVar1 = (int *)FUN_ram_20000040(((int)(DAT_ram_20001d8e + 0x21) >> 5) * 0x20 +
                                       (DAT_ram_20001bcb + 1) * 0x10 & 0xffff,0x20b),
     piVar1 != (int *)0x0)) {
    uVar4 = (uint)DAT_ram_20001bcb;
    piVar2 = piVar1;
    DAT_ram_20001e00 = piVar1;
    for (uVar5 = 0; uVar5 <= uVar4; uVar5 = uVar5 + 1 & 0xffff) {
      if (uVar5 == 0) {
        *(undefined2 *)((int)piVar2 + 10) = 0xff52;
        piVar2[1] = (int)(piVar1 + (uVar4 + 1) * 4);
      }
      else {
        *(undefined2 *)((int)piVar2 + 10) = 0xff54;
        piVar2[1] = 0;
      }
      *(undefined1 *)((int)piVar2 + 9) = 0;
      piVar3 = piVar2 + 4;
      if (uVar4 <= uVar5) {
        piVar3 = (int *)0x0;
      }
      *piVar2 = (int)piVar3;
      piVar2 = piVar2 + 4;
    }
  }
  return;
}

