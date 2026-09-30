/* Address: 00048a44; name: FUN_00048a44; body bytes: 98 */

/* Recovered from stored Thumb pointer at 0007a744; callback identification is inferred until
   reviewed. */

void FUN_00048a44(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  FUN_0004e00e(param_2,4);
  *(undefined4 *)(param_2 + 0x48) = 0;
  *(undefined1 *)(param_2 + 0x4c) = 0;
  *(undefined1 *)(param_2 + 0x4d) = 0;
  FUN_0004ac0a(param_2,5,0,0);
  FUN_0004aa4c(param_2,0x48a8d,0x20,0);
  FUN_0004e8a8(param_2,0);
  FUN_0003ee60(param_2,(&PTR_PTR_1ffe00d0)[*(byte *)(param_2 + 0x4c)]);
  if ((*(byte *)(param_2 + 0x4d) & 1) != 0) {
    FUN_0003ee46(param_2,(&PTR_DAT_1ffe00f8)[*(byte *)(param_2 + 0x4c)]);
    return;
  }
  iVar1 = FUN_0004a318(*(int *)(param_2 + 0x38) << 1);
  FUN_0004a404(iVar1,(&PTR_DAT_1ffe00f8)[*(byte *)(param_2 + 0x4c)],*(int *)(param_2 + 0x38) << 1);
  for (uVar2 = 0; uVar2 < *(uint *)(param_2 + 0x38); uVar2 = uVar2 + 1) {
    *(ushort *)(iVar1 + uVar2 * 2) = *(ushort *)(iVar1 + uVar2 * 2) & 0xfbff;
  }
  FUN_0003ee46(param_2,iVar1);
  FUN_00046bec(iVar1);
  return;
}

