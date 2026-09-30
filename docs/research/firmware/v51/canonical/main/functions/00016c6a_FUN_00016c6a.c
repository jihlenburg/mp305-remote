/* Address: 00016c6a; name: FUN_00016c6a; body bytes: 48 */

undefined8 FUN_00016c6a(undefined1 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 local_14;
  undefined1 local_10;
  undefined3 uStack_f;
  
  uVar2 = 0;
  _local_10 = CONCAT31((int3)((uint)param_4 >> 8),param_1);
  local_14 = param_3;
  iVar1 = FUN_00016468(0x40,&local_10,1,&local_14);
  if (iVar1 == 0) {
    uVar2 = (uint)CONCAT11((undefined1)local_14,local_14._1_1_);
  }
  return CONCAT44(2,uVar2);
}

