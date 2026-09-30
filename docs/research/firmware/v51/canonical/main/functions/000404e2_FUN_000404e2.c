/* Address: 000404e2; name: FUN_000404e2; body bytes: 42 */

void FUN_000404e2(int param_1)

{
  FUN_0004a57a(param_1,0,4);
  FUN_0004a57a(param_1 + 4,0,4);
  FUN_0004a57a(param_1 + 8,0,4);
  *(undefined1 *)(param_1 + 0xc) = 0xff;
  *(undefined1 *)(param_1 + 0xd) = 0xff;
  return;
}

