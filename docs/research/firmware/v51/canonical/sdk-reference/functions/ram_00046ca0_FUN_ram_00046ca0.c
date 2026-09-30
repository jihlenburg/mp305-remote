/* Address: ram:00046ca0; name: FUN_ram_00046ca0; body bytes: 170 */

undefined4 FUN_ram_00046ca0(byte param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  gp = 0x20004000;
  FUN_ram_000460f6(DAT_ram_20001a02,1);
  if ((DAT_ram_20001d50 & 10) == 0) {
    DAT_ram_20001a02 = 0;
    FUN_ram_00044092(0);
  }
  else {
    DAT_ram_20001a02 = param_1;
    FUN_ram_00044092(&DAT_ram_20001ca8);
    if (DAT_ram_20001a08 != 0) {
      gp = 0x20004000;
      return 0x13;
    }
    if (DAT_ram_20001a02 != 0) {
      DAT_ram_20001a08 = FUN_ram_20000040((uint)DAT_ram_20001a02 << 4,0x471b);
      if (DAT_ram_20001a08 == 0) {
        gp = 0x20004000;
        return 0x13;
      }
      tmos_memset(DAT_ram_20001a08,0,(uint)DAT_ram_20001a02 << 4);
      iVar1 = DAT_ram_20001a08;
      uVar2 = (uint)DAT_ram_20001a02;
      for (uVar3 = 0; (uVar3 & 0xff) < uVar2; uVar3 = uVar3 + 1) {
        *(undefined1 *)(uVar3 * 0x10 + iVar1) = 0xff;
      }
    }
  }
  return 0;
}

