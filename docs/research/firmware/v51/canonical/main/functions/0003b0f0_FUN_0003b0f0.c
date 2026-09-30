/* Address: 0003b0f0; name: FUN_0003b0f0; body bytes: 126 */

int FUN_0003b0f0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_0004c924(param_1,0x30000,0x3c);
  iVar2 = FUN_0004c924(param_1,0x30000,0x42);
  iVar3 = FUN_0004c960(param_1,0x30000);
  if (iVar3 < 1) {
    iVar3 = FUN_0004c960(param_1,0x30000);
    iVar3 = -iVar3;
  }
  else {
    iVar3 = FUN_0004c960(param_1,0x30000);
  }
  iVar4 = FUN_0004c96c(param_1,0x30000);
  if (iVar4 < 1) {
    iVar4 = FUN_0004c96c(param_1,0x30000);
    iVar4 = -iVar4;
  }
  else {
    iVar4 = FUN_0004c96c(param_1,0x30000);
  }
  iVar4 = iVar1 + iVar2 + iVar3 + iVar4;
  iVar2 = FUN_0004c924(param_1,0x30000,0x38);
  iVar3 = FUN_0004c924(param_1,0x30000,0x3b);
  iVar1 = iVar3 + iVar2;
  if (iVar3 + iVar2 < iVar4) {
    iVar1 = iVar4;
  }
  return iVar1;
}

