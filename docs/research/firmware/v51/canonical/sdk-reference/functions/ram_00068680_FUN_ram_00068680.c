/* Address: ram:00068680; name: FUN_ram_00068680; body bytes: 126 */

undefined4 FUN_ram_00068680(void)

{
  int iVar1;
  
  gp = 0x20004000;
  if (DAT_ram_200019cc == -1) {
    iVar1 = TMOS_ProcessEventRegister(FUN_ram_00068306);
    DAT_ram_200019cc = (char)iVar1;
    if (iVar1 != 0xff) {
      DAT_ram_20001a78 = 0;
      DAT_ram_20001f20 = 0;
      DAT_ram_20001f48 = 1;
      DAT_ram_20001f16 = 3;
      DAT_ram_20001f24 = 0;
      DAT_ram_20001f15 = 7;
      DAT_ram_20001f49 = 0;
      FUN_ram_00044cc8();
      gp = 0x20004000;
      return 0;
    }
  }
  return 0x18;
}

