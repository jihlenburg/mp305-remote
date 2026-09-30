/* Address: 0001bf3a; name: FUN_0001bf3a; body bytes: 98 */

undefined4 FUN_0001bf3a(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  if (param_1 + param_3 < 0x800001) {
    if (param_2 != 0) {
      for (; param_3 != 0; param_3 = param_3 - uVar2) {
        uVar2 = param_3;
        if (0xff < param_3) {
          uVar2 = 0x100;
        }
        FUN_0001f420(6,0);
        FUN_0001bf9c(2,param_1,param_2 + iVar3,uVar2);
        FUN_0001f3cc();
        FUN_0001f420(4,0);
        param_1 = param_1 + uVar2;
        iVar3 = iVar3 + uVar2;
      }
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

