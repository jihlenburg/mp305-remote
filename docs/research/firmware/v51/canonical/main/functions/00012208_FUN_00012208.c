/* Address: 00012208; name: FUN_00012208; body bytes: 16 */

bool FUN_00012208(int param_1,byte param_2)

{
  return (*(byte *)(param_1 + 0x44) & param_2) != 0;
}

