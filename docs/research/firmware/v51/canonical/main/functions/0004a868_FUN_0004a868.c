/* Address: 0004a868; name: FUN_0004a868; body bytes: 28 */

void FUN_0004a868(undefined4 param_1,int param_2)

{
  if ((*(char *)(param_2 + 0x30) == '\0') && (*(int *)(param_2 + 0x2c) != 0)) {
    FUN_00046bec();
  }
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  return;
}

