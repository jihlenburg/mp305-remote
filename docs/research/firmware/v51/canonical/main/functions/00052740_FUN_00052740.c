/* Address: 00052740; name: FUN_00052740; body bytes: 80 */

int FUN_00052740(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0004b144(&DAT_0007af80,param_1);
  FUN_0004b210();
  uVar2 = FUN_0004f078((short)param_3 * 100);
  uVar3 = FUN_0004f078((short)param_2 * 100);
  FUN_0004e7c2(iVar1,uVar3,uVar2);
  *(char *)(iVar1 + 0x2c) = (char)param_4;
  if (param_2 == 0 && param_3 == 0) {
    FUN_0004e7d8(param_1,param_4);
  }
  return iVar1;
}

