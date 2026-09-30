/* Address: 0001972c; name: FUN_0001972c; body bytes: 26 */

void FUN_0001972c(void)

{
  enter_critical();
  DAT_1fffaa1e = DAT_1fffaa1e & 0xfeff;
  exit_critical();
  return;
}

