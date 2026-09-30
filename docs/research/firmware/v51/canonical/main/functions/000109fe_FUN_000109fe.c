/* Address: 000109fe; name: FUN_000109fe; body bytes: 34 */

void FUN_000109fe(uint param_1)

{
  uint uVar1;
  
  uVar1 = (int)param_1 >> 0x1f;
  FUN_00010e18((param_1 ^ uVar1) - uVar1,0,0,0,0,uVar1 * -0x80000000,0x433);
  return;
}

