/* Address: 0004d40e; name: FUN_0004d40e; body bytes: 76 */

undefined8 FUN_0004d40e(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  iStack_20 = param_1;
  uStack_1c = param_2;
  uStack_18 = param_3;
  uStack_14 = param_4;
  FUN_0004bb48();
  iVar1 = FUN_00040994();
  if (iVar1 != 0) {
    FUN_0003d9a4(&iStack_20,param_2);
    iVar1 = FUN_0004af50(param_1,&iStack_20);
    if (iVar1 != 0) {
      if ((*(int *)(param_1 + 8) != 0) &&
         ((*(ushort *)(*(int *)(param_1 + 8) + 0x2a) & 0xfff) >> 10 == 2)) {
        FUN_0003db32(&iStack_20,5);
      }
      uVar2 = FUN_0004bb48(param_1);
      FUN_00048958(uVar2,&iStack_20);
    }
  }
  return CONCAT44(uStack_1c,iStack_20);
}

