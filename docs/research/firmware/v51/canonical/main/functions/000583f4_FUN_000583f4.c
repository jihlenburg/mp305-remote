/* Address: 000583f4; name: FUN_000583f4; body bytes: 60 */

void FUN_000583f4(int param_1,int param_2,int param_3)

{
  if (param_3 != 2) {
    if (param_3 == 3) {
      if (*(int *)(param_1 + 0x34) < 1) {
        *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_2 + 0x34);
      }
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_2 + 0x44);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x40);
      *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x10);
    }
    return;
  }
  if (*(int *)(param_1 + 0x34) < 1) {
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_2 + 0x34);
  }
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_2 + 0x44);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x38);
  return;
}

