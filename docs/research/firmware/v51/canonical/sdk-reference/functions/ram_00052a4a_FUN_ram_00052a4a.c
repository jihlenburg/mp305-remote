/* Address: ram:00052a4a; name: FUN_ram_00052a4a; body bytes: 276 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00052a4a(void)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  tmos_memcpy(&DAT_ram_20001e38,&DAT_ram_20001bd6,6);
  uVar1 = FUN_ram_00042910(0,0x3fff);
  iVar2 = FUN_ram_00042934(0,0xffffffff);
  while( true ) {
    if ((iVar2 != 0 || (uVar1 & 0x3fff) != 0) && ((iVar2 != -1 || ((uVar1 & 0x3fff) != 0x3fff))))
    break;
    uVar1 = FUN_ram_00042910(0,0x3fff);
    iVar2 = FUN_ram_00042934(0,0xffffffff);
  }
  DAT_ram_20001e48 = (undefined1)uVar1;
  DAT_ram_20001e49 = (byte)(uVar1 >> 8) | 0xc0;
  DAT_ram_20001e44 = iVar2;
  do {
    do {
      do {
        iVar2 = FUN_ram_00042910(0,0x3fff);
        uVar1 = FUN_ram_00042934(0,0xffffffff);
      } while (uVar1 == 0 && iVar2 == 0);
    } while ((uVar1 == 0xffffffff) && (iVar2 == 0x3fff));
    DAT_ram_20001e4c = (short)(uVar1 >> 0x10);
    DAT_ram_20001e4a = (undefined2)uVar1;
    _DAT_ram_20001e4e = (ushort)iVar2 & 0x3fff;
  } while (((uVar1 & 0xffff) == (uint)_DAT_ram_20001e38) &&
          ((DAT_ram_20001e4c == DAT_ram_20001e3a && (_DAT_ram_20001e4e == DAT_ram_20001e3c))));
  return;
}

