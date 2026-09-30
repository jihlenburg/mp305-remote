/* Address: ram:00048444; name: GGS_GetParameter; body bytes: 104 */

undefined4 GGS_GetParameter(int param_1,undefined2 *param_2)

{
  gp = 0x20004000;
  if (param_1 == 1) {
    *param_2 = DAT_ram_20001a24;
    return 0;
  }
  if (param_1 == 0) {
    tmos_memcpy(param_2,&DAT_ram_20001ae4,0x15);
  }
  else if (param_1 == 4) {
    FUN_ram_0006be7a(param_2,&DAT_ram_200019ac,8);
  }
  else {
    if (param_1 != 9) {
      gp = 0x20004000;
      return 2;
    }
    *(undefined1 *)param_2 = DAT_ram_200019a5;
  }
  return 0;
}

