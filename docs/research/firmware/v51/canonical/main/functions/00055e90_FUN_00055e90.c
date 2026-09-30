/* Address: 00055e90; name: FUN_00055e90; body bytes: 36 */

void FUN_00055e90(int param_1)

{
  if (DAT_1ffe02dc != param_1) {
    DAT_1ffe02dc = param_1;
    FUN_000499de(DAT_1ffe04e4,&DAT_00055eb8,param_1,(uint)(param_1 * 9) / 5 + 0x20);
    return;
  }
  return;
}

