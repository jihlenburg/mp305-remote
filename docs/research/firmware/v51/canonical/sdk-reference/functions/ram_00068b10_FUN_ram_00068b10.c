/* Address: ram:00068b10; name: FUN_ram_00068b10; body bytes: 326 */

byte FUN_ram_00068b10(uint param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  undefined1 auStack_54 [16];
  undefined1 auStack_44 [24];
  undefined1 auStack_2c [28];
  
  gp = 0x20004000;
  if (DAT_ram_20001a86 == param_1) {
    tmos_clear_event(DAT_ram_20001a8e,1);
    tmos_clear_event(DAT_ram_20001a8e,2);
    FUN_ram_00068ade();
  }
  uVar10 = param_1 * 6 & 0xff;
  uVar1 = uVar10 + 0x20 & 0xff;
  iVar9 = tmos_snv_read(uVar1,0x10,auStack_54);
  if ((iVar9 == 0) && (iVar9 = tmos_isbufset(auStack_54,0xff,6), iVar9 == 0)) {
    tmos_memset(auStack_54,0xff,0x10);
    tmos_memset(auStack_2c,0xff,0x1c);
    tmos_memset(auStack_44,0xff,0x18);
    bVar2 = FUN_ram_00042e5e(uVar1,0x10,auStack_54);
    bVar3 = FUN_ram_00042e5e(uVar10 + 0x21 & 0xff,0x1c,auStack_2c);
    bVar4 = FUN_ram_00042e5e(uVar10 + 0x22 & 0xfe,0x1c,auStack_2c);
    bVar5 = FUN_ram_00042e5e(uVar10 + 0x23 & 0xff,0x10,auStack_2c);
    bVar6 = FUN_ram_00042e5e(uVar10 + 0x24 & 0xfe,0x10,auStack_2c);
    bVar7 = FUN_ram_00042e5e(uVar10 + 0x25 & 0xff,4,auStack_2c);
    bVar8 = FUN_ram_00042e5e(param_1 + 0x70 & 0xff,0x18,auStack_44);
    bVar8 = bVar2 | bVar3 | bVar4 | bVar5 | bVar6 | bVar7 | bVar8;
    FUN_ram_00042e10(DAT_ram_200019c4);
  }
  else {
    bVar8 = 0;
  }
  return bVar8;
}

