/* Address: 00013c12; name: FUN_00013c12; body bytes: 44 */

undefined4 FUN_00013c12(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r2;
  uint extraout_r3;
  uint local_c;
  
  uVar2 = 0xfffffff8;
  local_c = 0;
  while( true ) {
    if (param_2 < local_c) {
      return uVar2;
    }
    iVar1 = FUN_00013a78(param_1);
    if (iVar1 == 1) break;
    local_c = local_c + 1;
    uVar2 = extraout_r2;
    param_2 = extraout_r3;
  }
  return 0;
}

