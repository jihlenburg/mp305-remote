/* Address: 0001c2e0; name: FUN_0001c2e0; body bytes: 28 */

undefined4 FUN_0001c2e0(int param_1,uint param_2,uint param_3,int param_4)

{
  while( true ) {
    if ((*(uint *)(param_1 + 0x14) & param_2) == param_3) {
      return 0;
    }
    if (param_4 == 0) break;
    param_4 = param_4 + -1;
  }
  return 0xfffffff8;
}

