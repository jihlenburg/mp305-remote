/* Address: 00045330; name: FUN_00045330; body bytes: 58 */

void FUN_00045330(int param_1)

{
  int iVar1;
  
  FUN_0004aa44();
  if ((*(char *)(param_1 + 4) == '\x02') && (iVar1 = *(int *)(param_1 + 0x20), iVar1 != 0)) {
    if (*(int *)(iVar1 + 0x10) < 0) {
      FUN_00046bec(*(undefined4 *)(iVar1 + 4));
      FUN_00046bec(*(undefined4 *)(param_1 + 0x20));
    }
    else {
      *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + -1;
    }
  }
  FUN_0004aa48(&DAT_2003a554);
  return;
}

