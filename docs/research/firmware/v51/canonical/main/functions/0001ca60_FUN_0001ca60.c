/* Address: 0001ca60; name: FUN_0001ca60; body bytes: 54 */

void FUN_0001ca60(undefined2 param_1)

{
  FUN_0001af7c();
  enter_critical();
  DAT_1ffe01c4 = 1;
  DAT_1fffab1c = 0;
  DAT_1fff9550 = DAT_1fff9550 | 0x4008;
  DAT_1ffe01c6 = param_1;
  exit_critical();
  return;
}

