/* Address: 00027964; name: FUN_00027964; body bytes: 94 */

/* Recovered from stored Thumb pointer at 00060784; callback identification is inferred until
   reviewed. */

undefined8 FUN_00027964(int param_1,uint param_2,int param_3,int param_4)

{
  byte bVar1;
  int local_18;
  uint local_14;
  int local_10;
  int local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  if ((*(byte *)(param_1 + 100) & 1) != param_2) {
    if (param_2 == 0) {
      bVar1 = *(byte *)(param_1 + 100) & 0xfe;
    }
    else {
      bVar1 = *(byte *)(param_1 + 100) | 1;
    }
    *(byte *)(param_1 + 100) = bVar1;
    local_10 = param_3;
    local_c = param_4;
    FUN_0003d9fe(&local_18,param_1 + 0x50);
    local_18 = local_18 + *(int *)(*(int *)(param_1 + 0x2c) + 0x14);
    local_14 = *(int *)(*(int *)(param_1 + 0x2c) + 0x18) + local_14;
    local_10 = *(int *)(*(int *)(param_1 + 0x2c) + 0x14) + local_10;
    local_c = *(int *)(*(int *)(param_1 + 0x2c) + 0x18) + local_c;
    FUN_0004d40e(param_1,&local_18);
  }
  return CONCAT44(local_14,local_18);
}

