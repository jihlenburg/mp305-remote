/* Address: ram:0006b1a8; name: FUN_ram_0006b1a8; body bytes: 272 */

undefined4 FUN_ram_0006b1a8(void)

{
  int iVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001bd3 & 3) == 0) {
    return 0x18;
  }
  if (DAT_ram_200019cc == -1) {
    iVar1 = TMOS_ProcessEventRegister(FUN_ram_0006ae86);
    DAT_ram_200019cc = (char)iVar1;
    if (iVar1 != 0xff) {
      DAT_ram_20001abc = 0;
      DAT_ram_20001f20 = 0;
      DAT_ram_20001f48 = 4;
      FUN_ram_00044cc8();
      tmos_memset(&DAT_ram_20001f28,0,0x10);
      tmos_memset(&DAT_ram_20001f38,0,0x10);
      DAT_ram_20001f16 = 0;
      DAT_ram_20001f24 = 0;
      DAT_ram_20001f15 = 7;
      DAT_ram_20001f49 = 0;
      DAT_ram_20001acc = 0;
      tmos_snv_read(2,0x10,&DAT_ram_20001f28);
      tmos_snv_read(3,0x10,&DAT_ram_20001f38);
      tmos_memcpy(&DAT_ram_20001b34,&DAT_ram_20001f28,0x10);
      tmos_memcpy(&DAT_ram_20001b44,&DAT_ram_20001f38,0x10);
      tmos_snv_read(4,4,&DAT_ram_20001acc);
      gp = 0x20004000;
      return 0;
    }
  }
  return 0x18;
}

