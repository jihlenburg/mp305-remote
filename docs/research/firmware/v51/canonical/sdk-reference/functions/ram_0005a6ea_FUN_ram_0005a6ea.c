/* Address: ram:0005a6ea; name: FUN_ram_0005a6ea; body bytes: 244 */

/* WARNING: Removing unreachable block (ram,0x0005a726) */
/* WARNING: Removing unreachable block (ram,0x0005a744) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_0005a6ea(int param_1)

{
  uint uVar1;
  undefined2 uVar2;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x2e) = DAT_ram_20001d63;
  *(uint *)(param_1 + 0x8c) = ((uint)*(ushort *)(param_1 + 0x38) * (uint)DAT_ram_20001b8c) / 800;
  FUN_ram_00056062();
  uVar1 = (uint)DAT_ram_20001b8c;
  if (uVar1 == 0) {
    uVar2 = 0xffff;
  }
  else {
    uVar2 = (undefined2)((((*(ushort *)(param_1 + 0x38) * uVar1) % 800) * 0x4e2) / uVar1);
  }
  *(undefined2 *)(param_1 + 0x20) = uVar2;
  *(short *)(param_1 + 0x80) = *(short *)(param_1 + 0x82) << 1;
  FUN_ram_00055a44(param_1);
  FUN_ram_00055d70(param_1);
  FUN_ram_00055a08(param_1,*(short *)(param_1 + 0x3c) * 0x10 + -2);
  FUN_ram_00058334(param_1);
  *(undefined1 *)(param_1 + 0x135) = 0x18;
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

