/* Address: 000521da; name: FUN_000521da; body bytes: 40 */

void FUN_000521da(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x34) != 0) {
    FUN_00046bec();
    *(undefined4 *)(param_2 + 0x34) = 0;
  }
  if (*(int *)(param_2 + 0x38) != 0) {
    FUN_00046bec();
    *(undefined4 *)(param_2 + 0x38) = 0;
  }
  if (*(int *)(param_2 + 0x30) != 0) {
    FUN_00046bec();
    *(undefined4 *)(param_2 + 0x30) = 0;
  }
  return;
}

