/* Address: 0004ef6a; name: FUN_0004ef6a; body bytes: 38 */

void FUN_0004ef6a(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_000263a0();
  iVar2 = *(int *)(param_1 + 8);
  if (iVar2 == 0) {
    if (uVar1 == 0) {
      return;
    }
    FUN_0004af28(param_1);
    iVar2 = *(int *)(param_1 + 8);
  }
  *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xf3ff | (ushort)((uVar1 & 3) << 10);
  return;
}

