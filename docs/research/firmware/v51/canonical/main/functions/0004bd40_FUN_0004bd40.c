/* Address: 0004bd40; name: FUN_0004bd40; body bytes: 16 */

uint FUN_0004bd40(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    return (*(ushort *)(*(int *)(param_1 + 8) + 0x2a) & 0x3ff) >> 6;
  }
  return 0xf;
}

