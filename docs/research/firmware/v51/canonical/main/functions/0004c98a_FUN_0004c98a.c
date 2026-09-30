/* Address: 0004c98a; name: FUN_0004c98a; body bytes: 48 */

int FUN_0004c98a(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_0004c924(param_1,param_2,0x11);
  iVar2 = FUN_0004c684(param_1,param_2);
  uVar3 = FUN_0004c648(param_1,param_2);
  if ((uVar3 & 1) != 0) {
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

