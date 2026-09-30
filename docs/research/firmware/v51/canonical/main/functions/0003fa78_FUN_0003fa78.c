/* Address: 0003fa78; name: FUN_0003fa78; body bytes: 30 */

void FUN_0003fa78(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_3 < *(uint *)(param_1 + 0x70)) {
    *(undefined4 *)(*(int *)(param_2 + 4) + param_3 * 4) = param_4;
    FUN_0003ab20(param_1,param_3);
    return;
  }
  return;
}

