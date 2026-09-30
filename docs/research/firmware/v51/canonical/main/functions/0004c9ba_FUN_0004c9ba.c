/* Address: 0004c9ba; name: FUN_0004c9ba; body bytes: 46 */

int FUN_0004c9ba(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_0004c7e0();
  iVar2 = FUN_0004c68a(param_1,param_2);
  uVar3 = FUN_0004c654(param_1,param_2);
  if ((uVar3 & 1) != 0) {
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

