/* Address: ram:00060500; name: FUN_ram_00060500; body bytes: 340 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_ram_00060500(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  
  gp = 0x20004000;
  iVar5 = FUN_ram_00057c90();
  if (iVar5 != 0) {
    iVar6 = FUN_ram_00057ba2();
    if (iVar6 == 0) {
      iVar5 = 1;
    }
    else {
      *(undefined2 *)(iVar6 + 10) = 0x111;
      *(undefined1 *)(iVar6 + 0xe) = 0xb0;
      *(undefined1 *)(iVar6 + 0x10) = 1;
      puVar8 = (undefined *)(DAT_ram_20001bcc + 9);
      if (&stvec < (undefined *)(DAT_ram_20001bcc + 9)) {
        puVar8 = &stvec;
      }
      if (puVar8 < 0x40) {
        puVar8 = (undefined *)0x40;
      }
      iVar7 = FUN_ram_20000040(puVar8,0x207);
      *(int *)(iVar6 + 0x110) = iVar7;
      if (iVar7 == 0) {
        FUN_ram_00057d86(*(undefined2 *)(iVar6 + 8));
      }
      else {
        *(undefined4 *)(iVar6 + 0x114) = DAT_ram_20001eac;
        uVar3 = DAT_ram_20001e2c;
        uVar2 = DAT_ram_20001e28;
        *(undefined4 *)(iVar6 + 0xfc) = DAT_ram_20001e2c;
        *(undefined4 *)(iVar6 + 0x10c) = uVar3;
        uVar1 = _DAT_ram_20001d9a;
        *(undefined4 *)(iVar6 + 0xf8) = uVar2;
        *(undefined4 *)(iVar6 + 0x108) = uVar2;
        *(undefined2 *)(iVar6 + 0x144) = uVar1;
        uVar4 = DAT_ram_20001daa;
        *(undefined2 *)(iVar6 + 0x146) = 0;
        *(undefined1 *)(iVar6 + 0x14f) = uVar4;
        *(undefined2 *)(iVar6 + 0x3e) = 0xffff;
        *(undefined2 *)(iVar6 + 0x26) = 0xffff;
        *(undefined1 *)(iVar6 + 0x28) = 0xff;
        *(byte *)(iVar6 + 0x2d) = *(byte *)(iVar6 + 0x2d) | 0xc0;
        *(undefined2 *)(iVar6 + 0x48) = 3000;
        FUN_ram_00055dd2(iVar6);
        *(undefined1 *)(iVar6 + 0x142) = DAT_ram_20001bd0;
        uVar4 = FUN_ram_00061d68();
        *(undefined1 *)(iVar6 + 0x16d) = 0x14;
        *(undefined1 *)(iVar6 + 0x16b) = 0x28;
        *(undefined2 *)(iVar6 + 0x15e) = 0x6f0;
        *(undefined1 *)(iVar6 + 0x160) = 0x7f;
        *(undefined1 *)(iVar6 + 0x143) = uVar4;
        *(undefined1 *)(iVar6 + 0x166) = uVar4;
        *(undefined1 *)(iVar6 + 0x167) = uVar4;
        *(undefined1 *)(iVar6 + 0x168) = uVar4;
        *(undefined1 *)(iVar6 + 0x169) = uVar4;
        *(undefined2 *)(iVar6 + 0x162) = 0xceba;
        DAT_ram_20001d68 = 0;
      }
    }
  }
  return iVar5;
}

