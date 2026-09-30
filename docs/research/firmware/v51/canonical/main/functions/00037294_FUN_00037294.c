/* Address: 00037294; name: FUN_00037294; body bytes: 72 */

uint FUN_00037294(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = param_1 - (uint)(param_2 < 3);
  return (uVar1 / 400 +
         ((((param_2 + (uint)(param_2 < 3) * 0xc + -2) * 0x1f) / 0xc + param_3 + uVar1 +
          (uVar1 >> 2)) - uVar1 / 100)) % 7;
}

