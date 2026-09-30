/* Address: 0004cd9c; name: FUN_0004cd9c; body bytes: 10 */

bool FUN_0004cd9c(int param_1,ushort param_2)

{
  return (*(ushort *)(param_1 + 0x28) & param_2) != 0;
}

