/* Address: 0004b210; name: FUN_0004b210; body bytes: 118 */

void FUN_0004b210(undefined4 *param_1)

{
  int iVar1;
  undefined4 extraout_r2;
  
  if (param_1 != (undefined4 *)0x0) {
    FUN_0004d500();
    FUN_0004b648(0);
    FUN_00052580(param_1);
    FUN_0004b2e6(*param_1,param_1);
    FUN_0004b648(1);
    FUN_0004dedc(param_1,0xf0000,0xff);
    FUN_0004deac(param_1);
    iVar1 = FUN_000472c8();
    if ((iVar1 != 0) && (iVar1 = FUN_0004d478(param_1), iVar1 != 0)) {
      FUN_00047164(extraout_r2,param_1);
    }
    iVar1 = FUN_0004bc8c(param_1);
    if (iVar1 != 0) {
      FUN_0004e5a6(iVar1,0x27,param_1);
      FUN_0004e5a6(iVar1,0x28,param_1);
      FUN_0004d3d8(param_1);
      return;
    }
  }
  return;
}

