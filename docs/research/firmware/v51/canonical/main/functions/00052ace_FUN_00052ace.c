/* Address: 00052ace; name: FUN_00052ace; body bytes: 24 */

int FUN_00052ace(uint *param_1)

{
  uint uVar1;
  
  uVar1 = FUN_000526fc(param_1[1]);
  if (*param_1 <= uVar1) {
    return 0;
  }
  return *param_1 - uVar1;
}

