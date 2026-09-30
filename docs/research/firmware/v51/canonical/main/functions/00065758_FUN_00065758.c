/* Address: 00065758; name: FUN_00065758; body bytes: 64 */

void FUN_00065758(int param_1)

{
  if (param_1 != 0) {
    if (((int)*(uint *)(param_1 + -4) < 0) && (*(int *)(param_1 + -8) == 0)) {
      *(uint *)(param_1 + -4) = *(uint *)(param_1 + -4) & 0x7fffffff;
      FUN_00065c04();
      DAT_1ffe0064 = *(int *)(param_1 + -4) + DAT_1ffe0064;
      FUN_00059bcc((int *)(param_1 + -8));
      DAT_1ffe0070 = DAT_1ffe0070 + 1;
      FUN_00066f6c();
      return;
    }
  }
  return;
}

