/* Address: ram:0006aadc; name: FUN_ram_0006aadc; body bytes: 82 */

undefined4 FUN_ram_0006aadc(void)

{
  int iVar1;
  
  gp = 0x20004000;
  if (DAT_ram_200019cc == -1) {
    iVar1 = TMOS_ProcessEventRegister(&LAB_ram_0006aa06);
    DAT_ram_200019cc = (char)iVar1;
    if (iVar1 != 0xff) {
      DAT_ram_20001ab8 = 0;
      DAT_ram_20001f48 = 2;
      FUN_ram_00044cc8();
      gp = 0x20004000;
      return 0;
    }
  }
  return 0x18;
}

