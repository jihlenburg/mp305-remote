/* Address: 00041546; name: FUN_00041546; body bytes: 12 */

bool FUN_00041546(uint *param_1,uint param_2)

{
  return (param_2 & *param_1 >> 0x10) != 0;
}

