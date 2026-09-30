/* Address: 0001f1be; name: FUN_0001f1be; body bytes: 48 */

undefined4 FUN_0001f1be(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  int extraout_r2;
  uint extraout_r3;
  
  uVar1 = 0;
  while( true ) {
    iVar2 = FUN_0001f01c(param_1,param_2);
    if (iVar2 == extraout_r2) {
      return 0;
    }
    if ((extraout_r3 < uVar1) && (extraout_r3 != 0xffffffff)) break;
    uVar1 = uVar1 + 1;
  }
  return 0xfffffff8;
}

