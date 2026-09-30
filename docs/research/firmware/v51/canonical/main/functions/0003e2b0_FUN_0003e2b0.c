/* Address: 0003e2b0; name: FUN_0003e2b0; body bytes: 156 */

void FUN_0003e2b0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined1 auStack_70 [92];
  
  if (param_5 != 0) {
    if (*(int *)(param_4 + 0xc) == -1) {
      uVar1 = *param_3;
    }
    else {
      uVar1 = *(undefined4 *)(param_4 + 8);
    }
    *(undefined4 *)(param_4 + 4) = uVar1;
    *(undefined4 *)(param_4 + 8) = param_2;
    *param_3 = param_2;
    FUN_0003c97c(param_4,0);
    FUN_0003c9f8(auStack_70);
    FUN_0003cb2a(auStack_70,param_4);
    FUN_0003cafa(auStack_70,0x3e047);
    FUN_0003cb1e(auStack_70,0,0x100);
    FUN_0003cadc(auStack_70,0x3e04f);
    uVar1 = FUN_0004c924(param_1,0,100);
    FUN_0003caea(auStack_70,uVar1);
    FUN_0003cb6c(auStack_70);
    return;
  }
  FUN_0003c97c(param_4,0);
  *(undefined4 *)(param_4 + 0xc) = 0xffffffff;
  *param_3 = param_2;
  FUN_0004d3d8(param_1);
  FUN_0003c97c(param_4,0);
  FUN_0003e1ee(param_1,param_4);
  return;
}

