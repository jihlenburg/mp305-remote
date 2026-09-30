/* Address: 0003c24c; name: FUN_0003c24c; body bytes: 74 */

void FUN_0003c24c(undefined4 param_1,int param_2)

{
  DAT_1ffe015a = '\0';
  DAT_40053048 = DAT_40053048 & 0xffff | param_2 << 0x10;
  DAT_40053040 = param_1;
  FUN_0001453c(&DAT_40053000,0,1);
  DAT_4001c004 = DAT_4001c004 | 0x40;
  do {
  } while (DAT_1ffe015a == '\0');
  FUN_000144fc(1);
  do {
  } while (-1 < DAT_4001c014 << 0x1a);
  DAT_4001c004 = DAT_4001c004 & 0xffffffbf;
  return;
}

