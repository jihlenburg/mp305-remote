/* Address: 000498fc; name: FUN_000498fc; body bytes: 110 */

void FUN_000498fc(int param_1,int param_2)

{
  byte bVar1;
  
  FUN_0003c97c(param_1,0x5e7a9);
  FUN_0003c97c(param_1,0x5e7af);
  FUN_0004f266(param_1 + 0x54,0);
  if (((param_2 == 2) || (param_2 == 3)) || (param_2 == 4)) {
    bVar1 = *(byte *)(param_1 + 0x5c) | 0x10;
  }
  else {
    bVar1 = *(byte *)(param_1 + 0x5c) & 0xef;
  }
  *(byte *)(param_1 + 0x5c) = bVar1;
  if (((bVar1 & 7) == 1) && (*(int *)(param_1 + 0x34) != -1)) {
    FUN_00049898(param_1);
  }
  *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xf8 | (byte)param_2 & 7;
  FUN_000493d0(param_1);
  return;
}

