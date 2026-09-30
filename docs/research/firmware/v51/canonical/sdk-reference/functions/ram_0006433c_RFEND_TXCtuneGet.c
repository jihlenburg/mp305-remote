/* Address: ram:0006433c; name: RFEND_TXCtuneGet; body bytes: 88 */

undefined4 RFEND_TXCtuneGet(undefined1 *param_1)

{
  gp = 0x20004000;
  if (param_1 != (undefined1 *)0x0) {
    *param_1 = 6;
    param_1[1] = DAT_ram_20001a75;
    param_1[2] = DAT_ram_20001a76;
    param_1[3] = DAT_ram_20001f00;
    param_1[4] = DAT_ram_20001ef0;
    param_1[5] = DAT_ram_20001f01;
    param_1[6] = DAT_ram_20001ef8;
    return 0;
  }
  return 1;
}

