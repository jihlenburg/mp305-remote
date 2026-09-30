/* Address: ram:000449da; name: FUN_ram_000449da; body bytes: 82 */

undefined4 FUN_ram_000449da(undefined4 param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (DAT_ram_20001c06 != '\0') {
    tmos_memcpy(&DAT_ram_200019d8,param_1,6);
    FUN_ram_000442de(DAT_ram_20001c06,&DAT_ram_200019d8);
    uVar1 = thunk_FUN_ram_0006522a(&DAT_ram_200019d8);
    return uVar1;
  }
  return 0;
}

