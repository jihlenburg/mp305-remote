/* Address: ram:00062730; name: FUN_ram_00062730; body bytes: 84 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00062730(void)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = DAT_ram_20001eb0;
  gp = 0x20004000;
  *(undefined4 *)(DAT_ram_20001eb0 + 0x14) = 0x8c;
  *(undefined4 *)(iVar2 + 0x1c) = 0x76;
  *(undefined4 *)(iVar2 + 0x24) = 0x8c;
  *(undefined4 *)(iVar2 + 0x2c) = 0x3c;
  *(undefined4 *)(iVar2 + 0x34) = 0x8c;
  *(undefined4 *)(iVar2 + 0x3c) = 0x3c;
  *(undefined4 *)(iVar2 + 0x44) = 0x8c;
  uVar1 = DAT_ram_20001eac;
  *(undefined4 *)(iVar2 + 0x4c) = 0x76;
  *(undefined4 *)(iVar2 + 0x74) = uVar1;
  *(undefined4 *)(iVar2 + 8) = 0xffff;
  *(undefined4 *)(iVar2 + 0xc) = 0xf00f;
  DAT_ram_e000e052 = 0x15;
  _DAT_ram_e000e068 = 0x2000168b;
  return;
}

