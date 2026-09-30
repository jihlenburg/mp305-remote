/* Address: ram:0004a0d4; name: FUN_ram_0004a0d4; body bytes: 80 */

void FUN_ram_0004a0d4(undefined2 *param_1)

{
  short *psVar1;
  short *psVar2;
  
  gp = 0x20004000;
  psVar1 = param_1 + 2;
  do {
    if (*psVar1 == 0) break;
    if (*(int *)(psVar1 + 4) != 0) {
      FUN_ram_20000104();
    }
    tmos_memset(psVar1,0,0xc);
    psVar2 = psVar1 + 6;
    *psVar1 = 0;
    psVar1 = psVar2;
  } while (psVar2 != param_1 + 0x5c);
  *param_1 = 0xffff;
  return;
}

