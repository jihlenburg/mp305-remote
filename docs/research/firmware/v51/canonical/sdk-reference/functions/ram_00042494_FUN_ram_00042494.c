/* Address: ram:00042494; name: FUN_ram_00042494; body bytes: 90 */

undefined4 FUN_ram_00042494(uint param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  gp = 0x20004000;
  if (param_1 < 0x30) {
    uVar1 = 2;
    if (*(int *)(DAT_ram_20001bf8 + param_1 * 0xc) != 0) {
      tmos_stop_task(param_1 >> 4,1 << (param_1 & 0xf) & 0xffff);
      puVar2 = (undefined4 *)(DAT_ram_20001bf8 + param_1 * 0xc);
      *puVar2 = 0;
      puVar2[1] = 0;
      uVar1 = 0;
    }
    return uVar1;
  }
  return 2;
}

