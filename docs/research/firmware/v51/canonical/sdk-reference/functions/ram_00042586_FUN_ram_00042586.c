/* Address: ram:00042586; name: FUN_ram_00042586; body bytes: 282 */

void FUN_ram_00042586(void)

{
  int iVar1;
  uint uVar2;
  
  gp = 0x20004000;
  DAT_ram_20001bb8 = 0;
  DAT_ram_20001bfc = 0;
  DAT_ram_20001c00 = 0;
  tmos_memset(&DAT_ram_20001b94,0,0x1c);
  tmos_memset(&DAT_ram_20001b64,0,0x2c);
  FUN_ram_00041b50();
  DAT_ram_20001b66 = ((DAT_ram_20001bd3 >> 2) + (DAT_ram_20001bd3 & 3)) * '\x03' + 0xe;
  DAT_ram_20001bf8 = FUN_ram_20000040((uint)DAT_ram_20001b66 * 6 + 0x240,1);
  if (DAT_ram_20001bf8 != 0) {
    tmos_memset(DAT_ram_20001bf8,0,(uint)DAT_ram_20001b66 * 6 + 0x240);
    DAT_ram_20001b90 = DAT_ram_20001bf8 + 0x240;
    DAT_ram_20001bb4 = DAT_ram_20001b90 + (uint)DAT_ram_20001b66 * 4;
    FUN_ram_00041d84();
    FUN_ram_00042a74();
    iVar1 = DAT_ram_20001b90;
    uVar2 = (uint)DAT_ram_20001b65;
    *(undefined1 **)(uVar2 * 4 + DAT_ram_20001b90) = &LAB_ram_00041db0;
    *(code **)((uVar2 + 1 & 0xff) * 4 + iVar1) = FUN_ram_00041e32;
    DAT_ram_20001b65 = DAT_ram_20001b65 + 3;
    *(code **)((uVar2 + 2 & 0xff) * 4 + iVar1) = FUN_ram_00041e32;
  }
  return;
}

