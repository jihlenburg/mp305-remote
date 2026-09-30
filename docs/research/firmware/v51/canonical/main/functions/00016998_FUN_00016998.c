/* Address: 00016998; name: FUN_00016998; body bytes: 80 */

undefined4 FUN_00016998(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_1fff8ec0 == '\x01') {
    DAT_1fff8ec0 = '\0';
    DAT_1fff8ebc = 0;
    DAT_1fff8ea0 = 0;
    DAT_1fff8eac = param_1;
    DAT_1fff8eb0 = param_2;
    FUN_00016834(&DAT_4004e000,1);
    FUN_00016988(&DAT_4004e000,1);
    FUN_00016ad2(&DAT_4004e000,1);
    FUN_00016ad2(&DAT_4004e000,0);
    FUN_0001691e(&DAT_4004e000);
  }
  else {
    uVar1 = 0xfffffffa;
  }
  return uVar1;
}

