/* Address: 0005e538; name: FUN_0005e538; body bytes: 100 */

undefined8 FUN_0005e538(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_0003711e(param_1,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x40),&local_18);
  if (local_18 < 0) {
    iVar1 = -local_18;
LAB_0005e566:
    FUN_0004e388(param_1,iVar1,0,1);
  }
  else {
    iVar1 = FUN_0004ccf8(param_1);
    if (iVar1 < local_10) {
      iVar1 = FUN_0004ccf8(param_1);
      iVar1 = iVar1 - local_10;
      goto LAB_0005e566;
    }
  }
  if (local_14 < 0) {
    iVar1 = -local_14;
  }
  else {
    iVar1 = FUN_0004bbec(param_1);
    if (local_c <= iVar1) goto LAB_0005e59a;
    iVar1 = FUN_0004bbec(param_1);
    iVar1 = iVar1 - local_c;
  }
  FUN_0004e388(param_1,0,iVar1,1);
LAB_0005e59a:
  return CONCAT44(local_14,local_18);
}

