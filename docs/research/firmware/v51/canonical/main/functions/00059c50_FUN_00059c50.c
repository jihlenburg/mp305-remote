/* Address: 00059c50; name: FUN_00059c50; body bytes: 28 */

bool FUN_00059c50(int param_1)

{
  int iVar1;
  
  enter_critical();
  iVar1 = *(int *)(param_1 + 0x38);
  exit_critical();
  return iVar1 == 0;
}

