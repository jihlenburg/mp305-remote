/* Address: 000404ba; name: FUN_000404ba; body bytes: 40 */

void FUN_000404ba(int param_1)

{
  FUN_0004a57a(param_1,0,2);
  FUN_0004a57a(param_1 + 2,0,2);
  FUN_0004a57a(param_1 + 4,0,2);
  *(undefined1 *)(param_1 + 6) = 0xff;
  *(undefined1 *)(param_1 + 7) = 0xff;
  return;
}

