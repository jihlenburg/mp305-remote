/* Address: ram:0005a804; name: FUN_ram_0005a804; body bytes: 432 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_ram_0005a804(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  uint uVar9;
  
  gp = 0x20004000;
  iVar5 = FUN_ram_00057c90();
  if (iVar5 != 0) {
    iVar6 = FUN_ram_00057ba2();
    if (iVar6 == 0) {
      iVar5 = 1;
    }
    else {
      *(undefined2 *)(iVar6 + 10) = 0x10;
      *(undefined1 *)(iVar6 + 0xe) = 0xb0;
      *(undefined1 *)(iVar6 + 0x10) = 1;
      puVar8 = (undefined *)(DAT_ram_20001bcc + 5);
      if (&stvec < (undefined *)(DAT_ram_20001bcc + 5)) {
        puVar8 = &stvec;
      }
      if (puVar8 < 0x40) {
        puVar8 = (undefined *)0x40;
      }
      iVar7 = FUN_ram_20000040(puVar8,0x203);
      *(int *)(iVar6 + 0x110) = iVar7;
      uVar3 = DAT_ram_20001e2c;
      if (iVar7 == 0) {
        FUN_ram_00057d86(*(undefined2 *)(iVar6 + 8));
      }
      else {
        *(undefined4 *)(iVar6 + 0x114) = DAT_ram_20001eac;
        uVar9 = DAT_ram_20001e28;
        cVar1 = DAT_ram_20001d61;
        *(undefined4 *)(iVar6 + 0xfc) = uVar3;
        *(uint *)(iVar6 + 0xf8) = uVar9;
        if (cVar1 == '\0') {
          *(uint *)(iVar6 + 0xf8) = uVar9 & 0xffffff3f;
        }
        *(undefined2 *)(iVar6 + 0x146) = 0;
        *(undefined4 *)(iVar6 + 0x10c) = *(undefined4 *)(iVar6 + 0xfc);
        uVar2 = _DAT_ram_20001d9a;
        *(undefined4 *)(iVar6 + 0x108) = *(undefined4 *)(iVar6 + 0xf8);
        *(undefined2 *)(iVar6 + 0x144) = uVar2;
        uVar4 = DAT_ram_20001daa;
        *(byte *)(iVar6 + 0x2d) = *(byte *)(iVar6 + 0x2d) | 0xc1;
        *(undefined1 *)(iVar6 + 0x14f) = uVar4;
        iVar7 = DAT_ram_20001e20;
        uVar9 = *(uint *)(iVar6 + 0xa4);
        *(uint *)(iVar6 + 0xa4) = uVar9 | 0x40;
        if (iVar7 << 6 < 0) {
          *(uint *)(iVar6 + 0xa4) = uVar9 | 0x50;
        }
        if (DAT_ram_20001dac != '\0') {
          *(uint *)(iVar6 + 0xa4) = *(uint *)(iVar6 + 0xa4) | 0x400000;
        }
        *(undefined2 *)(iVar6 + 0x3e) = 0xffff;
        *(undefined2 *)(iVar6 + 0x26) = 0xffff;
        *(undefined1 *)(iVar6 + 0x28) = 0xff;
        *(undefined2 *)(iVar6 + 0x48) = 3000;
        FUN_ram_00055dd2(iVar6);
        *(undefined1 *)(iVar6 + 0x142) = DAT_ram_20001bd0;
        uVar4 = FUN_ram_00061d68();
        *(undefined1 *)(iVar6 + 0x16d) = 0x14;
        *(undefined1 *)(iVar6 + 0x16b) = 0x28;
        *(undefined2 *)(iVar6 + 0x15e) = 0x6f0;
        *(undefined1 *)(iVar6 + 0x160) = 0x7f;
        *(undefined2 *)(iVar6 + 0x162) = 0xceba;
        *(undefined1 *)(iVar6 + 0x143) = uVar4;
        *(undefined1 *)(iVar6 + 0x166) = uVar4;
        *(undefined1 *)(iVar6 + 0x167) = uVar4;
        *(undefined1 *)(iVar6 + 0x168) = uVar4;
        *(undefined1 *)(iVar6 + 0x169) = uVar4;
        if ((*(uint *)(iVar6 + 0xfc) & 0x80) != 0) {
          *(undefined1 *)(iVar6 + 0x174) = 1;
        }
        DAT_ram_20001d68 = 0;
      }
    }
  }
  return iVar5;
}

