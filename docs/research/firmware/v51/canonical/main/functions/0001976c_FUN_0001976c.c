/* Address: 0001976c; name: FUN_0001976c; body bytes: 26 */

void FUN_0001976c(void)

{
  enter_critical();
  DAT_1fffaa1e = DAT_1fffaa1e & 0xffbf;
  exit_critical();
  return;
}

