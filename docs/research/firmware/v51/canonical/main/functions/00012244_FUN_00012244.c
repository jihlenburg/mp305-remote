/* Address: 00012244; name: FUN_00012244; body bytes: 22 */

undefined4 FUN_00012244(char *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*param_1 == '\x01') {
    uVar1 = 0xfffffffa;
  }
  else {
    *param_1 = '\x01';
  }
  return uVar1;
}

