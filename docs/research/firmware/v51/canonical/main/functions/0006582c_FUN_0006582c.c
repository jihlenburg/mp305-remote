/* Address: 0006582c; name: FUN_0006582c; body bytes: 68 */

void FUN_0006582c(int param_1,undefined4 param_2,undefined4 param_3)

{
  enter_critical();
  if (*(char *)(param_1 + 0x44) == -1) {
    *(undefined1 *)(param_1 + 0x44) = 0;
  }
  if (*(char *)(param_1 + 0x45) == -1) {
    *(undefined1 *)(param_1 + 0x45) = 0;
  }
  exit_critical();
  if (*(int *)(param_1 + 0x38) == 0) {
    FUN_000659e8(param_1 + 0x24,param_2,param_3);
  }
  FUN_00059ed0(param_1);
  return;
}

