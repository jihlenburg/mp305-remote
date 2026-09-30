/* Address: ram:00066b28; name: FUN_ram_00066b28; body bytes: 64 */

undefined4 FUN_ram_00066b28(byte param_1,uint param_2,uint param_3)

{
  gp = 0x20004000;
  DAT_ram_20001d99 = param_1;
  if ((param_1 & 1) == 0) {
    if ((DAT_ram_20001d9c & param_2) != param_2) {
      gp = 0x20004000;
      return 0x12;
    }
    DAT_ram_20001d9a = (undefined1)(DAT_ram_20001d9c & param_2);
  }
  if ((param_1 & 2) == 0) {
    if ((DAT_ram_20001d9d & param_3) != param_3) {
      return 0x12;
    }
    DAT_ram_20001d9b = (undefined1)param_3;
  }
  return 0;
}

