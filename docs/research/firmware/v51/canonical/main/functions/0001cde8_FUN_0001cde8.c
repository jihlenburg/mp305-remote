/* Address: 0001cde8; name: FUN_0001cde8; body bytes: 70 */

void FUN_0001cde8(undefined4 param_1,byte param_2,byte param_3,byte param_4,byte param_5,
                 byte param_6,byte param_7,byte param_8)

{
  int iVar1;
  
  iVar1 = FUN_00015ee8();
  *(byte *)(iVar1 + 8) =
       (param_2 & 1) << 6 | (param_3 & 1) << 5 | (param_4 & 1) << 4 | (param_5 & 1) << 3 |
       (param_6 & 1) << 2 | (param_7 & 1) << 1 | param_8 & 1;
  FUN_00012cb0(param_1,0xc);
  return;
}

