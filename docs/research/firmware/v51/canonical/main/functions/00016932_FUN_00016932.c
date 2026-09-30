/* Address: 00016932; name: FUN_00016932; body bytes: 10 */

bool FUN_00016932(int param_1,uint param_2)

{
  return (*(uint *)(param_1 + 0x1c) & param_2) != 0;
}

