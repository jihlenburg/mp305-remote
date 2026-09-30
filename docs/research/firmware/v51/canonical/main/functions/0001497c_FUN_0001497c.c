/* Address: 0001497c; name: FUN_0001497c; body bytes: 44 */

undefined4 FUN_0001497c(undefined4 param_1)

{
  int iVar1;
  undefined4 extraout_r2;
  uint extraout_r3;
  uint local_c;
  
  local_c = 0;
  do {
    iVar1 = FUN_0001470c(param_1);
    if (iVar1 == 1) {
      return extraout_r2;
    }
    local_c = local_c + 1;
  } while (local_c <= extraout_r3);
  return 0xfffffff8;
}

