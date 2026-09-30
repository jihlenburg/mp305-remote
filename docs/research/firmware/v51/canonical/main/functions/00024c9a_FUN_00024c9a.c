/* Address: 00024c9a; name: FUN_00024c9a; body bytes: 26 */

void FUN_00024c9a(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00024cea();
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffffd;
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffffe;
  return;
}

