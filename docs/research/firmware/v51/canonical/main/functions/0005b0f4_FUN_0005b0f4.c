/* Address: 0005b0f4; name: FUN_0005b0f4; body bytes: 30 */

void FUN_0005b0f4(int param_1)

{
  FUN_0004a2ac(&DAT_2003a4cc,param_1);
  if (*(code **)(param_1 + 0x14) != (code *)0x0) {
    (**(code **)(param_1 + 0x14))(param_1);
  }
  FUN_00046bec(param_1);
  return;
}

