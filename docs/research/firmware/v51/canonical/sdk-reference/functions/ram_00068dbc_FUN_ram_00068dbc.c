/* Address: ram:00068dbc; name: FUN_ram_00068dbc; body bytes: 220 */

void FUN_ram_00068dbc(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  gp = 0x20004000;
  for (uVar1 = 0; uVar1 < DAT_ram_20001a8d; uVar1 = uVar1 + 1 & 0xff) {
    iVar2 = uVar1 * 0x10;
    iVar3 = tmos_snv_read(uVar1 * 6 + 0x20 & 0xfe,0x10,DAT_ram_20001a88 + iVar2);
    if (iVar3 != 0) {
      tmos_memset(DAT_ram_20001a88 + iVar2,0xff,6);
      tmos_memset(DAT_ram_20001a88 + iVar2 + 6,0xff,6);
      *(undefined2 *)(iVar2 + DAT_ram_20001a88 + 0xc) = 0;
    }
  }
  uVar1 = FUN_ram_00068a86();
  if (DAT_ram_20001a8d == uVar1) {
    DAT_ram_20001f0f = DAT_ram_20001f0f | 1;
  }
  else {
    DAT_ram_20001f0f = DAT_ram_20001f0f & 0xfe;
  }
  if (DAT_ram_20001a85 != '\0') {
    FUN_ram_00068c88();
  }
  if (DAT_ram_20001a84 != '\0') {
    FUN_ram_00068cec();
  }
  FUN_ram_00068d94();
  return;
}

