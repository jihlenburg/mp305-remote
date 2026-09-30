/* Address: 0004537c; name: FUN_0004537c; body bytes: 68 */

void FUN_0004537c(undefined4 param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  
  if (0xb4 < param_4) {
    param_4 = (int)(short)((short)param_4 + -0xb4);
  }
  iVar1 = thunk_FUN_00052d12((int)(short)((short)param_4 + 0x5a));
  iVar2 = thunk_FUN_00052d12(param_4);
  FUN_000453c0(param_1,param_2,param_3,param_2 + (iVar1 >> 5),param_3 + (iVar2 >> 5),param_5);
  return;
}

