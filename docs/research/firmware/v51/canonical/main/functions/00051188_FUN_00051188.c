/* Address: 00051188; name: FUN_00051188; body bytes: 138 */

void FUN_00051188(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_70 [92];
  
  iVar1 = FUN_0004c924(param_1,0,100);
  if (iVar1 == 0) {
    return;
  }
  uVar2 = FUN_0004c584(param_1);
  iVar4 = *(int *)(param_1 + 0x2c);
  iVar5 = 0x100;
  if (iVar4 == -1) {
    if ((uVar2 & 1) != 0) {
      iVar4 = 0;
      goto LAB_000511c0;
    }
    iVar4 = 0x100;
    iVar5 = 0;
  }
  else {
    if ((uVar2 & 1) == 0) {
      iVar5 = 0;
    }
LAB_000511c0:
    if (iVar4 - iVar5 < 1) {
      iVar3 = iVar5 - iVar4;
      goto LAB_000511cc;
    }
  }
  iVar3 = iVar4 - iVar5;
LAB_000511cc:
  FUN_0003c97c(param_1,0);
  FUN_0003c9f8(auStack_70);
  FUN_0003cb2a(auStack_70,param_1);
  FUN_0003cafa(auStack_70,0x51075);
  FUN_0003cb1e(auStack_70,iVar4,iVar5);
  FUN_0003cadc(auStack_70,0x51069);
  FUN_0003caea(auStack_70,(uint)(iVar1 * iVar3) >> 8);
  FUN_0003cb6c(auStack_70);
  return;
}

