/* Address: 00038000; name: FUN_00038000; body bytes: 234 */

void FUN_00038000(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 auStack_28 [8];
  int local_20;
  int local_1c;
  
  FUN_00025cb8(param_1,&local_48);
  FUN_0004a57a(auStack_28,0,0x10);
  iVar1 = FUN_0004c924(param_1,0,0x12);
  iVar2 = FUN_0004c6ba(param_1,0);
  iVar3 = FUN_0004c678(param_1,0);
  if (iVar3 << 0x1d < 0) {
    iVar1 = iVar1 + iVar2;
  }
  iVar2 = FUN_0004c924(param_1,0,0x10);
  iVar3 = FUN_0004c6ba(param_1,0);
  iVar4 = FUN_0004c678(param_1,0);
  if (iVar4 << 0x1e < 0) {
    iVar2 = iVar2 + iVar3;
  }
  local_20 = FUN_0004bf20(param_1);
  local_20 = (*(int *)(param_1 + 0x14) + iVar1) - local_20;
  local_1c = FUN_0004bf2c(param_1);
  local_1c = (*(int *)(param_1 + 0x18) + iVar2) - local_1c;
  uVar5 = 0;
  while( true ) {
    if (*(ushort *)(*(int **)(param_1 + 8) + 10) <= uVar5) break;
    FUN_0003aca0(*(undefined4 *)(**(int **)(param_1 + 8) + uVar5 * 4),&local_48,auStack_28);
    uVar5 = uVar5 + 1;
  }
  FUN_00046bec(local_48);
  FUN_00046bec(local_44);
  FUN_00046bec(local_40);
  FUN_00046bec(local_3c);
  iVar1 = FUN_0004cbf6(param_1,0);
  iVar2 = FUN_0004c6de(param_1,0);
  if ((iVar1 == 0x3fffffff) || (iVar2 == 0x3fffffff)) {
    FUN_0004dbe0(param_1);
  }
  FUN_0004e5a6(param_1,0x30,0);
  return;
}

