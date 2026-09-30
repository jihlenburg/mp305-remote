/* Address: 00060710; name: FUN_00060710; body bytes: 116 */

void FUN_00060710(int param_1)

{
  int iVar1;
  undefined1 auStack_68 [92];
  
  iVar1 = FUN_0004c924(param_1,0x60000,100);
  if (iVar1 == 0) {
    FUN_0003c97c(param_1,0x27965);
    *(byte *)(param_1 + 100) = *(byte *)(param_1 + 100) | 1;
  }
  else {
    FUN_0003c9f8(auStack_68);
    FUN_0003cb2a(auStack_68,param_1);
    FUN_0003cafa(auStack_68,0x27965);
    FUN_0003caea(auStack_68,iVar1);
    FUN_0003cb06(auStack_68,iVar1);
    FUN_0003cb1e(auStack_68,1,0);
    FUN_0003cafe(auStack_68,0x3cabd);
    FUN_0003cb0a(auStack_68,0xffffffff);
    FUN_0003cb6c(auStack_68);
  }
  return;
}

