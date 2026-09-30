/* Address: ram:00052648; name: FUN_ram_00052648; body bytes: 76 */

bool FUN_ram_00052648(uint param_1,uint param_2,uint param_3,int param_4)

{
  gp = 0x20004000;
  if (((((param_1 - 6 & 0xffff) < 0xc7b) && (param_2 < 0xc81)) && (param_1 <= param_2)) &&
     ((param_3 < 500 && ((param_4 - 10U & 0xffff) < 0xc77)))) {
    return (int)((param_3 + 1) * param_2) < param_4 << 3;
  }
  return false;
}

