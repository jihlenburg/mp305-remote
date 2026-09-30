/* Address: 0004e25c; name: FUN_0004e25c; body bytes: 284 */

void FUN_0004e25c(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 auStack_70 [88];
  
  if (param_2 != 0 || param_3 != 0) {
    if (param_4 == 1) {
      uVar2 = FUN_0004bb48(param_1);
      FUN_0003c9f8(auStack_70);
      FUN_0003cb2a(auStack_70,param_1);
      FUN_0003cae6(auStack_70,0x5e4d5);
      if (param_2 != 0) {
        iVar1 = FUN_000408b0(uVar2);
        uVar3 = FUN_0003cb2e(iVar1 >> 1,200,400);
        FUN_0003caea(auStack_70,uVar3);
        iVar1 = FUN_0004bf20(param_1);
        FUN_0003cb1e(auStack_70,-iVar1,param_2 - iVar1);
        FUN_0003cafa(auStack_70,0x5e59d);
        FUN_0003cafe(auStack_70,0x3ca83);
        iVar1 = FUN_0004e5a6(param_1,9,auStack_70);
        if (iVar1 != 1) {
          return;
        }
        FUN_0003cb6c(auStack_70);
      }
      if (param_3 != 0) {
        iVar1 = FUN_00040960(uVar2);
        uVar2 = FUN_0003cb2e(iVar1 >> 1,200,400);
        FUN_0003caea(auStack_70,uVar2);
        iVar1 = FUN_0004bf2c(param_1);
        FUN_0003cb1e(auStack_70,-iVar1,param_3 - iVar1);
        FUN_0003cafa(auStack_70,0x5e5b3);
        FUN_0003cafe(auStack_70,0x3ca83);
        iVar1 = FUN_0004e5a6(param_1,9,auStack_70);
        if (iVar1 == 1) {
          FUN_0003cb6c(auStack_70);
        }
      }
    }
    else {
      FUN_0003c97c(param_1,0x5e5b3);
      FUN_0003c97c(param_1,0x5e59d);
      iVar1 = FUN_0004e5a6(param_1,9,0);
      if ((iVar1 == 1) && (iVar1 = FUN_0004e44e(param_1,param_2,param_3), iVar1 == 1)) {
        FUN_0004e5a6(param_1,0xb,0);
        return;
      }
    }
  }
  return;
}

