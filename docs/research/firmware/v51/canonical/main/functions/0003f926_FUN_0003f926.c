/* Address: 0003f926; name: FUN_0003f926; body bytes: 58 */

void FUN_0003f926(int param_1,int *param_2)

{
  if (param_2 != (int *)0x0) {
    if ((-1 < (int)((uint)*(byte *)(param_2 + 4) << 0x1d)) && (param_2[1] != 0)) {
      FUN_00046bec();
    }
    if ((-1 < (int)((uint)*(byte *)(param_2 + 4) << 0x1e)) && (*param_2 != 0)) {
      FUN_00046bec();
    }
    FUN_0004a2ac(param_1 + 0x2c,param_2);
    FUN_00046bec(param_2);
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

