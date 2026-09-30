/* Address: 00066ba4; name: FUN_00066ba4; body bytes: 92 */

undefined4
FUN_00066ba4(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00059f3c(param_3 << 2);
  if (iVar1 != 0) {
    iVar2 = FUN_00059f3c(0x50);
    if (iVar2 != 0) {
      FUN_0001049c(iVar2,0x50);
      *(int *)(iVar2 + 0x30) = iVar1;
      FUN_00059b48(param_1,param_2,param_3,param_4,param_5,param_6,iVar2,0);
      FUN_000598bc(iVar2);
      return 1;
    }
    FUN_00065758(iVar1);
  }
  return 0xffffffff;
}

