/* Address: ram:00062a48; name: RF_BondingErase; body bytes: 76 */

void RF_BondingErase(void)

{
  int iVar1;
  undefined1 auStack_18 [20];
  
  gp = 0x20004000;
  iVar1 = tmos_snv_read(0x10,6,auStack_18);
  if ((iVar1 == 0) && (iVar1 = tmos_isbufset(auStack_18,0xff,6), iVar1 != 1)) {
    tmos_memset(auStack_18,0xff,6);
    FUN_ram_00042e5e(0x10,6,auStack_18);
    FUN_ram_00042e10(1);
  }
  return;
}

