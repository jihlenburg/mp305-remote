/* Address: 000374e4; name: FUN_000374e4; body bytes: 170 */

void FUN_000374e4(int param_1,int *param_2,int param_3,int *param_4)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  
  iVar2 = FUN_0004c5ac(param_1,0x20000,param_3,param_4,param_3,param_4);
  iVar2 = iVar2 / 2;
  fVar9 = (float)FUN_00036de0(param_1);
  sVar1 = *(short *)(param_1 + 0x5c) + (short)(int)fVar9;
  iVar3 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
  iVar3 = (param_3 - iVar2) * iVar3 >> 0xf;
  iVar4 = thunk_FUN_00052d12((int)sVar1);
  iVar8 = (param_3 - iVar2) * iVar4 >> 0xf;
  iVar4 = FUN_0004c846(param_1,0x30000);
  iVar5 = FUN_0004c88e(param_1,0x30000);
  iVar6 = FUN_0004c8e2(param_1,0x30000);
  iVar7 = FUN_0004c7e6(param_1,0x30000);
  *param_4 = ((*param_2 + iVar3) - iVar4) - iVar2;
  param_4[2] = iVar5 + iVar2 + *param_2 + iVar3;
  param_4[1] = ((param_2[1] + iVar8) - iVar6) - iVar2;
  param_4[3] = iVar7 + iVar2 + param_2[1] + iVar8;
  return;
}

