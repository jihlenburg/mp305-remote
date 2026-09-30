/* Address: 0001459e; name: FUN_0001459e; body bytes: 10 */

undefined4 FUN_0001459e(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + param_2 * 0x40 + 0x40) = param_3;
  return 0;
}

