/* Address: ram:00047880; name: FUN_ram_00047880; body bytes: 56 */

undefined4 FUN_ram_00047880(undefined4 param_1)

{
  gp = 0x20004000;
  if ((DAT_ram_20001a18 != 0) && (DAT_ram_20001a1c != (undefined4 *)0x0)) {
    tmos_memcpy(param_1,*DAT_ram_20001a1c,*(undefined2 *)(DAT_ram_20001a1c + 1));
    return 0;
  }
  return 2;
}

