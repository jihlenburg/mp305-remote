/* Address: ram:00007c92; name: FUN_ram_00007c92; body bytes: 140 */

/* WARNING: Removing unreachable block (ram,0x00007cbc) */

undefined4 FUN_ram_00007c92(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined *puVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  gp = &DAT_ram_20002000;
  if (DAT_ram_20003004 == (undefined *)0x0) {
    DAT_ram_20003004 = &DAT_ram_20006d60;
  }
  puVar1 = DAT_ram_20003004;
  uVar4 = *(uint *)(DAT_ram_20003004 + 4);
  uVar2 = 0xffffffff;
  if ((int)uVar4 < 0x20) {
    if (param_1 != 0) {
      iVar5 = *(int *)(DAT_ram_20003004 + 0x88);
      if (iVar5 == 0) {
        gp = &DAT_ram_20002000;
        return 0xffffffff;
      }
      puVar6 = (undefined4 *)(uVar4 * 4 + iVar5);
      *puVar6 = param_3;
      uVar3 = 1 << (uVar4 & 0x1f);
      *(uint *)(iVar5 + 0x100) = *(uint *)(iVar5 + 0x100) | uVar3;
      puVar6[0x20] = param_4;
      if (param_1 == 2) {
        *(uint *)(iVar5 + 0x104) = uVar3 | *(uint *)(iVar5 + 0x104);
      }
    }
    *(uint *)(puVar1 + 4) = uVar4 + 1;
    *(undefined4 *)(puVar1 + uVar4 * 4 + 8) = param_2;
    uVar2 = 0;
  }
  return uVar2;
}

