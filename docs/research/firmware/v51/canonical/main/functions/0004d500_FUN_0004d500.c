/* Address: 0004d500; name: FUN_0004d500; body bytes: 38 */

void FUN_0004d500(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) | 1;
  iVar1 = FUN_0004bc94();
  *(ushort *)(iVar1 + 0x2a) = *(ushort *)(iVar1 + 0x2a) | 4;
  uVar2 = FUN_0004bb48();
  FUN_00040acc(uVar2,0x35,0);
  return;
}

