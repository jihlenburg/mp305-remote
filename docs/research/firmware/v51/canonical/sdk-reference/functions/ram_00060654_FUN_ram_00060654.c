/* Address: ram:00060654; name: FUN_ram_00060654; body bytes: 336 */

/* WARNING: Removing unreachable block (ram,0x000606a8) */
/* WARNING: Removing unreachable block (ram,0x000606ac) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00060654(int param_1)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = DAT_ram_20001d63;
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x2e) = DAT_ram_20001d63;
  uVar3 = FUN_ram_00042866(uVar1,*(undefined1 *)(param_1 + 0x2f));
  uVar7 = (uint)DAT_ram_20001b8c;
  uVar6 = uVar7 * *(ushort *)(param_1 + 0x38);
  uVar2 = (uint)DAT_ram_20001bd4;
  *(uint *)(param_1 + 0x94) = uVar3;
  *(uint *)(param_1 + 0x8c) = uVar6 / 800;
  if (uVar3 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    uVar3 = ((uint)*(ushort *)(param_1 + 0x38) * 0x4e2) / uVar3;
  }
  uVar2 = uVar2 + uVar3 + 0x17c;
  uVar3 = uVar2 & 0xffff;
  *(short *)(param_1 + 0x82) = (short)(uVar2 * 0x10000 >> 0x10);
  if (uVar7 == 0) {
    uVar5 = 0xffff;
  }
  else {
    uVar5 = (undefined2)(((uVar6 % 800) * 0x4e2) / uVar7);
  }
  *(undefined2 *)(param_1 + 0x20) = uVar5;
  uVar2 = (*(ushort *)(param_1 + 0x36) + 1) * 0x4e2 - uVar3;
  iVar4 = FUN_ram_0006bae2(uVar2 * uVar7,(int)((ulonglong)uVar2 * (ulonglong)uVar7 >> 0x20),1000000,
                           0);
  uVar2 = iVar4 + *(int *)(param_1 + 0x88);
  if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar2)) {
    uVar2 = uVar2 + 0x57400000;
  }
  *(uint *)(param_1 + 0x90) = uVar2;
  *(ushort *)(param_1 + 0x80) = (short)(uVar3 << 1) + (ushort)*(byte *)(param_1 + 0x35) * 0x4e2;
  FUN_ram_00055a44(param_1);
  FUN_ram_00055d70(param_1);
  FUN_ram_00055a08(param_1,*(short *)(param_1 + 0x3c) * 0x10 + -2);
  FUN_ram_00058334(param_1);
  DAT_ram_20001dfc = param_1;
  FUN_ram_00042570(&LAB_ram_000575b0,1);
  if (((DAT_ram_20001e7c & 2) != 0) && (DAT_ram_20001bec != (code *)0x0)) {
    (*DAT_ram_20001bec)(0xd,*(undefined4 *)(param_1 + 0x98));
    (*DAT_ram_20001bec)(0xe,*(undefined4 *)(param_1 + 0x9c));
  }
  DAT_ram_20001d6e = 0;
  _DAT_ram_20001d70 = 0;
  return;
}

