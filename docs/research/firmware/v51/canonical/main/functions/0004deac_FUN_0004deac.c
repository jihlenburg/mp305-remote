/* Address: 0004deac; name: FUN_0004deac; body bytes: 46 */

undefined4 FUN_0004deac(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004cbde(param_1,0);
  iVar2 = FUN_0004c6cc(param_1,0);
  if ((iVar1 != 0x3fffffff) && (iVar2 != 0x3fffffff)) {
    return 0;
  }
  FUN_0004d500(param_1);
  return 1;
}

