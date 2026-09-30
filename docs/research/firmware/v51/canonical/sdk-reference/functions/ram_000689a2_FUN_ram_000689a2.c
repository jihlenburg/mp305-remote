/* Address: ram:000689a2; name: FUN_ram_000689a2; body bytes: 150 */

undefined4 FUN_ram_000689a2(void)

{
  int iVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001bd3 & 0xfc) != 0) {
    iVar1 = TMOS_ProcessEventRegister(FUN_ram_000686fe);
    DAT_ram_20001a7c = (undefined1)iVar1;
    if (iVar1 != 0xff) {
      DAT_ram_20001f48 = 8;
      FUN_ram_00068974();
      if (DAT_ram_20001f17 != '\0') {
        gp = 0x20004000;
        return 0;
      }
      tmos_snv_read(2,0x10,&DAT_ram_20001f28);
      tmos_snv_read(3,0x10,&DAT_ram_20001f38);
      tmos_snv_read(4,4,&DAT_ram_20001acc);
      FUN_ram_00044cc8(DAT_ram_20001a7c);
      gp = 0x20004000;
      return 0;
    }
  }
  return 0x18;
}

