/* Address: 0001f420; name: FUN_0001f420; body bytes: 46 */

longlong FUN_0001f420(uint param_1,int param_2,int param_3)

{
  uint uStack_18;
  int iStack_14;
  int iStack_10;
  
  uStack_18 = param_1;
  iStack_14 = param_2;
  iStack_10 = param_3;
  FUN_00015384(2,0x20);
  FUN_00012d10(&uStack_18,1);
  if ((param_2 != 0) && (param_3 != 0)) {
    FUN_00012d10(param_2,param_3);
  }
  FUN_000153e0(2,0x20);
  return (ulonglong)uStack_18 << 0x20;
}

