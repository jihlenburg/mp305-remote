/* Address: 0004a030; name: FUN_0004a030; body bytes: 10 */

uint FUN_0004a030(int param_1)

{
  return (*(byte *)(param_1 + 0x34) & 3) >> 1;
}

