/* Address: ram:00065e92; name: FUN_ram_00065e92; body bytes: 38 */

undefined4 FUN_ram_00065e92(undefined1 *param_1)

{
  gp = 0x20004000;
  *param_1 = (char)DAT_ram_20001bcc;
  param_1[1] = (char)((ushort)DAT_ram_20001bcc >> 8);
  param_1[2] = DAT_ram_20001bcb;
  return 0;
}

