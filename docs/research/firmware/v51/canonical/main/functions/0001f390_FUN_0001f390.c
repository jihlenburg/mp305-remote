/* Address: 0001f390; name: FUN_0001f390; body bytes: 52 */

undefined4 FUN_0001f390(uint *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (uint *)0x0) {
    uVar1 = 0xfffffffd;
  }
  else {
    DAT_40049000 = (*param_1 | param_1[1] | param_1[2] | param_1[3] | param_1[4]) & 0x80010ff3 |
                   DAT_40049000 & 0x7ffef00c;
  }
  return uVar1;
}

