/* Address: 0001deba; name: FUN_0001deba; body bytes: 18 */

void FUN_0001deba(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)((param_1 + param_2 * 4 + 0x140) * 0x20 + 0x42000030) = param_3;
  return;
}

