/* Address: ram:00043120; name: FUN_ram_00043120; body bytes: 70 */

bool FUN_ram_00043120(undefined1 *param_1,int param_2)

{
  gp = 0x20004000;
  if (param_1 != (undefined1 *)0x0) {
    if (param_2 != 0) {
      tmos_memcpy(param_2,&DAT_ram_0006bf40,0x10);
      *(undefined1 *)(param_2 + 0xc) = *param_1;
      *(undefined1 *)(param_2 + 0xd) = param_1[1];
    }
    return param_2 != 0;
  }
  return false;
}

