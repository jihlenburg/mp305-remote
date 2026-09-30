/* Address: CODE:8a3b; name: FUN_CODE_8a3b; body bytes: 45 */

void FUN_CODE_8a3b(byte param_1,char param_2)

{
  _1_4 = 0;
  thunk_FUN_CODE_a560();
  if (param_2 == '\x01') {
    thunk_FUN_CODE_90f3(0);
    FUN_CODE_ae2a(0x4b1);
    FUN_CODE_aa99();
    if ((param_1 >> 6 == 0) && ((param_1 >> 5 & 1) != 0)) {
      _1_4 = 1;
    }
  }
  return;
}

